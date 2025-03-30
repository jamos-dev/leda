#include <stddef.h>
#include <stdint.h>
//#include <string.h>

#include "port.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;

static size_t console_row;
static size_t console_column;
static uint8_t console_color;
static uint16_t* console_buffer;

static void console_scroll();
static void console_setcursor(int, int);

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
typedef enum vga_color vga_color_t;

static inline uint8_t vga_entry_color(vga_color_t fg, vga_color_t bg) {
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

void console_initialize(void) {
	console_row = 0;
	console_column = 0;
	console_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	console_buffer = VGA_MEMORY;
    
    uint16_t empty_entry = vga_entry(' ', console_color);
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			console_buffer[index] = empty_entry;
        }
	}
}

static void console_writeat(unsigned char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	console_buffer[index] = vga_entry(c, color);
}

static void console_writechar(char c) {
	unsigned char uc = c;

	if (c == '\n') {
		console_row++;
		console_column = 0;
	} else {
		console_writeat(uc, console_color, console_column, console_row);
		console_column++;
	}

	if (console_column == VGA_WIDTH) {
		console_column = 0;
		if (++console_row == VGA_HEIGHT) {
			console_scroll();
			console_row--;
		}
	}

	console_setcursor(console_column, console_row);
}

void console_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		console_writechar(data[i]);
}

void console_clear() {
  
  size_t buffer_size = VGA_WIDTH * VGA_HEIGHT;
  uint16_t color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  
  for (size_t i = 0; i < buffer_size; i++)
    console_buffer[i] = vga_entry(' ', color);

  console_column = 0;
  console_row = 0;
  console_setcursor(console_column, console_row);
}

static void console_scroll() {
	// todo
}

static void console_setcursor(int col, int row) {
	uint16_t pos = row * VGA_WIDTH + col;
	outb(0x3d4, 0x0f);
	outb(0x3d5, (uint8_t) pos);
	outb(0x3d4, 0x0e);
	outb(0x3d5, (uint8_t) (pos >> 8));
}

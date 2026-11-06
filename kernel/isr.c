#include "isr.h"
#include "debug.h"
#include "io.h"
#include "printk.h"
#include <stdint.h>

// TODO: move to corresponding modules
void panic();

static isr_handler_t isr_routines[256] = {0};

static const char *exception_messages[32] = {
    "Division by zero",
    "Debug exception",
    "Non maskable interrupt",
    "Breakpoint exception",
    "Detected overflow",
    "Out of bounds exception",
    "Invalid opcode exception",
    "No coprocessor exception",
    "Double fault",
    "Coprocessor segment overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown interrupt exception",
    "Coprocessor fault",
    "Alignment check exception",
    "Machine check exception",
    "Interrupt 19",
    "Interrupt 20",
    "Interrupt 21",
    "Interrupt 22",
    "Interrupt 23",
    "Interrupt 24",
    "Interrupt 25",
    "Interrupt 26",
    "Interrupt 27",
    "Interrupt 28",
    "Interrupt 29",
    "Interrupt 30",
    "Interrupt 31",
};

void isr_register_handler(uint8_t int_no, isr_handler_t handler) { isr_routines[int_no] = handler; }

void isr_handler(registers_t regs) {
    uint32_t int_no = regs.int_no;
    isr_handler_t handler = isr_routines[int_no];

    if (handler != 0) {
        handler(regs);
    } else {
        printk("Unhandled exception: %s\n", exception_messages[int_no]);
        debug_registers(regs);
        panic();
    }
}

void irq_handler(registers_t regs) {
    uint32_t int_no;
    isr_handler_t handler;

    printk("b");

    int_no = regs.int_no;
    handler = isr_routines[int_no];

    if (int_no >= IRQ8) {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);

    if (handler != 0) {
        handler(regs);
    }
}

// TODO: improve
void panic() {
    printk("Kernel panic!!!");
    while (1)
        ;
}

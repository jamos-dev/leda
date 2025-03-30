#include <stdint.h>

#include "console.h"
#include "gdt.h"
#include "idt.h"
#include "multiboot.h"
#include "printk.h"

typedef void (*func_t)();

void kmain() {

  console_initialize();
  console_clear();
  printk("Console initialized\n");

  gdt_init();
  printk("GDT initialized\n");

  idt_init();
  printk("IDT initialized\n");

  printk("Generating fault\n");
  func_t func = (func_t)100501;
  func();

  printk("Fault handling failed\n");

  while (1)
    ;
}

static void debug(multiboot_info_t *mb_info) {
  printk("Memory lower: %x\n", mb_info->mem_lower);
  printk("Memory upper: %x\n", mb_info->mem_upper);
  printk("Boot loader name: %s\n", mb_info->boot_loader_name);
}

#include <stdint.h>

#include "console.h"
#include "gdt.h"
#include "idt.h"
#include "keyboard.h"
#include "printk.h"

void kmain() {

    console_initialize();
    console_clear();
    printk("Console initialized\n");

    gdt_init();
    printk("GDT initialized\n");

    idt_init();
    printk("IDT initialized\n");

    init_keyboard();
    printk("Keyboard initialized\n");

    while (1)
        ;
}

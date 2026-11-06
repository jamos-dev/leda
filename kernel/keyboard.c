#include "keyboard.h"
#include "isr.h"
#include "printk.h"

void irq_keyboard_handler(registers_t regs) { printk("a"); }

void init_keyboard() { isr_register_handler(IRQ1, irq_keyboard_handler); }

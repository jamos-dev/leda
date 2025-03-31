#include "isr.h"
#include "printk.h"
#include <stdint.h>

// TODO: move to corresponding modules
void debug_info(registers_t regs);
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

void isr_register_handler(uint8_t int_no, isr_handler_t handler) {
  isr_routines[int_no] = handler;
}

void isr_handler(registers_t regs) {
  uint32_t int_no = regs.int_no;
  isr_handler_t handler = isr_routines[int_no];

  if (handler != 0) {
    handler(regs);
  } else {
    printk("Unhandled exception: %s\n", exception_messages[int_no]);
    debug_info(regs);
    panic();
  }
}

void irq_handler(registers_t regs) {}

void debug_info(registers_t regs) {
  printk("===============================================================\n");
  printk("EAX=%x  ESI=%x  DS=%x  CS=%x\n", regs.eax, regs.esi, regs.ds,
         regs.cs);
  printk("EBX=%x  EDI=%x  ES=%x  SS=%x\n", regs.ebx, regs.edi, regs.es,
         regs.ss);
  printk("ECX=%x  EIP=%x  FS=%x\n", regs.ecx, regs.eip, regs.fs);
  printk("EDX=%x  ESP=%x  GS=%x\n", regs.edx, regs.esp, regs.gs);
  printk("EFLAGS=%x\n", regs.eflags);
  printk("===============================================================\n");
}

// TODO: improve
void panic() {
  printk("Kernel panic!!!");
  while (1)
    ;
}

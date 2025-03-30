#include "isr.h"
#include "printk.h"

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

void isr_handler(int int_no, int err_code) {
  printk("  ISR: int_no: %d, err_code: %d, msg: %s\n", int_no, err_code,
         exception_messages[int_no]);
  //  printk("eax=%x, ebx=%x, ecx=%x, edx=%x, esi=%x, edi=%x\n", regs->eax,
  //  regs->ebx, regs->ecx, regs->edx, regs->esi, regs->edi); printk(" ds=%x,
  //  es=%x,  gs=%x,  fs=%x\n", regs->ds, regs->es, regs->gs, regs->fs);
  //  printk("int_no=%d, err_no=%d", regs->int_no, regs->err_code);
  //  printk("eip=%x, cs=%x, eflags=%x, esp=%x, ss=%x", regs->eip, regs->cs,
  //  regs->eflags, regs->esp, regs->ss);
  while (1)
    ;
}

#include "debug.h"
#include "isr.h"
#include "printk.h"

void debug_registers(registers_t regs) {
    printk("===============================================================\n");
    printk("EAX=%x  ESI=%x  DS=%x  CS=%x\n", regs.eax, regs.esi, regs.ds, regs.cs);
    printk("EBX=%x  EDI=%x  ES=%x  SS=%x\n", regs.ebx, regs.edi, regs.es, regs.ss);
    printk("ECX=%x  EIP=%x  FS=%x\n", regs.ecx, regs.eip, regs.fs);
    printk("EDX=%x  ESP=%x  GS=%x\n", regs.edx, regs.esp, regs.gs);
    printk("EFLAGS=%x\n", regs.eflags);
    printk("===============================================================\n");
}

#ifndef LEDA_ISR_H
#define LEDA_ISR_H

#include <stdint.h>

struct registers {
  uint32_t edi, esi, ebp, ebx, ecx, edx, eax, eip, cs, eflags, esp, ss;
};

typedef struct registers registers_t;

typedef void (*isr_handler_t)(int int_no, int err);

#endif

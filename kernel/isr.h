#ifndef LEDA_ISR_H
#define LEDA_ISR_H

#include <stdint.h>

struct registers {
  uint32_t gs, fs, es, ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, cs, eflags, user_esp, ss;
};

typedef struct registers registers_t;

typedef void (*isr_handler_t)(registers_t reg, int int_no, int err);

#endif

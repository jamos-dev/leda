#ifndef LEDA_CONSOLE_H
#define LEDA_CONSOLE_H

#include <stddef.h>

void console_initialize();
void console_clear();
void console_write();
void console_write(const char* data, size_t size);

#endif

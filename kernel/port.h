#ifndef LEDA_PORT_H_
#define LEDA_PORT_H_

#include <stddef.h>
#include <stdint.h>

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t value);


#endif

#include <stdint.h>

#include "gdt.h"

extern void gdt_load(uint32_t);
static void gdt_set_gate(uint32_t, uint32_t, uint32_t, uint8_t, uint8_t);

gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt_ptr;

void gdt_init() {
	
	gdt_ptr.limit = sizeof(gdt_entry_t) * 5 - 1;
	gdt_ptr.base = (uint32_t) &gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

	gdt_load((uint32_t) &gdt_ptr);
}

static void gdt_set_gate(uint32_t number, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
	
	gdt_entries[number].base_low = base & 0xFFFF;
	gdt_entries[number].base_middle = (base >> 16) & 0xFF;
	gdt_entries[number].base_high = (base >> 24) & 0xFF;

	gdt_entries[number].limit_low = limit & 0xFFFF;
	gdt_entries[number].granularity = (limit >> 16) & 0x0F;

	gdt_entries[number].granularity |=  granularity & 0xF0;
	gdt_entries[number].access = access;
}

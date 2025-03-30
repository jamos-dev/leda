SOURCES_C=$(patsubst %.c,%.o,$(wildcard kernel/*.c))
SOURCES_ASM=$(patsubst %.asm,%.o,$(wildcard kernel/*.asm))

CC=i686-elf-gcc
LD=i686-elf-ld
ASM=nasm
CFLAGS=-std=gnu99 -nostdlib -fno-builtin -ffreestanding -m32 -Wall -Wextra # -Wpedantic
LDFLAGS=-melf_i386 -nostdlib
ASFLAGS=-felf
QEMU=qemu-system-i386

KERNEL=kernel.bin
OBJ=$(SOURCES_ASM) $(SOURCES_C)

.PHONY: all clear

all: $(OBJ) link

clean:
	-rm -f kernel/*.o $(KERNEL)

link:
	@echo "(LD)" $(KERNEL)
	@$(LD) $(LDFLAGS) -T kernel/linker.ld -o $(KERNEL) $(OBJ)

kernel/%.o:kernel/%.c
	@echo "(CC)" $<
	@$(CC) $(CFLAGS) $< -c -o $@

kernel/%.o:kernel/%.asm
	@echo "(ASM)" $<
	@$(ASM) $(ASFLAGS) $< -o $@

qemu:
	$(QEMU) -kernel $(KERNEL)

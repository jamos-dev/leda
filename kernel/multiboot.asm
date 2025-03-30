ALGN  		equ 1 << 0
MEMINFO 	equ 1 << 1
FLAGS 		equ ALGN | MEMINFO
MAGIC 		equ 0x1BADB002
CHECKSUM	equ - (MAGIC + FLAGS)

extern kmain

section .multiboot
align 4

dd	MAGIC
dd	FLAGS
dd	CHECKSUM

section .bss
align 16

stack_bottom: 
resb 16384
stack_top:

section .text
global _start
	
_start:
	mov	esp, stack_top

	; call 	_init
    cli
    push    ebx
	call 	kmain

	cli
hang:	hlt
	jmp hang


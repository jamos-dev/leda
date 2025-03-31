global memset
global strlen
global gdt_load
global idt_load

memset:
    mov edi, [esp + 4]
    mov al, [esp + 8]
    mov ecx, [esp + 12]

    rep stosb

    mov ax, [esp + 8]

    ret

strlen:
    mov esi, [esp + 4]
    xor ecx, ecx
    cld

.next:
    lodsb
    inc ecx
    or al, al
    jnz .next

    mov eax, ecx
    dec eax

    ret

gdt_load:
	mov	eax, [esp + 4]
	lgdt [eax]

	mov	ax, 0x10
	mov	ds, ax
	mov	es, ax
	mov	fs, ax
	mov	gs, ax
	mov	ss, ax

	jmp	0x08:.flush

.flush:
	ret

idt_load:
    mov eax, [esp + 4]
    lidt [eax]
    ret


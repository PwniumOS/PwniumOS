[BITS 32]

section multiboot
ALIGN 4 ; multiboot header
MULTIBOOT_PAGE_ALIGN	equ 1<<0
MULTIBOOT_MEMORY_INFO	equ 1<<1
MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO
MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
dd MULTIBOOT_HEADER_MAGIC
dd MULTIBOOT_HEADER_FLAGS
dd MULTIBOOT_CHECKSUM


section .text
	GLOBAL start
	EXTERN main

	start:
	mov esp, stack
	cli
	push esp ;
	push eax ;
	push ebx ; multiboot header
	call main ; main(multiboot*, int eax, void *esp)

	hang:
	nop
	jmp hang


global idt_load
extern idt_p
idt_load:
	lidt [idt_p]
	ret

global gdt_load
extern gp
gdt_load:
	lgdt [gp]
	mov ax, 0x10
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov gs, ax
	mov fs, ax
	jmp 0x08:load_cd ; code segment can't be loaded otherwise
	load_cd:
	ret

section .bss
	resb 8192  ; 8KB
stack:

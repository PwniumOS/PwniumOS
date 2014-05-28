[BITS 32]

SECTION multiboot
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
	hlt
    jmp $


section .bss
	resb 8192  ; 8KB
stack:

%macro ISR_NOERRCODE 1
	[global isr%1]
	isr%1:
		push byte 0
		push byte %1
		jmp call_interrupt_handler
%endmacro

%macro ISR_ERRCODE 1
	[global isr%1]
	isr%1:
		push byte %1
		jmp call_interrupt_handler
%endmacro

%macro IRQ_NOERRCODE 1
	[global irq%1]
	irq%1:
		push byte 0
		push byte %1
		jmp call_irq_handler
%endmacro

%macro IRQ_ERRCODE 1
	[global irq%1]
	irq%1:
		push byte %1
		jmp call_irq_handler
%endmacro


ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_ERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

IRQ_NOERRCODE 0

extern interrupt_handler
call_interrupt_handler:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp   ; Push us the stack so that interrupt_handler receive a pointer as a parametre
    push eax
    mov eax, interrupt_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

extern irq_handler
call_irq_handler:
	pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, irq_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

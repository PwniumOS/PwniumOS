global isr0 ; divide-error
isr0:
    push 0x0
    push 0x0
    jmp call_interrupt_handler

global isr1
isr1:
    push 0x0
    push 0x1
    jmp call_interrupt_handler

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

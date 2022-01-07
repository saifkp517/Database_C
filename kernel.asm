
bits 32                         ;nasm directive 32 bit
section .text                   ;asm code goes here

    ;specifications for multi booting to load our kernel from boot menu
    align 4
    dd 0x1BADB002
    dd 0x00
    dd - (0x1BADB002 + 0x00)

    global _start:              ;
        extern kmain            ;kmain is gonna be defined in the c file

    _start:
        cli                     ;blocks interrupts
        mov esp, stack_space    ;set stack pointer
        call kmain              
        hlt                     ;halting the CPU

section .bss
    resb 8192                   ;8kb for the stack
    stack_space:


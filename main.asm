[bits 32]
section .text
        align 4
        dd 0x1BADB002              ; Multiboot magic
        dd 0x00                    ; Flags
        dd -(0x1BADB002 + 0x00)    ; Checksum

global _start
extern kernel_main

_start:
        call kernel_main           ; Jump to your or my C code
.hang:
    hlt          ; Sleep until next interrupt
    jmp .hang 

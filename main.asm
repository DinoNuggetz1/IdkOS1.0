[BITS 16]
[org 7c00]

KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE], dl

mov bp 0x9000
mov sp, bo

call lod_kernl

jmp $

[BITS 16]
lod_kernl:
mov bx, KERNEL_OFFSET
mov dh, 2
mov dl, [BOOT_DRIVE]
call dsk_lod
ret
[BITS 32]
BEGIN32BIT:
call KERNEL_OFFSET
jmp $

BOOT_DRIVE db 0

times 510 - ($-$$) db 0

; magic number
dw 0xaa55
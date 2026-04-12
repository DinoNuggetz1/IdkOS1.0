#!/bin/bash
set -e

echo "This software is distributed without warranty of any kind, Use at your own risk"
echo "In order to compile this code you must have the following tools: GCC i386, Nasm(Netwide Assembler), Qemu(Quick Emulator), and Grub2(Grub-mkrescue) if you cannot install these tool or prefer not to there is a precompiled iso in the releases section of this repository"

read -p "Do you want to proceed? (y/n): " response

case "$response" in
    [yY]*)
        rm -rf build
        mkdir -p build/iso/boot/grub
        nasm -f elf32 main.asm -o boot.o
        gcc -m32 -ffreestanding -c kernel.c -o kernel.o
        ld -m elf_i386 -T linker.ld boot.o kernel.o -o kernel.bin
        cp kernel.bin build/iso/boot/
        cp grub.cfg build/iso/boot/grub/
        grub-mkrescue -o GOLD_OS.iso build/iso
        rm *.o
        rm -rf build
        rm *.bin
        qemu-system-i386 -cdrom GOLD_OS.iso
        echo "Build complete: GOLD_OS.iso created."
        ;;
    [nN]*)
        echo "Aborting."
        exit 1
        ;;
    *)
        echo "Invalid input."
        exit 1
        ;;
esac

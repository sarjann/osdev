#!/bin/bash
i686-elf-gcc -T kernel/linker.ld -o target/os.bin -ffreestanding -O2 -nostdlib target/boot_asm.o\
    target/kernel.o\
    target/descriptors_asm.o\
    target/descriptors.o\
    target/vga.o\
    target/ps2.o\
    # ../libgc/libgc.h\

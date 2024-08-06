#!/bin/bash
i686-elf-gcc -T linker.ld -o ../target/os.bin -ffreestanding -O2 -nostdlib ../target/boot.o\
    ../target/kernel.o\
    ../target/isr_wrapper.o\
    ../target/interrupt.o\
    ../target/ps2.o\
    # ../libgc/libgc.h\
    -lgcc

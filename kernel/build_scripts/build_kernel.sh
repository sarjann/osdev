#!/bin/bash
i686-elf-gcc kernel.c -o ../target/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -c

i686-elf-gcc src/drivers/ps2.c -o ../target/ps2.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -c
i686-elf-gcc interrupt.c -o ../target/interrupt.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -c

# NASM
nasm -felf32 isr_wrapper.asm -o ../target/isr_wrapper.o

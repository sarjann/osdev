#!/bin/bash
i686-elf-gcc kernel/kernel.c -o target/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -c

i686-elf-gcc kernel/src/drivers/ps2.c -o target/ps2.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -c
i686-elf-gcc kernel/src/drivers/vga.c -o target/vga.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -c
i686-elf-gcc kernel/descriptors.c -o target/descriptors.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -c

# NASM
nasm -felf32 kernel/descriptors.asm -o target/descriptors_asm.o

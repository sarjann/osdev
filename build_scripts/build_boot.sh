#!/bin/bash
nasm -felf32 kernel/boot.asm -o target/boot_asm.o

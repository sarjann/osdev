#!/bin/bash

# Make target directory if doesn't exist
rm -rf target
rm -rf isodir

mkdir -p isodir/boot/grub
mkdir -p target

echo "Building boot"
./build_scripts/build_boot.sh

echo "Building kernel"
./build_scripts/build_kernel.sh

echo "Linking"
./build_scripts/build_linker.sh

echo "Check multiboot"
if grub-file --is-x86-multiboot target/os.bin; then
  echo "Has multiboot"
else
  echo "Not multiboot"
  exit 1
fi

echo "Creating iso"
cp target/os.bin isodir/boot/os.bin
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o target/os.iso isodir

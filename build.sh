#!/bin/bash

# Build script from OSDev wiki 32-bit bare bones example
# which I kindly stole as a starting point and I wish to
# use for this operating system i guess idk lol XD lmfao
# Sauce: https://wiki.osdev.org/Bare_Bones

# Requires i686-* GNU tools so add them to PATH
export PATH="$PATH:$HOME/opt/cross/bin"

# Assemble boot.s to provide our entry point into C program
i686-elf-as boot.s -o boot.o

# Assemble our operating system's kernel!
#
# -- Use C99 for the minimal standard which is confirmed
#    to work on most compilers and also supports all our
#    extensions used!
i686-elf-gcc -c osdev_vga.c -o osdev_vga.o -std=gnu99 -ffreestanding -Wall -Wextra
i686-elf-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -Wall -Wextra

# Link the kernel to create a .bin file
#
# -- This part uses linker.ld which is a script provided
#    by the OSDev wiki and links our program into the
#    optimal format for x86_64 UEFI or x86_32 BIOS or
#    x86_64 BIOS to boot!
i686-elf-gcc -T linker.ld -o myos.bin -ffreestanding -nostdlib boot.o kernel.o osdev_vga.o -lgcc

# Verify our file is multiboot.
#
# -- This part is purely optional since it most likely is
#    but functions as a way to make sure just in case our
#    toolchain is messed up.
if grub-file --is-x86-multiboot myos.bin; then
  echo multiboot confirmed
else
  echo the file is not multiboot
fi

# Make our CD
mkdir -p isodir/boot/grub
cp myos.bin isodir/boot/myos.bin
cp grub.cfg isodir/boot/grub/grub.cfg
sudo grub-mkrescue -d /usr/lib/grub/i386-pc -o myos.iso isodir

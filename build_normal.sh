#!/bin/bash
# build_normal.sh - Compila la versión normal de YanisMinesitoo OS
set -e
KERNEL=kernel_normal.c
OUT=kernel_normal.bin
ISO=YanisMinesitooOS_normal.iso
WORKDIR="$PWD/build_normal"
ISO_DIR="$WORKDIR/iso"

mkdir -p "$ISO_DIR/boot/grub"

# Compilar kernel normal
x86_64-elf-gcc -ffreestanding -c $KERNEL -o kernel_normal.o
nasm -f elf64 kernel_entry.asm -o kernel_entry.o
x86_64-elf-ld -T linker.ld kernel_entry.o kernel_normal.o -o $OUT

# Copiar archivos
cp $OUT "$ISO_DIR/boot/kernel.bin"
cp grub.cfg "$ISO_DIR/boot/grub/grub.cfg"

# Crear la ISO
cd "$WORKDIR"
grub-mkrescue -o "$ISO" iso
cd "$OLDPWD"

echo "\nISO normal creada: $WORKDIR/$ISO"

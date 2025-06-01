#!/bin/bash
# build_portable.sh - Compila la versión portable de YanisMinesitoo OS
set -e
KERNEL=kernel_portable.c
OUT=kernel_portable.bin
ISO=YanisMinesitooOS_portable.iso
WORKDIR="$PWD/build_portable"
ISO_DIR="$WORKDIR/iso"

mkdir -p "$ISO_DIR/boot/grub"

# Compilar kernel portable
x86_64-elf-gcc -ffreestanding -c $KERNEL -o kernel_portable.o
nasm -f elf64 kernel_entry.asm -o kernel_entry.o
x86_64-elf-ld -T linker.ld kernel_entry.o kernel_portable.o -o $OUT

# Copiar archivos
cp $OUT "$ISO_DIR/boot/kernel.bin"
cp grub.cfg "$ISO_DIR/boot/grub/grub.cfg"

# Crear la ISO
cd "$WORKDIR"
grub-mkrescue -o "$ISO" iso
cd "$OLDPWD"

echo "\nISO portable creada: $WORKDIR/$ISO"

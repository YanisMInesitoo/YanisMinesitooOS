#!/bin/bash
# build.sh - Script para compilar tu kernel propio y crear una ISO de arranque mínima para x86_64

set -e

WORKDIR="$PWD/build"
ISO_DIR="$WORKDIR/iso"

# 1. Preparar directorios
mkdir -p "$ISO_DIR/boot/grub"

# 2. Compilar el kernel propio
x86_64-elf-gcc -ffreestanding -c kernel.c -o kernel.o
nasm -f elf64 kernel_entry.asm -o kernel_entry.o
x86_64-elf-ld -T linker.ld kernel_entry.o kernel.o -o kernel.bin

# 3. Copiar kernel y grub.cfg a la estructura de la ISO
cp kernel.bin "$ISO_DIR/boot/kernel.bin"
cp grub.cfg "$ISO_DIR/boot/grub/grub.cfg"

# 4. Crear la ISO de arranque
cd "$WORKDIR"
grub-mkrescue -o YanisMinesitooOS.iso iso

cd "$OLDPWD"
echo "\n¡ISO creada exitosamente! Archivo: $WORKDIR/YanisMinesitooOS.iso"
echo "Para probarla en QEMU ejecuta:"
echo "qemu-system-x86_64 -cdrom $WORKDIR/YanisMinesitooOS.iso"

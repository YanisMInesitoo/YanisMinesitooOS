@echo off
REM build_normal.bat - Compila la versión normal de YanisMinesitoo OS
setlocal
set KERNEL=kernel_normal.c
set OUT=kernel_normal.bin
set ISO=YanisMinesitooOS_normal.iso
set WORKDIR=%CD%\build_normal
set ISO_DIR=%WORKDIR%\iso

if not exist %WORKDIR% mkdir %WORKDIR%
if not exist %ISO_DIR%\boot\grub mkdir %ISO_DIR%\boot\grub

REM Compilar kernel normal
x86_64-elf-gcc -ffreestanding -c %KERNEL% -o kernel_normal.o
nasm -f elf64 kernel_entry.asm -o kernel_entry.o
x86_64-elf-ld -T linker.ld kernel_entry.o kernel_normal.o -o %OUT%

REM Copiar archivos
copy %OUT% %ISO_DIR%\boot\kernel.bin >nul
copy grub.cfg %ISO_DIR%\boot\grub\grub.cfg >nul

REM Crear la ISO
cd %WORKDIR%
grub-mkrescue -o %ISO% iso
cd %CD%

echo.
echo ISO normal creada: %WORKDIR%\%ISO%
endlocal

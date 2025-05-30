all: kernel.bin iso

kernel.bin: kernel_entry.asm kernel.c linker.ld
	 x86_64-elf-gcc -ffreestanding -c kernel.c -o kernel.o
	 nasm -f elf64 kernel_entry.asm -o kernel_entry.o
	 x86_64-elf-ld -T linker.ld kernel_entry.o kernel.o -o kernel.bin

iso: kernel.bin grub.cfg
	 mkdir -p isodir/boot/grub
	 cp kernel.bin isodir/boot/kernel.bin
	 cp grub.cfg isodir/boot/grub/grub.cfg
	 grub-mkrescue -o YanisMinesitooOS.iso isodir

clean:
	 rm -rf *.o *.bin isodir YanisMinesitooOS.iso
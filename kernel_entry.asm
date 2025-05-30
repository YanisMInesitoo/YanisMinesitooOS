; filepath: c:\Users\Yanis\Documents\YanisMinesitoo OS\kernel_entry.asm
global _start
extern kernel_main
section .text
_start:
    call kernel_main
    cli
    hlt
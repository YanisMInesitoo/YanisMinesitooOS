/* filepath: c:\Users\Yanis\Documents\YanisMinesitoo OS\linker.ld */
ENTRY(_start)
SECTIONS
{
  . = 1M;
  .text : { *(.text*) }
  .data : { *(.data*) }
  .bss  : { *(.bss*)  }
}
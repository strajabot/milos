OUTPUT_ARCH( "riscv" )
ENTRY( entry )


SECTIONS
{
  . = 0x80000000;
  __kernel_start = .;

  __text_start = .;
  .text : {
    *(.entry)
    . = ALIGN(0x1000);
    *(.text .text.*)
    . = ALIGN(0x1000);
    
  }
  __text_end = .;

  __rodata_start = .;
  .rodata : {
    *(.srodata .srodata.*)
    . = ALIGN(16);
    *(.rodata .rodata.*)
    . = ALIGN(16);
  }
  __rodata_end = .;

  __data_start = .;
  .data : {
    __global_pointer = . + 0x800;
    *(.sdata .sdata.*)
    . = ALIGN(16);
    *(.data .data.*)
    . = ALIGN(16);
  }
  __data_end = .;

  __bss_start = .;
  .bss : {
    *(.sbss .sbss.*)
    . = ALIGN(16);
    *(.bss .bss.*)
    . = ALIGN(16);
  }
  __bss_end = .;

  . = ALIGN(0x1000);

  __stack_space = .;
  __stack_size = 0x1000;

  . += 0x10000;

  __kernel_end = .;

  . = ALIGN(0x1000);
  __heap_start = .;

  __heap_end = __kernel_start + 0x10000000;

}

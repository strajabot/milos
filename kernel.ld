OUTPUT_ARCH( "riscv" )
ENTRY( entry )


SECTIONS
{
  . = 0x80000000;
  kernel_start = .;

  text_start = .;
  .text : {
    *(.entry)
    . = ALIGN(0x1000);
    *(.text .text.*)
    . = ALIGN(0x1000);
    
  }
  text_end = .;

  .rodata : {
    . = ALIGN(16);
    *(.srodata .srodata.*)
    . = ALIGN(16);
    *(.rodata .rodata.*)
  }

  . = ALIGN(16);
  data_start = .;
  .data : {
    *(.sdata .sdata.*)
    . = ALIGN(16);
    *(.data .data.*)
  }
  data_end = .;

  . = ALIGN(16);
  bss_start = .;
  .bss : {
    *(.sbss .sbss.*)
    . = ALIGN(16);
    *(.bss .bss.*)
  }
  bss_end = .;

  kernel_end = .;
}

OUTPUT_ARCH( "riscv" )

ENTRY ( _start )

/* RAM starts at 0x80000000 on QEMU's RISC-V virt board */
MEMORY {
  ram (wxa) : ORIGIN = 0x80000000, LENGTH = 128M
}

/* ELF Program Headers */
PHDRS {
  text PT_LOAD ;
  data PT_LOAD ;
  bss  PT_LOAD ;
}

SECTIONS {
  /* Contains executable instructions and read-only data */
  .text : {
    *(.text)
  } >ram :text

  /* Contains initialized data */
  .data : {
    *(.text)
  } >ram :data

  /* Contains uninitialized data */
  .bss : {
    *(.bss)
  } >ram :data

  /* Stack */
  . = ALIGN(0x80) ;
  STACK_BOTTOM = . ;
  . += 0x8000 ;
  STACK_TOP = . ;
}
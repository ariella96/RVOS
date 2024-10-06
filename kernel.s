.section .text
.global _kernel

_kernel:
  la a0, hello
  jal write_uart
  
  j .

.section .data

hello: .ascii "Hello, world!\n\x00"

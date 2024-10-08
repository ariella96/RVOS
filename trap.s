.section .text
.global _trap

.balign 4 /* Align trap vector to a 4-byte boundary */
_trap:
  la a0, trap_message
  j panic

.section .data

trap_message : .ascii "Trap encountered.\n\x00"

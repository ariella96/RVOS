SHELL = /bin/sh

# Use the RISC-V GNU Compiler Toolchain by default
AS = riscv64-elf-as
LD = riscv64-elf-ld

# Default to building kernel.elf
.PHONY : all
all : kernel.elf

kernel.elf : kernel.o
	$(LD) $(LDFLAGS) -T $(srcdir)link.ld $< -o $@

kernel.o : boot.s
	$(AS) $(ASFLAGS) $< -o $@

.PHONY : clean
clean :
	rm kernel.elf kernel.o
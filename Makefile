SHELL = /bin/sh

# Use the RISC-V GNU Compiler Toolchain by default
AS = riscv64-elf-as
LD = riscv64-elf-ld

# Default to building kernel.elf
.PHONY : all
all : kernel.elf

kernel.elf : boot.o trap.o kernel.o
	$(LD) $(LDFLAGS) -T $(srcdir)link.ld $(srcdir)boot.o $(srcdir)trap.o $(srcdir)kernel.o -o $@

boot.o : boot.s
	$(AS) $(ASFLAGS) $< -o $@

trap.o : trap.s
	$(AS) $(ASFLAGS) $< -o $@

kernel.o : kernel.s
	$(AS) $(ASFLAGS) $< -o $@

.PHONY : run
run :
	qemu-system-riscv64 -machine virt -cpu rv64i,sv39=off,zicsr=on -m 128M -nographic -serial mon:stdio -bios none -kernel kernel.elf

.PHONY : clean
clean :
	rm kernel.elf boot.o trap.o kernel.o
SHELL = /bin/sh

# Use the RISC-V GNU Compiler Toolchain by default
CC = riscv64-elf-gcc
AS = riscv64-elf-as
LD = riscv64-elf-ld

SDIR = src
IDIR = inc
BDIR = build
S_SRCS = $(wildcard $(SDIR)/*.s)
C_SRCS = $(wildcard $(SDIR)/*.c)
OBJS = $(S_SRCS:$(SDIR)/%.s=$(BDIR)/%_s.o) $(C_SRCS:$(SDIR)/%.c=$(BDIR)/%.o)
CFLAGS = -I $(IDIR) -mcmodel=medany -march=rv64izicsr -mabi=lp64
ASFLAGS = -march=rv64izicsr -mabi=lp64

# Default to building kernel.elf
.PHONY : all
all : clean build kernel.elf

.PHONY : build
build:
	mkdir build

kernel.elf : $(OBJS)
	$(LD) $(LDFLAGS) -T link.ld $(OBJS) -o $@

$(BDIR)/%.o : $(SDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BDIR)/%_s.o : $(SDIR)/%.s
	$(AS) $(ASFLAGS) $< -o $@

.PHONY : run
run :
	qemu-system-riscv64 -machine virt -cpu rv64i,sv39=off,zicsr=on -m 128M -nographic -serial mon:stdio -bios none -kernel kernel.elf

.PHONY : clean
clean :
	rm -rf $(BDIR)
	rm -f kernel.elf
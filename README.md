
# RVOS

A simple bootloader, kernel, and OS for RISC-V. Built for the purpose of
learning RISC-V assembly and operating system design.

## Target

Code will target the ['virt' Generic Virtual Platform (virt)](https://www.qemu.org/docs/master/system/riscv/virt.html) board of QEMU's [RISC-V System emulator](https://www.qemu.org/docs/master/system/target-riscv.html), with a single RV64I core with Zicsr extension.

## Building

Requires the [RISC-V GNU Compiler Toolchain](https://github.com/riscv-collab/riscv-gnu-toolchain).

Build using make:

```sh
  make all
```

## Running

Requires QEMU's RISC-V System emulator.

Run using make:

```sh
  make run
```

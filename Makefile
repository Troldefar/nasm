ASM = nasm
CC = gcc
BOOTSTRAP_FILE = bootstrap.asm
INIT_KERNEL_FILES = starter.asm
KERNEL_FILES = main.c
KERNEL_FLAGS = -Wall -m32 -c -ffreestanding -fno-asynchronous-unwind-tables -fno-pie
KERNEL_OBJECT = -o kernel.elf

build: \
    $(BOOTSTRAP_FILE) $(KERNEL_FILES) $(INIT_KERNEL_FILES) \
    $(ASM) -f bin $(BOOTSTRAP_FILE) -o bootstrap.o \
    $(ASM) -f elf32 $(INIT_KERNEL_FILES) -o starter.o \
    $(CC) $(KERNEL_FLAGS) $(KERNEL_FILES) $(KERNEL_OBJECT) \
    ld -melf_i386 -T linker.ld starter.o kernel.elf -o troldefarkernel.elf \
    objcopy -O binary troldefarkernel.elf troldefarkernel.bin \
    dd if=bootstrap.o of=kernel.img \
    dd seek=1 conv=sync if=troldefarkernel.bin of=kernel.img bs=512 count=5 \
    dd seek=6 conv=sync if=/dev/zero of=kernel.img bs=512 count=2046 \
    qemu-system-x86_64 -s kernel.img

clean: \
    rm -f bootstrap.o starter.o kernel.elf troldefarkernel.elf troldefarkernel.bin kernel.img

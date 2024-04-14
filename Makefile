ASM = nasm
CC = gcc
BOOTSTRAP_FILE = bootstrap.asm
INIT_KERNEL_FILES = starter.asm
KERNEL_FILES = main.c
KERNEL_FLAGS = -Wall -m32 -c -ffreestanding -fno-asynchronous-unwind-tables -fno-pie
KERNEL_OBJECT = -o kernel.elf

BOOTLOADER_DIR = src/bootloader/
FILESYSTEM_DIR = src/filesystem/
DISK_DIR = src/disk/
PROCESS_DIR = src/process/
SCHEDULER_DIR = src/scheduler/
SYSTEM_DIR = src/system/
UTILS_DIR = src/utils/
MEMORY_DIR = src/memory/

build: \
    $(BOOTSTRAP_FILE) $(KERNEL_FILES) \
    $(ASM) -f bin $(BOOTSTRAP_FILE) -o bootstrap.o \
    $(ASM) -f elf32 $(INIT_KERNEL_FILES) -o starter.o \
    $(CC) $(KERNEL_FLAGS) $(KERNEL_FILES) $(KERNEL_OBJECT) \
    $(CC) $(KERNEL_FLAGS) $(UTILS_DIR)screen.c -o screen.elf \
    $(CC) $(KERNEL_FLAGS) $(PROCESS_DIR) process.c -o process.elf \
    $(CC) $(KERNEL_FLAGS) $(SCHEDULER_DIR)scheduler.c -o scheduler.elf \
    $(CC) $(KERNEL_FLAGS) $(MEMORY_DIR)heap.c -o heap.elf \
    $(CC) $(KERNEL_FLAGS) $(MEMORY_DIR)paging.c -o paging.elf \
    $(CC) $(KERNEL_FLAGS) $(DISK_DIR)ata.c -o ata.elf \
    $(CC) $(KERNEL_FLAGS) $(UTILS_DIR)str.c -o str.elf \
    $(CC) $(KERNEL_FLAGS) $(FILESYSTEM_DIR)filesystem.c -o filesystem.elf \
    ld -melf_i386 -Tlinker.ld starter.o kernel.elf screen.elf process.elf scheduler.elf heap.elf paging.elf ata.elf str.elf filesystem.elf -o troldefarkernel.elf \
    objcopy -O binary troldefarkernel.elf troldefarkernel.bin \
    dd if=bootstrap.o of=kernel.img \
    dd seek=1 conv=sync if=troldefarkernel.bin of=kernel.img bs=512 count=20 \
    dd seek=21 conv=sync if=/dev/zero of=kernel.img bs=512 count=2046 \
    qemu-system-x86_64 -s kernel.img
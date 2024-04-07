bits 16 ; Real mode for now
extern kernel_main ; Symbol

start:
	mov ax, cs
	mov ds, ax

	call load_gdt
	call init_video_mode ; Use VGA since we'll enter protected mode where BIOS is meh
	call enter_protected_mode
	call setup_interrupts

	call 08h:start_kernel

setup_interrupts:
	ret

load_gtp:
	cli ; Disable maskable interrupts until later before protected mode
	lgdt [gdtr - start]

	ret

enter_protected_mode:
  mov eax, cr0 ; Load target bit into eax
  or eax, 1    ; Bitwise OR it
  mov cr0, eax ; Enable protected mode by copy cr0 imm. 1 into eax and mov int into proper cr

  ret

init_video_mode:
  mov ah, 0h
  mov al, 03h
  int 10h ; Set video mode with correct above operands

  mov ah, 01h ; Disable cursor
  mov cx, 2000h
  int 10h

  ret

bits 32
start_kernel:
  mov eax, 10h
  mov ds, eax
  mov ss, eax
  
  mov eax, 0h
  mov es, eax
  mov fs, eax
  mov gs, eax

  sti ; Reeanble interrupts

  call kernel_main

%include "gdm.asm"

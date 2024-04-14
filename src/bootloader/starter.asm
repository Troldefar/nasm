bits 16 ; Real mode for now
extern page_directory
extern kernel_main ; Symbol
extern interrupt_handler
extern scheduler
extern run_next_process

global load_page_directory
global enable_paging
global dev_write
global dev_write_word
global dev_read

start:
	mov ax, cs
	mov ds, ax

	call load_gdt
	call init_video_mode ; Use VGA since we'll enter protected mode where BIOS is meh
	call enter_protected_mode
	call setup_interrupts
  call load_task_register

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

load_task_register:
  mov ax, 40d ; 40d since (6 entries * 8 bytes) - 8 (since indexing starts at 0)
  ltr ax

  ret

bits 32

dev_write: ; Boot functionality for OUT and IN device drivers with 8 bit ( al )
  push edx
  push eax

  ; Clear

  xor edx, edx
  xor eax, eax

  ; Set parameters

  mov dx, [esp + 12]
  mov al, [esp + 16]

  out dx, al ; Send value of al to dx which enables us to send cmds to a device on some port

  ; Restore previous state

  pop eax
  pop edx

  ret

dev_write_word: ; Boot functionality for OUT and IN device drivers with 16 bits ( ax )
  push edx
  push eax

  ; Clear

  xor edx, edx
  xor eax, eax

  ; Set parameters

  mov dx, [esp + 12]
  mov al, [esp + 16]

  out dx, ax ; Send value of al to dx which enables us to send cmds to a device on some port

  ; Restore previous state

  pop eax
  pop edx

  ret

dev_read: ; Read
  push edx

  ; Clear

  xor edx, edx
  xor eax, eax

  mox dx, [esp + 8]

  in ax, dx

  pop edx
  
  ret

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

load_page_directory:
  mov eax, [page_directory]
  mov cr3, eax

  ret

enable_paging:
  mov eax, cr0
  or eax 80000000h ; Or the value of the cr0 register to switch it to 1 and put it back = paging enabled
  mov cr0, eax

  ret

%include "gdm.asm"
%include "idt.asm"

tss: ; Task state segment
  dd 0
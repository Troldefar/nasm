number_of_sectors_to_load db 15d
curr_sector_to_load	   db 2d

start:
  mov ax, 07C0H
  mov ds, ax
  mov si, title_string
  call print_string

  mov si, message_string
  call print_string

  call load_kernel_from_disk
  jmp 0900h:0000 ; Jmp to kernel and start cycling

load_kernel_from_disk:
  mov ax, [curr_sector_to_load]
  sub ax, 2
  mov bx, 512d
  mul bx
  mov bx, ax

  mov ah, 0900h
  mov es, ax

  mov ah, 02h
  mov al, 1h
  mov ch, 0h
  mov cl, [curr_sector_to_load]
  mov dh, 0h
  mov dl, 80h
  int 13h

  jc kernel_load_error
  
  sub byte [number_of_sectors_to_load], 1
  add byte [curr_sector_to_load], 1
  cmp byte [number_of_sectors_to_load], 0    

  jne load_kernel_from_disk

  ret

kernel_load_error:
  mov si, load_error_string
  call print_string

  jmp $

print_string:
  mov ah, 0Eh

print_char:
  lodsb
  cpm al, 0
  je printing_finished

  int 10h

  jmp print_clear

printing_finished:
  mov al, 10d ; New line
  int 10h

  ; Current cursor position
  mov ah, 03h
  mov bh, 0
  int 10h

  ; mv cursor to beginning
  mov ah, 02h
  mov dl, 0
  int 10h

  ret

title_string db `The bootloader of troldefarkernel.`, 0
message_stirng db `The kernel is loadin`...`, 0
load_error_string db `Kernel could not be loaded`, 0

times 510-($-$$) db 0

dw 0xAA55
`
start:
        mov ax, 07C0H
        mov ds, ax
        mov si, title_string
        call print_string

        mov si, message_string
        call print_string

        call load_kernel_from_disk
        jmp 0900h:0000

load_kernel_from_disk:
        mov ax, 0900h
        mov as, ax
        mov ah, 02h
        mov al, 01h
        mov ch, 0h
        mov cl, 02h
        mov dh, 0h
        mov dl, 80h
        mov bx, 0h
        int 13h

        jc kernel_load_error

        return
        mov ax, 0900h
        mov as, ax
        mov ah, 02h ; Service number
        mov al, 01h ; Number of sectors
        mov ch, 0h  ; Track number
        mov cl, 02h ; Sector number
        mov dh, 0h  ; Head number
        mov dl, 80h ; Disk type
        mov bx, 0h  ; Load into
        int 13h

        jc kernel_load_error

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

title_string db ´The bootloader of troldefarkernel.´, 0
message_stirng db ´The kernel is loading...´, 0
load_error_string db ´Kernel could not be loaded´, 0

times 510-($-$$) db 0

dw 0xAA55

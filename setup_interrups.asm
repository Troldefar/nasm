setup_interrupts:
	call remap_pic
	call load_idt

	ret

remap_pic: ; Routine for changing default mapping on interrupt numbers @ PIC
	mov al, 11h

	; Initialize

	send_init_cmd_to_pic_master:
		out 0x20 al

	send init_cmd_to_pic_slave:
		out 0xa0 al

	; Start from

	make_irq_start_from_intr_32_in_pic_master:
		mov al, 32d
		out 0x21, al

	; Tell master

	tell_pic_master_where_pic_slave_is_connected:
		mov al, 04h
		out 0x21, al

	; Tell slave

	tell_pic_slave_where_pic_master_is_connected:
		mov al, 02h
		out 0xa1, al

	mov al, 01h

	tell_pic_master_the_arch_is_x86:
		out 0x21, al
	
	tell_pic_slave_the_arch_is_x86:
		out 0xa1, al

	; ... ;

	mov al, 0h

	make_pic_master_enable_all_irqs:
		mov 0x21, al	

	make_pic_slave_enable_all_irqs:
		mov 0xa1, al

	ret

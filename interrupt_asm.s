extern pic_acknowledge      ; defined in pic.c
extern handle_interrupt
extern handle_cpu_interrupt

global enable_interrupts
global disable_interrupts
global handle_cpu_int
global handle_pic_int

section .text:

enable_interrupts:
    sti
    ret

disable_interrupts:
    cli
    ret

handle_cpu_int:
    call    handle_cpu_interrupt
    ;mov word [0xB8000], 0x0F43
    iret

handle_pic_int:
	push	eax
	push	ebx
	push	ecx
	push	edx
	push	ebp
	push	esi
	push	edi
    call    handle_interrupt

    ;push    eax
    ;call    pic_acknowledge 
    ;pop     eax

	pop	    edi
	pop	    esi
	pop	    ebp
	pop	    edx
	pop	    ecx
	pop	    ebx
	pop	    eax
    iret

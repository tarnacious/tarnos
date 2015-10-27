#include "fb.h"
#include "serial.h"
#include "gdt.h"
#include "pic.h"
#include "idt.h"
#include "interrupt.h"
#include "multiboot.h"


int kmain(uint32_t info) {
    char newline[] = "";
	writeln(newline);
	clear();

    multiboot_info_t *mbinfo = (multiboot_info_t *) info;


    char mem_upper[] = "Mem upper: ";
	write(mem_upper);
    write_hex32(mbinfo->mem_upper);
	writeln(newline);

    char mem_lower[] = "Mem lower: ";
	write(mem_lower);
    write_hex32(mbinfo->mem_lower);
	writeln(newline);

    char boot_device[] = "boot_device: ";
	write(boot_device);
    write_hex32(mbinfo->boot_device);
	writeln(newline);

	char message[] = "tarnos!";
	writeln(message);

    write_hex32(0xDEADBEEF);

	writeln(newline);

    write_hex16((uint16_t) 0xDEADBEEF);

	writeln(newline);
    write_hex8((uint8_t) 0xDEADBEEF);

	writeln(newline);

	serial_init();
	char log[] = "System started!";
	serial_write(log);

    disable_interrupts();
    gdt_init();
    pic_init();
    idt_init();
    enable_interrupts();

    return 0;
}


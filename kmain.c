#include "fb.h"
#include "serial.h"
#include "gdt.h"
#include "pic.h"
#include "idt.h"
#include "interrupt.h"


int kmain()
{
	clear();
	char message[] = "tarnos!";
	writeln(message);

    write_hex32(0xDEADBEEF);

    char newline[] = "";
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


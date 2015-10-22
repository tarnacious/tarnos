#include "fb.h"
#include "serial.h"
#include "gdt.h"


int kmain()
{
	clear();
	char message[] = "tarnos!";
	writeln(message);

	serial_init();
	char log[] = "System started!";
	serial_write(log);

    gdt_init();

    return 0;
}


#include "fb.h"
#include "serial.h"


int kmain()
{
	clear();
	char message[] = "tarnos!";
	writeln(message);

	serial_init();
	char log[] = "System started!";
	serial_write(log);

    return 0;
}


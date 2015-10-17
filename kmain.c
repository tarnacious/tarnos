#include "fb.h"
#include "serial.h"


int kmain()
{
	clear();
	char message[] = "tarnos";
	writeln(message, 6);

	serial_init();
	char log[] = "hello!";
	serial_write(log, 6);

	for(int i = 0; i < 25; i++) {
		char line[3] = { '0' + (i % 10), ':', ' ' };
		write(line, 3);
		writeln(message, 6);
	}


	char prompt[] = "ok> ";
	write(prompt, 4);
    return 0;
}


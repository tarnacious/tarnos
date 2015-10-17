#include "fb.h"
#include "serial.h"


int kmain()
{
	clear();
	char message[] = "tarnos";
	writeln(message);

	serial_init();
	char log[] = "hello!";
	serial_write(log);

	for(int i = 0; i < 25; i++) {
		char line[3] = { '0' + (i % 10), ':', ' ' };
		write(line);
		writeln(message);
	}


	char prompt[] = "ok> ";
	write(prompt);
    return 0;
}


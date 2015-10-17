#include "fb.h"


int kmain()
{
	clear();
	char message[6] = {'t', 'a', 'r', 'n', 'o', 's'};
	writeln(message, 6);
	for(int i = 0; i < 25; i++) {
		char line[3] = { '0' + (i % 10), ':', ' ' };
		write(line, 3);
		writeln(message, 6);
	}


	char prompt[4] = {'o', 'k', '>', ' '};
	write(prompt, 4);
    return 0;
}


#include "interrupt.h"
#include "fb.h"
#include "pic.h"
#include "keyboard.h"
#include "keyboard_decoder.h"



void handle_interrupt() {
	uint8_t scan_code = kbd_read();
	char character = kbd_scan_code_to_ascii(scan_code);
    char message2[2] = { character, '\0' };
    write(message2);
    pic_acknowledge();
}

void handle_cpu_interrupt() {
    //char message[] = "CPU Interrupt!";
    //writeln(message);
}

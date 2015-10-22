#include "interrupt.h"
#include "fb.h"
#include "pic.h"
#include "keyboard.h"

void handle_interrupt() {
    char message[] = "Interrupt!";
    writeln(message);
	kbd_read();
    pic_acknowledge();
}

void handle_cpu_interrupt() {
    //char message[] = "CPU Interrupt!";
    //writeln(message);
}

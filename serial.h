#ifndef INCLUDE_SERIAL_H
#define INCLUDE_SERIAL_H

void serial_init();
void serial_write_char(unsigned char data);
void serial_write(char* text, short length);

#endif /* INCLUDE_SERIAL_H */

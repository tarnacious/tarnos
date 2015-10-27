#ifndef INCLUDE_FB_H
#define INCLUDE_FB_H
#include "stdint.h"

void write(char* text);
void writeln(char* text);

void write_hex4(uint8_t value);
void write_hex8(uint8_t value);
void write_hex16(uint16_t value);
void write_hex32(uint32_t value);

void clear();

#endif /* INCLUDE_FB_H */

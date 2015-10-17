#include "fb.h"
#include "io.h"

#define FB_GREEN     2
#define FB_DARK_GREY 8

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15


#define FB_NUM_COLS 80
#define FB_NUM_ROWS 25

unsigned short cursor_position;

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos)
{
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT,    pos & 0x00FF);
}

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg)
{
	char *fb = (char *) 0x000B8000;
	fb[i] = c;
	fb[i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
}

unsigned short fb_read(unsigned int i)
{
	short *fb = (short *) 0x000B8000;
    return fb[i];
}

void fb_write(unsigned int i, unsigned short value)
{
	short *fb = (short *) 0x000B8000;
    fb[i] = value;
}

void scroll() {
    for(int i = 0; i < (FB_NUM_COLS * (FB_NUM_ROWS - 1)); i++) {
        fb_write(i, fb_read(i + FB_NUM_COLS));
    }
}

void clear() {
    cursor_position = 0;
    for(int i = 0; i < (FB_NUM_COLS * FB_NUM_ROWS); i++) {
        fb_write(i, (FB_GREEN << 8));
    }
    fb_move_cursor(cursor_position);
}

void write(char* text)
{
    while(*text != '\0') {
		fb_write_cell(cursor_position * 2, *text, 0, FB_GREEN);
		cursor_position++;
        text++;
    }
    fb_move_cursor(cursor_position);
}

void writeln(char* text)
{
    while(*text != '\0') {
		fb_write_cell(cursor_position * 2, *text, 0, FB_GREEN);
		cursor_position++;
        text++;
    }
    int offset = cursor_position % FB_NUM_COLS;
    cursor_position += FB_NUM_COLS - offset;

    // extremely dodgy scrolling
    if (cursor_position > FB_NUM_ROWS * FB_NUM_COLS) {
        scroll();
        cursor_position = (FB_NUM_ROWS - 1) * FB_NUM_COLS;

        // clear the last line
        for(int i = 0; i < FB_NUM_COLS; i++) {
            fb_write( (FB_NUM_ROWS-1) * FB_NUM_COLS - 2 + i, (FB_GREEN << 8));
        }
    }

    fb_move_cursor(cursor_position);
}

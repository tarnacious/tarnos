#include "keyboard_decoder.h"
#include "stdint.h"

#define KBD_DATA_PORT   0x60

/* Alphabet */
#define KBD_SC_A        0x1e
#define KBD_SC_B        0x30
#define KBD_SC_C        0x2e
#define KBD_SC_D        0x20
#define KBD_SC_E        0x12
#define KBD_SC_F        0x21
#define KBD_SC_G        0x22
#define KBD_SC_H        0x23
#define KBD_SC_I        0x17
#define KBD_SC_J        0x24
#define KBD_SC_K        0x25
#define KBD_SC_L        0x26
#define KBD_SC_M        0x32
#define KBD_SC_N        0x31
#define KBD_SC_O        0x18
#define KBD_SC_P        0x19
#define KBD_SC_Q        0x10
#define KBD_SC_R        0x13
#define KBD_SC_S        0x1f
#define KBD_SC_T        0x14
#define KBD_SC_U        0x16
#define KBD_SC_V        0x2f
#define KBD_SC_W        0x11
#define KBD_SC_X        0x2d
#define KBD_SC_Y        0x15
#define KBD_SC_Z        0x2c

/* Numeric keys */
#define KBD_SC_1        0x02
#define KBD_SC_2        0x03
#define KBD_SC_3        0x04
#define KBD_SC_4        0x05
#define KBD_SC_5        0x06
#define KBD_SC_6        0x07
#define KBD_SC_7        0x08
#define KBD_SC_8        0x09
#define KBD_SC_9        0x0a
#define KBD_SC_0        0x0b

/* Special keys */
#define KBD_SC_ENTER    0x1c
#define KBD_SC_SPACE    0x39
#define KBD_SC_BS       0x0e
#define KBD_SC_LSHIFT   0x2a
#define KBD_SC_RSHIFT   0x36
#define KBD_SC_DASH     0x0c
#define KBD_SC_EQUALS   0x0d
#define KBD_SC_LBRACKET 0x1a
#define KBD_SC_RBRACKET 0x1b
#define KBD_SC_BSLASH   0x2b
#define KBD_SC_SCOLON   0x27
#define KBD_SC_QUOTE    0x28
#define KBD_SC_COMMA    0x33
#define KBD_SC_DOT      0x34
#define KBD_SC_FSLASH   0x35
#define KBD_SC_TILDE    0x29
#define KBD_SC_CAPSLOCK 0x3a

uint8_t is_lshift_down       = 0;
uint8_t is_rshift_down       = 0;
uint8_t is_caps_lock_pressed = 0;

void toggle_left_shift(void)
{
    is_lshift_down = is_lshift_down ? 0 : 1;
}

void toggle_right_shift(void)
{
    is_rshift_down = is_rshift_down ? 0 : 1;
}

void toggle_caps_lock(void)
{
    is_caps_lock_pressed = is_caps_lock_pressed ? 0 : 1;
}


uint8_t handle_caps_lock(uint8_t ch)
{
    if (ch >= 'a' && ch <= 'z') {
        return ch + 'A' - 'a';
    }
    return ch;
}

uint8_t handle_shift(uint8_t ch)
{
    // Alphabetic characters
    if (ch >= 'a' && ch <= 'z') {
        return ch + 'A' - 'a';
    }

    // Special characters
    if (ch == '0') return ')';
    if (ch == '1') return '!';
    if (ch == '2') return '@';
    if (ch == '3') return '#';
    if (ch == '4') return '$';
    if (ch == '5') return '%';
    if (ch == '6') return '^';
    if (ch == '7') return '&';
    if (ch == '8') return '*';
    if (ch == '9') return '(';
    if (ch == '-') return '_';
    if (ch == '=') return '+';
    if (ch == '[') return '{';
    if (ch == ']') return '}';
    if (ch == '\\') return '|';
    if (ch == ';') return ':';
    if (ch == '\'') return '\"';
    if (ch == ',') return '<';
    if (ch == '.') return '>';
    if (ch == '/') return '?';
    if (ch == '`') return '~';
    return ch;
}

uint8_t kbd_scan_code_to_ascii(uint8_t scan_code)
{
    uint8_t ch = 0;

    if (scan_code & 0x80) {
        scan_code &= 0x7F; // clear the bit set by key break

        switch (scan_code) {
            case KBD_SC_LSHIFT:
                toggle_left_shift();
                break;
            case KBD_SC_RSHIFT:
                toggle_right_shift();
                break;
            case KBD_SC_CAPSLOCK:
                toggle_caps_lock();
                break;
            default:
                break;
        }

        return ch;
    }

    if (scan_code == KBD_SC_A) ch = 'a';
    if (scan_code == KBD_SC_B) ch = 'b';
    if (scan_code == KBD_SC_C) ch = 'c';
    if (scan_code == KBD_SC_D) ch = 'd';
    if (scan_code == KBD_SC_E) ch = 'e';
    if (scan_code == KBD_SC_F) ch = 'f';
    if (scan_code == KBD_SC_G) ch = 'g';
    if (scan_code == KBD_SC_H) ch = 'h';
    if (scan_code == KBD_SC_I) ch = 'i';
    if (scan_code == KBD_SC_J) ch = 'j';
    if (scan_code == KBD_SC_K) ch = 'k';
    if (scan_code == KBD_SC_L) ch = 'l';
    if (scan_code == KBD_SC_M) ch = 'm';
    if (scan_code == KBD_SC_N) ch = 'n';
    if (scan_code == KBD_SC_O) ch = 'o';
    if (scan_code == KBD_SC_P) ch = 'p';
    if (scan_code == KBD_SC_Q) ch = 'q';
    if (scan_code == KBD_SC_R) ch = 'r';
    if (scan_code == KBD_SC_S) ch = 's';
    if (scan_code == KBD_SC_T) ch = 't';
    if (scan_code == KBD_SC_U) ch = 'u';
    if (scan_code == KBD_SC_V) ch = 'v';
    if (scan_code == KBD_SC_W) ch = 'w';
    if (scan_code == KBD_SC_X) ch = 'x';
    if (scan_code == KBD_SC_Y) ch = 'y';
    if (scan_code == KBD_SC_Z) ch = 'z';
    if (scan_code == KBD_SC_0) ch = '0';
    if (scan_code == KBD_SC_1) ch = '1';
    if (scan_code == KBD_SC_2) ch = '2';
    if (scan_code == KBD_SC_3) ch = '3';
    if (scan_code == KBD_SC_4) ch = '4';
    if (scan_code == KBD_SC_5) ch = '5';
    if (scan_code == KBD_SC_6) ch = '6';
    if (scan_code == KBD_SC_7) ch = '7';
    if (scan_code == KBD_SC_8) ch = '8';
    if (scan_code == KBD_SC_9) ch = '9';
    if (scan_code == KBD_SC_ENTER) ch = '\n';
    if (scan_code == KBD_SC_SPACE) ch = ' ';
    if (scan_code == KBD_SC_BS) ch = 8;
    if (scan_code == KBD_SC_DASH) ch = '-';
    if (scan_code == KBD_SC_EQUALS) ch = '=';
    if (scan_code == KBD_SC_LBRACKET) ch = '[';
    if (scan_code == KBD_SC_RBRACKET) ch = ']';
    if (scan_code == KBD_SC_BSLASH) ch = '\\';
    if (scan_code == KBD_SC_SCOLON) ch = ';';
    if (scan_code == KBD_SC_QUOTE) ch = '\'';
    if (scan_code == KBD_SC_COMMA) ch = ',';
    if (scan_code == KBD_SC_DOT) ch = '.';
    if (scan_code == KBD_SC_FSLASH) ch = '/';
    if (scan_code == KBD_SC_TILDE) ch = '`';
    if (scan_code == KBD_SC_LSHIFT) toggle_left_shift();
    if (scan_code == KBD_SC_RSHIFT) toggle_right_shift();

    if (is_caps_lock_pressed) {
        ch = handle_caps_lock(ch);
    }

    if (is_lshift_down || is_rshift_down) {
        ch = handle_shift(ch);
    }

    return ch;
}

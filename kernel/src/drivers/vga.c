#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

size_t strlen(char *string) {
    size_t length = 0;
    while (string[length]) {
        length++;
    }
    return length;
}

static const size_t VGA_HEIGHT = 25;
static const size_t VGA_WIDTH = 80;

enum vga_colours {
    VGA_COLOUR_BLACK = 0,
    VGA_COLOUR_BLUE = 1,
    VGA_COLOUR_GREEN = 2,
    VGA_COLOUR_CYAN = 3,
    VGA_COLOUR_RED = 4,
    VGA_COLOUR_MAGENTA = 5,
    VGA_COLOUR_BROWN = 6,
    VGA_COLOUR_LIGHT_GREY = 7,
    VGA_COLOUR_DARK_GREY = 8,
    VGA_COLOUR_LIGHT_BLUE = 9,
    VGA_COLOUR_LIGHT_GREEN = 10,
    VGA_COLOUR_LIGHT_CYAN = 11,
    VGA_COLOUR_LIGHT_RED = 12,
    VGA_COLOUR_LIGHT_MAGENTA = 13,
    VGA_COLOUR_LIGHT_BROWN = 14,
    VGA_COLOUR_WHITE = 15,
};

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_colour;
uint16_t *terminal_buffer;

static inline uint8_t get_colour(enum vga_colours fg, enum vga_colours bg) {
    return fg | bg << 4;
}

static inline uint16_t get_vga_entry(unsigned char c, uint8_t colour) {
    return (uint16_t)c | (uint16_t)colour << 8;
}

void initialise_vga(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_colour = get_colour(VGA_COLOUR_BLUE, VGA_COLOUR_BROWN);
    terminal_buffer = (uint16_t *)0xB8000;

    for (size_t x = 0; x < VGA_WIDTH; x++) {
        for (size_t y = 0; y < VGA_HEIGHT; y++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = get_vga_entry(' ', terminal_colour);
        }
    }
}

void increment_row() {
    terminal_row++;
    if (terminal_row == VGA_HEIGHT) {
        terminal_row = 0;
    }
    terminal_column = 0;
}

void write_at_location(char c, uint8_t colour, size_t x, size_t y) {
    size_t index = terminal_row * VGA_WIDTH + terminal_column;
    terminal_buffer[index] = get_vga_entry(c, terminal_colour);
}

void write_char(char c) {
    if (c == '\n') {
        increment_row();
    } else {
        write_at_location(c, terminal_colour, terminal_column, terminal_row);
        if (terminal_column++ == VGA_WIDTH) {
            terminal_column = 0;
            if (terminal_row++ == VGA_HEIGHT) {
                terminal_row = 0;
            }
        }
    }
}

void write_string(const char *data) {
    size_t length = strlen(data);
    for (size_t i = 0; i < length; i++) {
        write_char(data[i]);
    }
}

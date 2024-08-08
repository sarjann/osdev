#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "Using linux, expecting cross-compiler"
#endif

#if !defined(__i386__)
#error "Expects ix86-elf compiler"
#endif

//// Load external
extern void test_fun(void);

extern void set_idt_gate(int, uint32_t);
extern void load_idt(void *);

// extern void init_gdt(void);
// extern void init_idt(void);
extern void init_descriptors(void);
////

extern void write_string(char *);
extern void initialise_vga();

void kernel_entrypoint(void) {
    init_descriptors();

    initialise_vga();

    // Check if 64 bit
    if (sizeof(void *) == 8) {
        write_string("64 bit\n");
    } else {
        write_string("32 bit\n");
    }

    write_string("a\na\na\na\na\n");
    write_string("Test here\nand here is \n asd");
}

void interrupt_handler(void) {
    test_fun();
}

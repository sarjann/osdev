#include <stddef.h>
#include <stdint.h>

void *memset(void *dest, int val, size_t len) {
    unsigned char *ptr = dest;
    while (len-- > 0) {
        *ptr++ = (unsigned char)val;
    }
    return dest;
}

struct idt_entry {
    uint16_t offset_1;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attributes;
    uint16_t offset_2;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

struct idt_entry idt[256];
struct idt_ptr idtp;

extern void load_idt(struct idt_ptr *idtp);

void set_idt_gate(int n, uint32_t handler) {
    idt[n].offset_1 = handler & 0xFFFF;
    idt[n].selector = 0x08;
    idt[n].zero = 0;
    idt[n].type_attributes = 0x8E;
    idt[n].offset_2 = (handler >> 16) & 0xFFFF;
}

void init_idt() {
    idtp.limit = (sizeof(struct idt_entry) * (256 - 1));
    idtp.base = (uint32_t)&idt;
    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    extern void isr_wrapper(void);

    set_idt_gate(1, (uint32_t)isr_wrapper);
    load_idt(&idtp);
}

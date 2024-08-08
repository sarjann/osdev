#include <stddef.h>
#include <stdint.h>

void *memset(void *dest, int val, size_t len) {
    unsigned char *ptr = dest;
    while (len-- > 0) {
        *ptr++ = (unsigned char)val;
    }
    return dest;
}

// IDT

struct idt_entry_s {
    uint16_t offset_1;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attributes;
    uint16_t offset_2;
} __attribute__((packed));
typedef struct idt_entry_s idt_entry_t;

struct idt_ptr_s {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));
typedef struct idt_ptr_s idt_ptr_t;

idt_entry_t idt[256];
idt_ptr_t idtp;

void set_idt_gate(int n, uint32_t handler) {
    idt[n].offset_1 = handler & 0xFFFF;
    idt[n].selector = 0x08;
    idt[n].zero = 0;
    idt[n].type_attributes = 0x8E;
    idt[n].offset_2 = (handler >> 16) & 0xFFFF;
}

void init_idt() {
    idtp.limit = (sizeof(idt_entry_t) * (256 - 1));
    idtp.base = (uint32_t)&idt;
    memset(&idt, 0, sizeof(idt_entry_t) * 256);

    extern void isr_wrapper(void);
    set_idt_gate(32, (uint32_t)isr_wrapper);
    extern void load_idt(idt_ptr_t * idtp);
    load_idt(&idtp);
}

// GDT

struct gdtr_s {
    uint16_t offset;
    uint32_t size;
} __attribute__((packed));

struct gdt_entry_s {
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));
typedef struct gdt_entry_s gdt_entry_t;

struct gdt_ptr_s {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
typedef struct gdt_ptr_s gdt_ptr_t;

gdt_entry_t gdt[5];
gdt_ptr_t gdt_ptr;

void set_gdt_gate(uint8_t n, uint16_t limit, uint32_t base, uint8_t access,
                  uint8_t granularity) {
    gdt[n].limit = limit;
    gdt[n].base_low = base & 0xFFFF;
    gdt[n].base_mid = (base >> 16) & 0xFF;
    gdt[n].base_high = (base >> 24) & 0xFF;

    gdt[n].access = access;
    gdt[n].granularity = granularity;

    return;
}

static void init_gdt(void) {
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_ptr.base = (uint32_t)&gdt;
    set_gdt_gate(0, 0, 0, 0, 0);
    set_gdt_gate(1, 0xFFFF, 0, 0x9A, 0xCF);
    set_gdt_gate(2, 0xFFFF, 0, 0x92, 0xCF);
    set_gdt_gate(3, 0xFFFF, 0, 0xFA, 0xCF);
    set_gdt_gate(4, 0xFFFF, 0, 0xF2, 0xCF);

    extern void gdt_flush(uint32_t);
    gdt_flush((uint32_t)&gdt_ptr);
    return;
}

void init_descriptors(void) {
    init_gdt();
    // init_idt();
    return;
}

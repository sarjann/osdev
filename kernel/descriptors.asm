section .bss
global isr_wrapper:function
global load_idt:function
global gdt_flush:function

align 4
    isr_wrapper:
        pushad
        cld
        extern interrupt_handler
        call interrupt_handler
        popad
        iret
    load_idt:
        lidt [esp + 4]
        ret
    gdt_flush:
        mov eax, [esp + 4]
        lgdt [eax]

        mov ax, 0x10
        mov ds, ax
        mov es, ax
        mov fs, ax
        mov gs, ax
        mov ss, ax

        ; jmp 0x08:.flush
        jmp 8
        ;:.flush
    flush:
        ret


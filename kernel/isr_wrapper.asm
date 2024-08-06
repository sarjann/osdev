section .bss
global isr_wrapper:function
global load_idt:function

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


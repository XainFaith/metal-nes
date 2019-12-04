ENTRY (_start)

SECTIONS
{
    /* Starts at LOADER_ADDR. */
    . = 0x0;

    /* For AArch64, use . = 0x80000; */
    __start = .;
    __text_start = .;
    .text :
    {
        KEEP(*(.text.boot))
        *(.text)
    }
    . = ALIGN(4096); /* align to page size */
    __text_end = .;
 
    /* Include the list of initialization functions sorted. */
    .init_array :
    {
        build/obj/crti.o(.init_array)
        KEEP (*(SORT(EXCLUDE_FILE(build/obj/crti.o build/obj/crtn.o) .init_array.*)))
        KEEP (*(EXCLUDE_FILE(build/obj/crti.o build/obj/crtn.o) .init_array))
        build/obj/crtn.o(.init_array)
    }

    /* Include the list of termination functions sorted. */
    .fini_array :
    {
        build/obj/crti.o(.fini_array)
        KEEP (*(SORT(EXCLUDE_FILE(build/obj/crti.o build/obj/crtn.o) .fini_array.*)))
        KEEP (*(EXCLUDE_FILE(build/obj/crti.o build/obj/crtn.o) .fini_array))
        build/obj/crtn.o(.fini_array)
    }

    __rodata_start = .;
    .rodata :
    {
        *(.rodata)
    }
    . = ALIGN(4096); /* align to page size */
    __rodata_end = .;
 
    __data_start = .;
    .data :
    {
        *(.data)
    }
    . = ALIGN(4096); /* align to page size */
    __data_end = .;
 
    __bss_start = .;
    .bss :
    {
        bss = .;
        *(.bss)
    }

    . = ALIGN(4096); /* align to page size */
    __bss_end = .;
    __bss_size = __bss_end - __bss_start;
    __end = .;

    /* Read-write data (initialized) */
	.stack : ALIGN(4K)
	{
        __stack_end = .;
        . += 32K;
		KEEP(*(.stack))
         __stack_base = .;
	}

    . = ALIGN(4K);
    __kernel_end  = .;
}

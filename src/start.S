.section .text.boot
interrupt_vector_table:
    b _start
    b . 
    b . @ SWI instruction
    b . 
    b .
    b .
    b .
    b .

_start:
    .globl _start
    ldr sp, =__stack_base @ Set up the stack
    bl _clear_bss
    bl _init
    bl main @ Jump to the main function
    bl _fini
_halt:
    b _halt

_clear_bss:
    @Load in the base address of the bss
    ldr r0, =__bss_start
    ldr r1, =__bss_end
    mov r4, #0
    mov r5, #0
    mov r6, #0
    mov r7, #0
    
    _clear_bss_loop:
    stmia r0!,{r4 - r7}
    cmp r0, r1
    blo _clear_bss_loop
    MOV pc,lr 

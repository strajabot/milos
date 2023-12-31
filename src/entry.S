.globl entry

.section .entry
.align 4
entry: 
    #Entry to the OS, All Harts start here
    
    .cfi_startproc
    #Inform the debugger that there is nowhere to backtrace past entry;
    .cfi_undefined ra

    #Setup Global Pointer;
    .option push
    #norelax needs to be enabled to change global pointer;
    .option norelax
    la gp, __global_pointer
    .option pop

    #Setup vectored machine mode trap table;
    la t0, machine_trap;
    ori t0, t0, 0x1;
    csrw mtvec, t0;

    #Setup vectored supervisor mode trap table;
    la t0, supervisor_trap;
    ori t0, t0, 0x1;
    csrw stvec, t0;

    #Each hart gets it's own aligned stack;
    la sp, __stack_space
    andi sp, sp, ~0b1111
    
    csrr a0, mhartid
    ld t0, __stack_size
    andi t0, t0, ~0b1111;
    
    mv t1, zero
loop:
    beq a0, t1, done
    add sp, sp, t0
    addi t1, t1, 1
    j loop;

done:
    #Stack is initialized, jump to C
    call start;

    wfi
    
    .cfi_endproc


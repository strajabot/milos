.globl entry

.section .entry
.align 4
entry: 
    #Entry to the OS, All Harts start here
    
    .cfi_startproc
    #Inform the debugger that there is nowhere to backtrace past entry;
    .cfi_undefined ra

    #Physical Memory Protection START
    la t0, __kernel_start
    la t1, __text_end
    la t2, __rodata_end
    la t3, __kernel_end
    li t4, 0x3fffffffffffff

    #pmpaddr contains addr [55:2], trim low bits
    srai t0, t0, 2
    srai t1, t1, 2
    srai t2, t2, 2
    srai t3, t3, 2

    csrw pmpaddr0, t0
    csrw pmpaddr1, t1
    csrw pmpaddr2, t2
    csrw pmpaddr3, t3
    csrw pmpaddr4, t4

    #pmp7cfg: 0x00: PMP_L                           (unused)
    #pmp6cfg: 0x00: PMP_L                           (unused)
    #pmp5cfg: 0x00: PMP_L                           (unused)
    #pmp4cfg: 0x8F: PMP_L|PMP_TOR|PMP_X|PMP_W|PMP_R (heap)
    #pmp3cfg: 0x8B: PMP_L|PMP_TOR|PMP_W|PMP_R:      (data,bss,stack)
    #pmp2cfg: 0x89: PMP_L|PMP_TOR|PMP_R: 0x99       (rodata)
    #pmp1cfg: 0x8C: PMP_L|PMP_TOR|PMP_X: 0x9C       (text)
    #pmp0cfg: 0x8B: PMP_L|PMP_TOR|PMP_W|PMP_R:      (hardware)

    li t0, 0x0000008F8B898C8B
    csrw pmpcfg0, t0

    sfence.vma x0, x0

    #Physical Memory Protection END

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
    la t0, __stack_size
    andi t0, t0, ~0b1111;
    
    mv t1, zero
loop:
    add sp, sp, t0
    beq a0, t1, done
    addi t1, t1, 1
    j loop;

done:
    #Stack is initialized, jump to C
    call start;

    wfi
    
    .cfi_endproc


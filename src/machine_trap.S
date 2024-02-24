#include "../h/types.h"
#include "../h/hw.h"
#include "../h/riscv.h"

.globl machine_trap

.align 4
machine_trap:
    j machine_internal_trap
    j machine_unknown_trap
    j machine_unknown_trap
    j machine_unknown_trap
    j machine_unknown_trap
    j machine_unknown_trap
    j machine_unknown_trap
    j machine_timer_trap
    j machine_unknown_trap
    j machine_unknown_trap

.align 4
machine_internal_trap:
    #check if trap was caused by supervisor trap
    #otherwise call fault handler
    csrr t0, mcause
    li t1, SUPERVISOR_ECALL
    bne t0, t1, machine_fault_trap

    #(a0: opcode, a1-a7: args)
    #increase sepc 
    csrr t0, mepc
    addi t0, t0, 4
    csrw mepc, t0

    la t0, scall_jump_table
    #load jump table offset
    andi a0, a0, 0xf
    slli a0, a0, 2
    add t0, t0, a0
    jr t0

.align 4
scall_jump_table:
    j scall_read_mhartid  
    j scall_read_mtime
    j scall_write_mtime
    j scall_read_mtimecmp
    j scall_write_mtimecmp
    j scall_illegal
    j scall_illegal
    j scall_illegal
    j scall_illegal
    j scall_illegal
    j scall_illegal
    j scall_illegal
    j scall_illegal
    j scall_illegal
    j scall_illegal
    j scall_illegal
    
.align 4
scall_read_mhartid:
    csrr a0, mhartid
    mret

.align 4
scall_read_mtime:
    li t0, CLINT_MTIME
    ld a0, (t0)
    mret

.align 4
scall_write_mtime:
    li t0, CLINT_MTIME
    sd a1, (t0)
    mret

.align 4
scall_read_mtimecmp:
    #todo: bounds check a1
    li t0, CLINT_MTIMECMP
    slli a1, a1, 3
    add t0, t0, a1
    ld a0, (t0)
    mret

.align 4
scall_write_mtimecmp:
    #todo: bounds check a1
    li t0, CLINT_MTIMECMP
    slli a1, a1, 3
    add t0, t0, a1
    sd a2, (t0)
    mret
    
.align 4
scall_illegal:
    #todo: kernel oops.
    ebreak;

.align 4
machine_fault_trap:
    #todo: kernel oops.
    ebreak;

.align 4
machine_timer_trap:
    #todo: alloc extra space to save t0 and t1
    addi sp, sp, -16
    
    sd t0,  8(sp)
    sd t1,  0(sp)

    csrr t0, mhartid
    # clear machine mode interrupt;
    li t1, CLINT_MTIMECMP
    slli t0, t0, 3
    add t1, t1, t0
    li t0, UINT64_MAX
    sd t0, (t1)

    # delegate interrupt to supervisor mode;
    li t0, SUPERVISOR_TIMER_INTR_MASK
    csrs mip, t0

    ld t0,  8(sp)
    ld t1,  0(sp)
    
    addi sp, sp, 16

    mret

.align 4
machine_unknown_trap:
    addi sp, sp, -240
    
    sd ra,  232(sp)
    sd fp,  224(sp)
    sd gp,  216(sp)
    sd tp,  208(sp)
    sd s1,  200(sp)
    sd s2,  192(sp)
    sd s3,  184(sp)
    sd s4,  176(sp)
    sd s5,  168(sp)
    sd s6,  160(sp)
    sd s7,  152(sp)
    sd s8,  144(sp)
    sd s9,  136(sp)
    sd s10, 128(sp)
    sd s11, 120(sp)
    sd a0,  112(sp)
    sd a1,  104(sp)
    sd a2,  96(sp)
    sd a3,  88(sp)
    sd a4,  80(sp)
    sd a5,  72(sp)
    sd a6,  64(sp)
    sd a7,  56(sp)
    sd t0,  48(sp)
    sd t1,  40(sp)
    sd t2,  32(sp)
    sd t3,  24(sp)
    sd t4,  16(sp)
    sd t5,  8(sp)
    sd t6,  0(sp)

    addi fp, sp, 240
    #todo: kernel oops
    ebreak


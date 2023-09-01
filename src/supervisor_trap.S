.globl supervisor_trap

.align 4
supervisor_trap:
    j supervisor_internal_trap
    j supervisor_timer_trap
    j supervisor_unknown_trap
    j supervisor_unknown_trap
    j supervisor_unknown_trap
    j supervisor_unknown_trap
    j supervisor_unknown_trap
    j supervisor_unknown_trap
    j supervisor_unknown_trap
    j supervisor_uart_trap


.align 4
supervisor_internal_trap:
    addi sp, sp, -120

    sd ra,  112(sp)
    sd fp,  104(sp)
    sd gp,  96(sp)
    sd tp,  88(sp)
    sd s1,  80(sp)
    sd s2,  72(sp)
    sd s3,  64(sp)
    sd s4,  56(sp)
    sd s5,  48(sp)
    sd s6,  40(sp)
    sd s7,  32(sp)
    sd s8,  24(sp)
    sd s9,  16(sp)
    sd s10, 8(sp)
    sd s11, 0(sp)

    addi fp, sp, 120

    call supervisor_internal_trap_handler

    ld ra,  112(sp)
    ld fp,  104(sp)
    ld gp,  96(sp)
    ld tp,  88(sp)
    ld s1,  80(sp)
    ld s2,  72(sp)
    ld s3,  64(sp)
    ld s4,  56(sp)
    ld s5,  48(sp)
    ld s6,  40(sp)
    ld s7,  32(sp)
    ld s8,  24(sp)
    ld s9,  16(sp)
    ld s10, 8(sp)
    ld s11, 0(sp)

    addi sp, sp, 120

    sret

.align 4
supervisor_timer_trap:
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

    call supervisor_timer_trap_handler

    ld ra,  232(sp)
    ld fp,  224(sp)
    ld gp,  216(sp)
    ld tp,  208(sp)
    ld s1,  200(sp)
    ld s2,  192(sp)
    ld s3,  184(sp)
    ld s4,  176(sp)
    ld s5,  168(sp)
    ld s6,  160(sp)
    ld s7,  152(sp)
    ld s8,  144(sp)
    ld s9,  136(sp)
    ld s10, 128(sp)
    ld s11, 120(sp)
    ld a0,  112(sp)
    ld a1,  104(sp)
    ld a2,  96(sp)
    ld a3,  88(sp)
    ld a4,  80(sp)
    ld a5,  72(sp)
    ld a6,  64(sp)
    ld a7,  56(sp)
    ld t0,  48(sp)
    ld t1,  40(sp)
    ld t2,  32(sp)
    ld t3,  24(sp)
    ld t4,  16(sp)
    ld t5,  8(sp)
    ld t6,  0(sp)

    addi sp, sp, 240 

    sret

.align 4
supervisor_unknown_trap:
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

    call supervisor_unknown_trap_handler

    ld ra,  232(sp)
    ld fp,  224(sp)
    ld gp,  216(sp)
    ld tp,  208(sp)
    ld s1,  200(sp)
    ld s2,  192(sp)
    ld s3,  184(sp)
    ld s4,  176(sp)
    ld s5,  168(sp)
    ld s6,  160(sp)
    ld s7,  152(sp)
    ld s8,  144(sp)
    ld s9,  136(sp)
    ld s10, 128(sp)
    ld s11, 120(sp)
    ld a0,  112(sp)
    ld a1,  104(sp)
    ld a2,  96(sp)
    ld a3,  88(sp)
    ld a4,  80(sp)
    ld a5,  72(sp)
    ld a6,  64(sp)
    ld a7,  56(sp)
    ld t0,  48(sp)
    ld t1,  40(sp)
    ld t2,  32(sp)
    ld t3,  24(sp)
    ld t4,  16(sp)
    ld t5,  8(sp)
    ld t6,  0(sp)

    addi sp, sp, 240 

    sret

.align 4
supervisor_uart_trap:
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

    call supervisor_uart_trap_handler

    ld ra,  232(sp)
    ld fp,  224(sp)
    ld gp,  216(sp)
    ld tp,  208(sp)
    ld s1,  200(sp)
    ld s2,  192(sp)
    ld s3,  184(sp)
    ld s4,  176(sp)
    ld s5,  168(sp)
    ld s6,  160(sp)
    ld s7,  152(sp)
    ld s8,  144(sp)
    ld s9,  136(sp)
    ld s10, 128(sp)
    ld s11, 120(sp)
    ld a0,  112(sp)
    ld a1,  104(sp)
    ld a2,  96(sp)
    ld a3,  88(sp)
    ld a4,  80(sp)
    ld a5,  72(sp)
    ld a6,  64(sp)
    ld a7,  56(sp)
    ld t0,  48(sp)
    ld t1,  40(sp)
    ld t2,  32(sp)
    ld t3,  24(sp)
    ld t4,  16(sp)
    ld t5,  8(sp)
    ld t6,  0(sp)

    addi sp, sp, 240 

    sret


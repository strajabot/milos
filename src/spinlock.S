.globl lock
.globl unlock

.local loop
.local unlock_fail

lock:
    li t0, 1
wait_lock:
    lw t1, (a0)
    bnez t1, wait_lock 
    amoswap.w.aq t1, t0, (a0)
    bnez t1, wait_lock
    ret

unlock:
    lw t0, (a0) 
    beqz t0, unlock_fail
    amoswap.w.rl x0, x0, (a0)
    mv a0, x0
    ret
unlock_fail:
    li a0, -1
    ret


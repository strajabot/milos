#ifndef HART_H
#define HART_H

#include "types.h"
#include "hw.h"
#include "riscv.h"
#include "syscall.h"

typedef struct hart {
	uint32_t lock_depth;
	uint32_t lock_interrupts;
} hart_t;

extern hart_t harts[HART_CNT];

hart_t* hart_get(uint32_t hart_id);
hart_t* hart_curr();

static inline int interrupts_get();
static inline void interrupts_enable();
static inline void interrupts_disable();

static inline int interrupts_get()
{
	return read_sstatus() & SSTATUS_SIE;
}

static inline void interrupts_enable()
{
	mask_set_sstatus(SSTATUS_SIE);
}

static inline void interrupts_disable()
{
	mask_clear_sstatus(SSTATUS_SIE);
}

#endif //!HART_H


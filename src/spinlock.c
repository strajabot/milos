#include "../h/types.h"
#include "../h/riscv.h"

#include "../h/spinlock.h"

extern void atomic_lock(uint32_t* raw_lock);
extern int atomic_unlock(uint32_t* raw_lock);

void lock(spinlock_t* spinlock)
{
	// todo: null check

	// todo: mechanism for turning interrupts off

	atomic_lock(&spinlock->raw_lock);

}

int unlock(spinlock_t* spinlock)
{
	// todo: null check

	int ret = atomic_unlock(&spinlock->raw_lock);

	// todo: mechanisim for turning interrupts on

	return ret;
}





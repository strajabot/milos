#include "../h/spinlock.h"

#include "../h/debug.h"
#include "../h/hart.h"
#include "../h/syscall.h"


extern void atomic_lock(uint32_t* raw_lock);
extern int atomic_unlock(uint32_t* raw_lock);

void lock(spinlock_t* spinlock)
{
	int interrupts = interrupts_get();
	interrupts_disable();

	if(!spinlock)
		oops("spinlock.c: lock: spinlock is nullptr");
	
	hart_t* hart = hart_curr();

	if(hart->lock_depth++ == 0)
		hart->lock_interrupts = interrupts;

	atomic_lock(&spinlock->raw_lock);

}

int unlock(spinlock_t* spinlock)
{
	if(!spinlock)
		oops("spinlock.c: lock: spinlock is nullptr");
	
	hart_t* hart = hart_curr();

	int ret = atomic_unlock(&spinlock->raw_lock);

	if(--hart->lock_depth == 0 && hart->lock_interrupts)
		interrupts_enable();

	return ret;
}





#ifndef SPINLOCK_H
#define SPINLOCK_H

#include "types.h"

typedef struct spinlock {
	uint32_t raw_lock;
	uint32_t hart_id;
	char name[64];
} spinlock_t;

//Returns when lock is acquired
void lock(spinlock_t* spinlock);

//Returns -1 if lock was already unlocked, otherwise returns 0;
int unlock(spinlock_t* spinlock);

#endif

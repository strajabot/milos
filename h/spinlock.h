#ifndef SPINLOCK_H
#define SPINLOCK_H

#include "types.h"

//Returns when lock is acquired
void lock(volatile uint32_t* var);

//Returns -1 if lock was already unlocked, otherwise returns 0;
int unlock(volatile uint32_t* var);

#endif

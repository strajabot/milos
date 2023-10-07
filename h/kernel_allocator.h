#ifndef KERNEL_ALLOCATOR
#define KERNEL_ALLOCATOR

#include "types.h"

void* kalloc(uint64_t size);
int kfree(void* address);

#endif //!KERNEL_ALLOCATOR

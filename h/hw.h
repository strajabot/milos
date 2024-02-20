#define HART_CNT 4
#define PAGE_SIZE 0x1000

#define CLINT_MSIP 0x2000000
#define CLINT_MTIME 0x200BFF8
#define CLINT_MTIMECMP 0x2004000

#ifndef __ASSEMBLER__

#ifndef HW_H
#define HW_H

#include "types.h"





extern void* HEAP_START[];
extern void* HEAP_END[];

#define PAGE_CEIL(ptr) ((void*)(((uint64_t)ptr + PAGE_SIZE-1) & ~(PAGE_SIZE-1)))
#define PAGE_FLOOR(ptr) ((void*)((uint64_t)ptr & ~(PAGE_SIZE-1)))

#define HEAP_START_ALIGNED PAGE_CEIL(HEAP_START)
#define HEAP_END_ALIGNED PAGE_FLOOR(HEAP_END)

#endif // !HW_H
#endif // !__ASSEMBLER__

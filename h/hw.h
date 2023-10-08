#ifndef HW_H
#define HW_H

#include "types.h"

#define HART_CNT 4
#define PAGE_SIZE 0x1000

#define CLINT 0x2000000
#define CLINT_MTIME ((time_t*)((char*)CLINT + 0xBFF8))

//msip is mapped into 4 byte word
#define CLINT_MSIP(hart_id) ((volatile uint32_t*)((char*)CLINT + 4*hart_id))

//mtimecmp is mapped into 8 byte word;
#define CLINT_MTIMECMP(hart_id) ((volatile uint64_t*)(char*)CLINT + 0x4000 + 8*hart_id)

extern void* HEAP_START[];
extern void* HEAP_END[];

#define PAGE_CEIL(ptr) ((void*)(((uint64_t)ptr + PAGE_SIZE-1) & ~(PAGE_SIZE-1)))
#define PAGE_FLOOR(ptr) ((void*)((uint64_t)ptr & ~(PAGE_SIZE-1)))

#define HEAP_START_ALIGNED PAGE_CEIL(HEAP_START)
#define HEAP_END_ALIGNED PAGE_FLOOR(HEAP_END)

#endif // !HW_H

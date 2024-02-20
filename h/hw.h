#define HART_CNT 4
#define PAGE_SIZE 0x1000

#define CLINT_MSIP 0x2000000
#define CLINT_MTIME 0x200BFF8
#define CLINT_MTIMECMP 0x2004000

#ifndef __ASSEMBLER__

#ifndef HW_H
#define HW_H

#include "types.h"

extern void* __kernel_start[];

extern void* __text_start[];
extern void* __text_end[];

extern void* __rodata_start[];
extern void* __rodata_end[];

extern void* __data_start[];
extern void* __data_end[];

extern void* __data_start[];
extern void* __data_end[];

extern void* __bss_start[];
extern void* __bss_end[];

extern void* __kernel_end[];

extern void* __heap_start[];
extern void* __heap_end[];

#define PAGE_CEIL(ptr) ((void*)(((uint64_t)ptr + PAGE_SIZE-1) & ~(PAGE_SIZE-1)))
#define PAGE_FLOOR(ptr) ((void*)((uint64_t)ptr & ~(PAGE_SIZE-1)))

#define HEAP_START_ALIGNED PAGE_CEIL(__heap_start)
#define HEAP_END_ALIGNED PAGE_FLOOR(__heap_end)

#endif // !HW_H
#endif // !__ASSEMBLER__

#ifndef HW_H
#define HW_H

#include "types.h"

#define HART_CNT 4

volatile uint64_t* const CLINT = (uint64_t*) 0x2000000;
volatile time_t* const CLINT_MTIME = (time_t*)((char*)CLINT + 0xBFF8);
inline volatile uint32_t* CLINT_MSIP(uint64_t hart_id);
inline volatile time_t* CLINT_MTIMECMP(uint64_t hart_id);

extern void* HEAP_START;
extern void* HEAP_END;

inline volatile uint32_t* CLINT_MSIP(uint64_t hart_id)
{
	//msip is mapped into 4 byte word;
	return (volatile uint32_t*)((char*)CLINT + 4*hart_id);
}

inline volatile time_t* CLINT_MTIMECMP(uint64_t hart_id)
{
	//mtimecmp is mapped into 8 byte word;
	return (volatile uint64_t*)((char*)CLINT + 0x4000 + 8*hart_id);
}

#endif // !HW_H

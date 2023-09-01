#ifndef SUPERVISOR_TRAP_HANDLER
#define SUPERVISOR_TRAP_HANDLER

#include "stdint.h"

#define SBI_MALLOC			0x0000000000000010
#define SBI_FREE			0x0000000000000011
#define SBI_FORK			0x0000000000000020
#define SBI_EXEC			0x0000000000000021
#define SBI_SPAWN			0x0000000000000022
#define SBI_EXIT			0x0000000000000023
#define SBI_THREAD_CREATE	0x0000000000000030
#define SBI_THREAD_EXIT		0x0000000000000031
#define SBI_THREAD_JOIN		0x0000000000000032
#define SBI_THREAD_SLEEP	0x0000000000000033
#define SBI_SEM_OPEN		0x0000000000000040
#define SBI_SEM_CLOSE		0x0000000000000041
#define SBI_SEM_WAIT		0x0000000000000042
#define SBI_SEM_SIGNAL		0x0000000000000043
//#define SBI_FOPEN			0x0000000000000050


uint64_t supervisor_internal_trap_handler(
	uint64_t a0,
	uint64_t a1,
	uint64_t a2,
	uint64_t a3,
	uint64_t a4,
	uint64_t a5,
	uint64_t a6,
	uint64_t a7);

void supervisor_timer_trap_handler();
void supervisor_unknown_trap_handler();
void supervisor_uart_trap_handler();

#endif // !SUPERVISOR_TRAP_HANDLER


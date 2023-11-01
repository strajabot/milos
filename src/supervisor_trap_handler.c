#include "../h/supervisor_trap_handler.h"

#include "../h/riscv.h"

uint64_t supervisor_internal_trap_handler(
	uint64_t a0, 
	uint64_t a1, 
	uint64_t a2, 
	uint64_t a3,
	uint64_t a4,
	uint64_t a5,
	uint64_t a6, 
	uint64_t a7) 
{
	uint64_t sstatus = read_sstatus();
	uint64_t pc = (uint64_t) read_sepc();
	const uint64_t code = a0;

	switch (code) {
		case SBI_MALLOC:

		break;
		case SBI_FREE:

		break;
		case SBI_FORK:

		break;
		case SBI_EXEC:
		
		break;
		case SBI_SPAWN:

		break;
		case SBI_EXIT:

		break;
		case SBI_THREAD_CREATE:

		break;
		case SBI_THREAD_EXIT:
		
		break;
		case SBI_THREAD_JOIN:

		break;
		case SBI_THREAD_SLEEP:

		break;
		case SBI_SEM_OPEN:

		break;
		case SBI_SEM_CLOSE:

		break;
		case SBI_SEM_WAIT:
		
		break;
		case SBI_SEM_SIGNAL:

		break;
	}


	return a0;
}

void supervisor_timer_trap_handler()
{
	
}

void supervisor_unknown_trap_handler()
{

}

void supervisor_uart_trap_handler()
{

}


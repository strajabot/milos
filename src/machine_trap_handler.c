#include "../h/machine_trap_handler.h"

#include "../h/riscv.h"
#include "../h/timer.h"

uint64_t machine_internal_trap_handler(
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
	uint64_t pc = read_sepc();

	const uint64_t code = a7;
	switch(code) {
		case REQ_TIMER_INTERRUPT:
			a0 = timer_create(a1);
		break;

		case REQ_PERIODIC_INTERRUPT:
			a0 = timer_create_periodic(a1);
		break;
		
		case STOP_PERIODIC_INTERRUPT:
			a0 = (uint64_t) timer_destroy_periodic(a1); 
		break;

		case GET_TIME:
			a0 = timer_get_time();
		break;
	}

	write_sepc(pc + 4);
	write_sstatus(sstatus);
	
	return a0;
}

void machine_timer_trap_handler()
{
		
}

void machine_unknown_trap_handler()
{

}


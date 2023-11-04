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
	uint64_t mstatus = read_mstatus();
	uint64_t pc = (uint64_t)read_mepc();

	const uint64_t code = a7;
	uint64_t ret = 0;
	switch(code)
	{
		case READ_MHARTID:
		{
			ret = read_mhartid();
			break;
		}
		case READ_MTIMECMP:
		{
			const uint64_t hart_id = a0; 
			ret = read_mtimecmp(hart_id);
			break;
		}
		case WRITE_MTIMECMP:
		{
			const uint64_t hart_id = a0;
			const time_t time = a1;
			write_mtimecmp(hart_id, time);
			break;
		}
		default:
		{
			ret = -1;
			break;
		}
	}

	write_mepc((void*)(pc + 4));
	write_mstatus(mstatus);
	
	return ret;
}

void machine_timer_trap_handler()
{
	//Machine Timer Interrupt Is handled here.
	timer_machine_interrupt();
}

void machine_unknown_trap_handler()
{

}


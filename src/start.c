#include "../h/riscv.h"
#include "../h/types.h"
#include "../h/main.h"


void start()
{
	//Machine mode

	//Flush everything in TLB;
	sfence_vma_all();
	//Disable address translation;
	write_satp(0x0000000000000000);
	//Flush everything in TLB;
	sfence_vma_all();

	//Delegate Supervisor Interrupts to Supervisor;
	write_mideleg(
		SUPERVISOR_EXT_INTR_MASK |
		SUPERVISOR_TIMER_INTR_MASK |
		SUPERVISOR_SOFT_INTR_MASK
	);
	//Delegate Supervisor Exceptions to Supervisor;
	//TODO: Enum MEDELEG values 
	write_medeleg(0xFFFFFFFFFFFFFFFF);	

	//Hart ID is passed to Supervisor via sscratch;
	write_sscratch(read_mhartid());

	//Setup drop to Supervisor mode;
	mask_clear_mstatus(MSTATUS_MPP);
	mask_set_mstatus(MSTATUS_MPP_SUPERVISOR);

	//Setup jump to main; 
	write_sepc(main);

	//Drop to supervisor, jump to main();
	mret();
	
	return;
}

#include "../h/riscv.h"
#include "../h/types.h"

extern int main();

void start()
{
	//Machine mode


	//Delegate Supervisor Interrupts to Supervisor;
	write_mideleg(
		SUPERVISOR_EXT_INTR_MASK |
		SUPERVISOR_TIMER_INTR_MASK |
		SUPERVISOR_SOFT_INTR_MASK
	);

	//Delegate Supervisor Exceptions to Supervisor;
	write_medeleg(
		INSTR_MISALIGNED_MASK |
		INSTR_ACCESS_FAULT_MASK |
		INSTR_ILLEGAL_MASK |
		BREAKPOINT_MASK |
		LOAD_MISALIGNED_MASK |
		LOAD_ACCESS_FAULT_MASK |
		STORE_MISALIGNED_MASK |
		STORE_ACCESS_FAULT_MASK |
		USER_ECALL_MASK |
		//SUPERVISOR_ECALL_MASK | //Supervisor syscalls are handled in Machine mode
		//MACHINE_ECALL_MASK | //Machine mode ecall can't be delegated
		INSTR_PAGE_FAULT_MASK |
		LOAD_PAGE_FAULT_MASK |
		STORE_PAGE_FAULT_MASK
	);

	write_mie(
		SUPERVISOR_SOFT_INTR_MASK |
		MACHINE_SOFT_INTR_MASK |
		SUPERVISOR_TIMER_INTR_MASK |
		MACHINE_TIMER_INTR_MASK |
		SUPERVISOR_EXT_INTR_MASK |
		MACHINE_EXT_INTR_MASK
	);

	//Flush everything in TLB;
	sfence_vma_all();
	//Disable address translation;
	write_satp(0x0000000000000000);
	//Flush everything in TLB;
	sfence_vma_all();

	//Hart ID is passed to Supervisor via sscratch;
	write_sscratch(read_mhartid());

	//Setup drop to Supervisor mode;
	mask_clear_mstatus(MSTATUS_MPP);
	mask_set_mstatus(MSTATUS_MPP_SUPERVISOR);

	//Setup jump to main; 
	write_mepc(main);

	//Drop to supervisor, jump to main();
	mret();

	return;
}

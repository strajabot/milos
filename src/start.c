#include "../h/riscv.h"
#include "../h/stdint.h"
#include "../h/main.h"


void start(uint64_t hart_id)
{

	//delegate all interrupts to supervisor mode;
	write_mideleg(0xFFFFFFFFFFFFFFFF);
	
	
	main(0, NULL);

	return;
}

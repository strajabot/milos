#include "../h/riscv.h"
#include "../h/types.h"
#include "../h/main.h"


void start()
{
	//Machine mode

	//delegate all interrupts to supervisor mode;
	write_mideleg(0xFFFFFFFFFFFFFFFF);
	
	//Hart ID is passed to Supervisor thru sscratch
	write_sscratch(read_mhartid());

	//TODO: Switch to Supervisor Mode into main();

	main();

	return;
}

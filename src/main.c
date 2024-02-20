#include "../h/types.h"
#include "../h/riscv.h"
#include "../h/frame_allocator.h"

int main()
{
	//Supervisor Mode
	//Important: Machine Mode passes Hart ID thru sscratch
	uint64_t hart_id = read_sscratch();

	frame_allocator_init();	
		
	return -4;
}

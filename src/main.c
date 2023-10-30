#include "../h/main.h"

#include "../h/frame_allocator.h"

int main()
{
	//Supervisor Mode
	//Important: Machine Mode passes Hart ID thru sscratch

	read_mhartid();
	frame_allocator_init();	
		
	return -4;
}

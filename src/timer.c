#include "../h/timer.h"

#include "../h/riscv.h"

static time_t time = 0;

static timer_t* list = NULL;

//provides a timer interrupt after time [ns] 
uint64_t timer_create(time_t time)
{

	//todo: implement;
}

uint64_t timer_create_periodic(time_t period)
{
	//todo: implement;
}

int timer_destroy_periodic(time_t period)
{
	//todo: implement;
}

time_t timer_get_time()
{
	return time + read_mtime();
}

void timer_interrupt()
{
	time += read_mtime();

}

#include "../h/timer.h"

#include "../h/riscv.h"

static time_t time = 0;
static uint64_t timer_id = 0;
static timer_t* list = NULL;

//provides a timer interrupt after time [ns] 
uint64_t timer_create(time_t delay)
{
	timer_t* timer = timer_alloc();
	
	timer->timer_id = timer_id++;
	timer->delay = delay;
	timer->periodic = 0;
	timer->next = NULL;
	
	if(list == NULL) 
	{
		//add to head when no interrupts are scheduled;
		list = timer;
		timer_update_req();
		return timer->timer_id;
	} 

	time_t time_relative = read_mtime();
	
	if(timer->delay < list->delay - time_relative)
	{
		//add to head when interrupt is scheduled
		//before the first in the list; 
		list->delay -= time_relative + timer->delay;
		timer->next = list;
		list = timer;
		timer_update_req();
		return timer->timer_id; 
	} else {
		//add into list (not head);
		timer->delay -= list->delay - time_relative;
		timer_t* iter = list;
        timer_t* next = iter->next;
		
		while(next != NULL)
		{
			//find place to insert timer entry;
			if(next->delay > iter->delay) break;
			timer->delay -= next->delay;
			iter = next;
			next = iter->next;
		}
		
		iter->next = timer;
		timer->next = next;
		timer_update_req();

	}

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
	//todo: implement;
	//time += read_mtime();
	//remove head of list;
	timer_update_req();
}

timer_t* timer_alloc()
{
	//todo: implement;
	return NULL;
}

void timer_update_req()
{
	time_t delay = list != NULL? list->delay: 0;
	time += read_mtime();
	write_mtime(0);
	write_mtimecmp(delay);
}
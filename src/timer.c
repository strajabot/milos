#include "../h/timer.h"

#include "../h/hw.h"
#include "../h/kernel_allocator.h"
#include "../h/riscv.h"
#include "../h/spinlock.h"

static volatile uint32_t mutex = 0;
static volatile uint64_t timer_id = 0;

//sorted list of (unscheduled) timer interrupt requests
static volatile timer_t* volatile timer_list = NULL;

//maps hart_id -> (scheduled) timer interrupt request
static volatile timer_t* const hart_timer[HART_CNT] = { NULL };

//provides a timer interrupt after time [ns] 
uint64_t timer_create(time_t delay)
{
	timer_t* timer = (timer_t*) kalloc(sizeof(timer_t));
	if(timer == NULL) return 0;
	
	time_t curr_time = read_time();

	lock(&mutex);

	timer->id = timer_id++;
	timer->end = curr_time + delay;
	timer->period = 0;
	timer->next = NULL;
	
	timer_add(timer);

	unlock(&mutex);
	return timer->id;
}

//Must be called inside MUTEX;
static void timer_queue_periodic(timer_t* timer)
{
	time_t curr_time = read_time();
	timer->end = curr_time + timer->period;
	timer_add(timer);
}

uint64_t timer_create_periodic(time_t period)
{	
	timer_t* timer = (timer_t*) kalloc(sizeof (timer_t));
	if(timer == NULL) return 0;
	
	lock(&mutex);

	timer->id = timer_id++;
	timer->period = 1;
	timer->next = NULL;

	timer_queue_periodic(timer);

	unlock(&mutex);
	return timer->id;
}

int timer_destroy_periodic(uint64_t id)
{
	lock(&mutex);

	for(int iter=0; iter<HART_CNT; iter++)
	{
		if(hart_timer[iter]->id == id)
		{
			//remove scheduled interrupt
			kfree(hart_timer[iter]);
			hart_timer[iter] = NULL;
			timer_sched(iter);
			unlock(&mutex);
			return 0;
		}
	}

	if(timer_list == NULL) return -1;

	timer_t* prev = timer_list;

	if(timer_list->id == id)	
	{
		//remove from list head
		timer_list = timer_list->next; 
		kfree(prev);
		unlock(&mutex);
		return 0;
	}
	
	timer_t* iter = timer_list->next;

	while(iter != NULL) {
		if(iter->id == id) {
			prev->next = iter->next;
			kfree(iter);
			unlock(&mutex);
			return 0;
		}
	}

	unlock(&mutex);
	return -1;
}

//tries to schedule a timer interrupt on one of the harts
//based on the trigger time. if no sufficient hart is found
//it puts the request in a sorted queue
void timer_add(timer_t* timer)
{

	//try to find hart to schedule timer interrupt;
	uint32_t hart_id = HART_CNT;
	for(uint32_t iter=0; iter<HART_CNT; iter++)
	{
		if(hart_timer[iter] == NULL)
		{
			hart_id = iter;
			break;
		}

		time_t hart_end = hart_timer[hart_id]->end;
		time_t iter_end = hart_timer[iter]->end;
		
		if(iter_end > timer->end && iter_end > hart_end)
		{
			hart_id = iter;
		}

	}
	
	if(hart_id < HART_CNT)
	{
		//hart was found;
		if(hart_timer[hart_id] != NULL)
			timer_list_add(hart_timer[hart_id]);
		timer_write(hart_id, timer);
	}

	timer_list_add(timer);

}

void timer_list_add(timer_t* timer)
{
	
	if(timer_list == NULL || timer_list->end >= timer->end)
	{
		timer->next = timer_list;
		timer_list = timer;
		return;
	}

	//add into list (not head);
	timer_t* iter = timer_list;
    timer_t* next = iter->next;
	
	while(next != NULL)
	{

		//find place to insert timer entry;
		if(next->end > timer->end) break;
		iter = next;
		next = iter->next;
	}
		
	iter->next = timer;
	timer->next = next;
}

void timer_write(uint32_t hart_id, timer_t* timer)
{
	//todo: Dodati assert
	if(hart_id >= HART_CNT) return;
	//replace current 
	hart_timer[hart_id] = timer; 
	time_t end = timer != NULL? timer->end: UINT64_MAX;
	mcall_write_mtimecmp(hart_id, end);
}


void timer_supervisor_intr()
{
	uint32_t hart_id = mcall_read_hartid();

	timer_callback callback = NULL;

	lock(&mutex);
	
	timer_t* timer = hart_timer[hart_id];
	callback = timer->callback;



	if(timer->periodic)
		timer_queue_periodic(timer); 
	
	unlock(&mutex);

	//if(callback == NULL) 
		//TODO: panic;
	
	callback();
}

void timer_machine_intr()
{
	write_mtimecmp(read_mhartid(), UINT64_MAX);
	mask_clear_mip(MACHINE_TIMER_INTR_MASK);
	mask_set_mip(SUPERVISOR_TIMER_INTR_MASK);
}

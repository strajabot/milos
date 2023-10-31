#include "../h/frame_allocator.h"

#include "../h/hw.h"
#include "../h/spinlock.h"
#include "../h/types.h"


static volatile uint32_t mutex = 0;

static free_frame_t* free_list = NULL;

static inline free_frame_t* next_frame(free_frame_t* frame)
{
	return (free_frame_t*) ((uint64_t)frame + PAGE_SIZE); 	
}

void frame_allocator_init()
{
	lock(&mutex);
	
	free_list = (free_frame_t*) HEAP_START_ALIGNED;
	free_list->next = NULL;

	free_frame_t* frame = free_list;
	free_frame_t* next = next_frame(frame);
	while(next != HEAP_END_ALIGNED)
	{
		frame->next = next;
		frame = next;
		next = next_frame(frame);
	}
	frame->next = NULL;

	unlock(&mutex);
}

void* frame_alloc()
{
	lock(&mutex);

	if(!free_list) 
	{
		unlock(&mutex);
		return NULL;
	}
	free_frame_t* frame = free_list;
	free_list = free_list->next;
	
	unlock(&mutex);
	
	return frame;
}

void frame_free(void *ptr)
{
	ptr = PAGE_FLOOR(ptr);
	
	lock(&mutex);

	free_frame_t* frame = (free_frame_t*) ptr;
	frame->next = free_list;
	free_list = frame;

	unlock(&mutex);
}


#include "../h/frame_allocator.h"

#include "../h/hw.h"
#include "../h/spinlock.h"
#include "../h/types.h"


static uint32_t list_lock = 0;

static free_frame_t* free_list = NULL;

static inline free_frame_t* next_frame(free_frame_t* frame)
{
	return (free_frame_t*) ((uint64_t)frame + PAGE_SIZE); 	
}

void frame_allocator_init()
{
	lock(&list_lock);
	
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

	unlock(&list_lock);
}

void* frame_alloc()
{
	lock(&list_lock);

	if(!free_list) 
	{
		unlock(&list_lock);
		return NULL;
	}
	free_frame_t* frame = free_list;
	free_list = free_list->next;
	
	unlock(&list_lock);
	
	return frame;
}

void frame_free(void *ptr)
{
	ptr = PAGE_FLOOR(ptr);
	
	lock(&list_lock);

	free_frame_t* frame = (free_frame_t*) ptr;
	frame->next = free_list;
	free_list = frame;

	unlock(&list_lock);
}


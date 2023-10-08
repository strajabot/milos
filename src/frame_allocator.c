#include "../h/frame_allocator.h"

#include "../h/types.h"
#include "../h/hw.h"

static free_frame_t* free_list = NULL;

static inline free_frame_t* next_frame(free_frame_t* frame)
{
	return (free_frame_t*) ((uint64_t)frame + PAGE_SIZE); 	
}

void frame_allocator_init()
{
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
}

void* frame_alloc()
{
	if(!free_list) return NULL;
	free_frame_t* frame = free_list;
	free_list = free_list->next;
	return frame;
}

void frame_free(void *ptr)
{
	ptr = PAGE_FLOOR(ptr);
	free_frame_t* frame = (free_frame_t*) ptr;
	frame->next = free_list;
	free_list = frame;
}


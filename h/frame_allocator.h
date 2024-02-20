#ifndef FRAME_ALLOCATOR_H
#define FRAME_ALLOCATOR_H

typedef struct free_frame {
	struct free_frame* next;		
} free_frame_t;

void frame_allocator_init();
void* frame_alloc();
void frame_free(void* ptr);

#endif // !FRAME_ALLOCATOR_H


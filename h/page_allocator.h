#ifndef PAGE_ALLOCATOR_H
#define PAGE_ALLOCATOR_H

#define PAGE_SIZE 0x1000  

typedef struct free_page {
	struct free_page* next;		
} free_page_t;

void pallocator_init();
void* pallocator_alloc();
void pallocator_free(void* ptr);

#endif // !PAGE_ALLOCATOR_H


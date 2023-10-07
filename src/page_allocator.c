#include "../h/page_allocator.h"

#include "../h/types.h"
#include "../h/hw.h"

static free_page_t* free_list = NULL;

static inline free_page_t* next_page(free_page_t* page)
{
	return (free_page_t*) ((char*)page + PAGE_SIZE); 	
}

void pallocator_init()
{
	free_list = (free_page_t*) HEAP_START;
	free_list->next = NULL;

	free_page_t* page = free_list;
	free_page_t* next = next_page(page);
	while(next != HEAP_END)
	{
		page->next = next;
		page = next;
		next = next_page(page);
	}
	page->next = NULL;
}

void* pallocator_alloc()
{
	if(!free_list) return NULL;
	free_page_t* page = free_list;
	free_list = free_list->next;
	return page;
}

void pallocator_free(void *ptr)
{
	free_page_t* page = (free_page_t*) ptr;
	page->next = free_list;
	free_list = page;
}


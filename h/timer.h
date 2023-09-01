#ifndef TIMER_H
#define TIMER_H

#include "stdint.h"

typedef struct timer {
	uint64_t timer_id;
	time_t delay;
	bool_t periodic;
	struct timer* next;
} timer_t;

uint64_t timer_create(time_t time);
uint64_t timer_create_periodic(time_t period);
int timer_destroy_periodic(uint64_t id);
time_t timer_get_time();

timer_t* timer_alloc(); 
void timer_update_req();

#endif //!TIMER_H

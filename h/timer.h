#ifndef TIMER_H
#define TIMER_H

#include "types.h"

typedef struct timer {
	uint64_t id;
	time_t end;
	bool_t periodic;
	struct timer* next;
} timer_t;

uint64_t timer_create(time_t time);
uint64_t timer_create_periodic(time_t period);
int timer_destroy_periodic(uint64_t id);
time_t timer_get_time();

void timer_add(timer_t* timer);
void timer_list_add(timer_t* timer);
void timer_sched(uint32_t hart_id);
void timer_write(uint32_t hart_id, timer_t* timer);

void machine_timer_write(uint32_t hart_id, time_t end);
void machine_timer_interrupt();
#endif //!TIMER_H

#include "../h/hart.h"
#include "../h/debug.h"
#include "../h/syscall.h"

hart_t harts[HART_CNT] = { 0 };

hart_t* hart_get(uint32_t hart_id)
{
	if(hart_id >= HART_CNT)
		oops("hart.c: hart_get: hart_id >= HART_CNT");
	return &harts[hart_id];
}

hart_t* hart_curr()
{
	return hart_get(sys_read_mhartid());
}

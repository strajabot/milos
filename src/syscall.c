#include "../h/types.h"
#include "../h/syscall.h"

uint64_t syscall(uint64_t code, ...) 
{
	uint64_t ret;
	asm volatile("ecall");
	asm volatile("mv %0, a0": "=r"(ret));
	return ret;
}

// supervisor level system calls

uint64_t sys_read_mhartid()
{
	return syscall(READ_MHARTID);
}

uint64_t sys_read_mtime()
{
	return syscall(READ_MTIME);
}

void sys_write_mtime(uint64_t mtime)
{
	syscall(WRITE_MTIME, mtime);
}

uint64_t sys_read_mtimecmp(uint64_t hart_id)
{
	return syscall(READ_MTIMECMP, hart_id);
}

void sys_write_mtimecmp(uint64_t hart_id, uint64_t mtimecmp)
{
	syscall(WRITE_MTIMECMP, hart_id, mtimecmp);
}

// user level system calls


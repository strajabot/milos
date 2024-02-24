#define MACHINE_SYSCALL_MASK	0x1000000000000000

#define READ_MHARTID	0x1000000000000000
#define READ_MTIME	0x1000000000000001
#define WRITE_MTIME	0x1000000000000002
#define READ_MTIMECMP	0x1000000000000003
#define WRITE_MTIMECMP	0x1000000000000004

#ifndef __ASSEMBLER__

#ifndef SYSCALL_H
#define SYSCALL_H

#include "types.h"

uint64_t	sys_read_mhartid();
uint64_t	sys_read_mtime();
void		sys_write_mtime(uint64_t mtime);
uint64_t	sys_read_mtimecmp(uint64_t hart_id);
void		sys_write_mtimecmp(uint64_t hart_id, uint64_t mtimecmp);

#endif //!SYSCALL_H
#endif //!__ASSEMBLER__

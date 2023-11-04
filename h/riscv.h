#ifndef RISCV_H
#define RISCV_H

#include "hw.h"
#include "types.h"

//mhartid register helpers
inline uint64_t read_mhartid();

#define MSTATUS_MPP				0x0000000000001800
#define MSTATUS_MPP_MACHINE		0x0000000000001800
#define MSTATUS_MPP_SUPERVISOR	0x0000000000000800
#define MSTATUS_MPP_USER		0x0000000000000000
#define MSTATUS_MIE				0x0000000000000008

//mstatus register helpers
inline uint64_t read_mstatus();
inline void write_mstatus(uint64_t mstatus);
inline void mask_set_mstatus(uint64_t mask);
inline void mask_clear_mstatus(uint64_t mask);

//mtvec register helpers
#define MTVEC_MODE_VECTORED 0b01

inline void write_mtvec(void* base_addr, uint64_t mode);

//medeleg register helpers
inline void write_medeleg(uint64_t medeleg);
inline void mask_set_medeleg(uint64_t mask);
inline void mask_clear_medeleg(uint64_t mask);

//mideleg register helpers
inline void write_mideleg(uint64_t mideleg);
inline void mask_set_mideleg(uint64_t mask);
inline void mask_clear_mideleg(uint64_t mask);

#define SUPERVISOR_SOFT_INTR_MASK	0x0000000000000002
#define MACHINE_SOFT_INTR_MASK		0x0000000000000008
#define SUPERVISOR_TIMER_INTR_MASK	0x0000000000000020
#define MACHINE_TIMER_INTR_MASK		0x0000000000000080
#define SUPERVISOR_EXT_INTR_MASK	0x0000000000000200
#define MACHINE_EXT_INTR_MASK		0x0000000000000800

//mip register helpers
inline uint64_t read_mip();
inline void write_mip(uint64_t mip);
inline void mask_set_mip(uint64_t mask);
inline void mask_clear_mip(uint64_t mask);

//mie register helpers
inline uint64_t read_mie();
inline void write_mie(uint64_t mie);
inline void mask_set_mie(uint64_t mask);
inline void mask_clear_mie(uint64_t mask);

//mscratch register helpers
inline uint64_t read_mscratch();
inline void write_mscratch(uint64_t mscratch);

//mepc register helpers
inline void* read_mepc();
inline void write_mepc(void* mepc);

//mcause register helpers
#define INTR_MASK 				0x8000000000000000
#define SUPERVISOR_SOFT_INTR 	0x8000000000000001
#define MACHINE_SOFT_INTR 		0x8000000000000003
#define SUPERVISOR_TIMER_INTR 	0x8000000000000005
#define MACHINE_TIMER_INTR 		0x8000000000000007
#define SUPERVISOR_EXT_INTR 	0x8000000000000009
#define MACHINE_EXT_INTR 		0x800000000000000B

#define INSTR_MISALIGNED 		0x0000000000000000
#define	INSTR_ACCESS_FAULT 		0x0000000000000001
#define INSTR_ILLEGAL 			0x0000000000000002
#define BREAKPOINT 				0x0000000000000003
#define LOAD_MISALIGNED 		0x0000000000000004
#define LOAD_ACCESS_FAULT 		0x0000000000000005
#define STORE_MISALIGNED 		0x0000000000000006
#define STORE_ACCESS_FAULT 		0x0000000000000007
#define USER_ECALL				0x0000000000000008
#define SUPERVISOR_ECALL 		0x0000000000000009
#define MACHINE_ECALL	 		0x000000000000000B
#define	INSTR_PAGE_FAULT 		0x000000000000000C
#define LOAD_PAGE_FAULT			0x000000000000000D
#define STORE_PAGE_FAULT 		0x000000000000000F

inline uint64_t read_mcause();

//mtval register helpers
inline uint64_t read_mtval();

//mtime register helpers
inline time_t read_mtime();
inline void write_mtime(time_t mtime);

//mtimecmp register helpers
inline time_t read_mtimecmp(uint64_t hart_id);
inline void write_mtimecmp(uint64_t hart_id, time_t mtimecmp);

//mret instruction wrapper
inline void mret();

//sstatus register helpers
#define SSTATUS_SIE 	0x0000000000000002
#define SSTATUS_SPIE 	0x0000000000000020
#define SSTATUS_SPP 	0x0000000000000100

inline uint64_t read_sstatus();
inline void write_sstatus(uint64_t sstatus);
inline void mask_set_sstatus(uint64_t mask);
inline void mask_clear_sstatus(uint64_t mask);

//sscratch register helpers
inline uint64_t read_sscratch();
inline void write_sscratch(uint64_t sscratch);

//sepc register helpers
inline void* read_sepc();
inline void write_sepc(void* sepc);

//satp register helpers
inline void* read_satp();
inline void write_satp(void* satp);

inline void sfence_vma_all();

inline time_t read_time();

//implementation starts here
inline uint64_t read_mhartid() 
{
	uint64_t mhartid;
	asm volatile("csrr %0, mhartid": "=r"(mhartid));
	return mhartid;
}

inline uint64_t read_mstatus()
{
	uint64_t mstatus;
	asm volatile("csrr %0, mstatus": "=r"(mstatus));
	return mstatus;
}

inline void write_mstatus(uint64_t mstatus)
{
	asm volatile("csrw mstatus, %0": : "r"(mstatus));
}

inline void mask_set_mstatus(uint64_t mask)
{
	asm volatile("csrs mstatus, %0": : "r"(mask));
}

inline void mask_clear_mstatus(uint64_t mask)
{
	asm volatile("csrc mstatus, %0": : "r"(mask));
}

inline void write_mtvec(void* base_addr, uint64_t mode)
{
	uint64_t mtvec = (uint64_t)base_addr & ~0b11;
	mtvec |= mode & 0b11;
	asm volatile("csrw mtvec, %0": : "r"(mtvec));
}

inline uint64_t read_medeleg()
{
	uint64_t medeleg;
	asm volatile("csrr %0, medeleg": "=r"(medeleg));
	return medeleg;
}

inline void write_medeleg(uint64_t medeleg)
{
	asm volatile("csrw medeleg, %0": : "r"(medeleg));
}

inline void mask_set_medeleg(uint64_t mask)
{
	asm volatile("csrs medeleg, %0": : "r"(mask));
}

inline void mask_clear_medeleg(uint64_t mask)
{
	asm volatile("csrc medeleg, %0": : "r"(mask));
}

inline uint64_t read_mideleg()
{
	uint64_t mideleg;
	asm volatile("csrr %0, mideleg": "=r"(mideleg));
	return mideleg;
}

inline void write_mideleg(uint64_t mideleg)
{
	asm volatile("csrw mideleg, %0": : "r"(mideleg));
}

inline void mask_set_mideleg(uint64_t mask)
{
	asm volatile("csrs mideleg, %0": : "r"(mask));
}

inline void mask_clear_mideleg(uint64_t mask)
{
	asm volatile("csrc mideleg, %0": : "r"(mask));
}

inline uint64_t read_mip()
{
	uint64_t mip;
	asm volatile("csrr %0, mip": "=r"(mip));
	return mip;
}

inline void write_mip(uint64_t mip)
{
	asm volatile("csrw mip, %0": : "r"(mip));
}

inline void mask_set_mip(uint64_t mask)
{
	asm volatile("csrs mip, %0": : "r"(mask));
}

inline void mask_clear_mip(uint64_t mask)
{
	asm volatile("csrc mip, %0": : "r"(mask));
}

inline uint64_t read_mie()
{
	uint64_t mie;
	asm volatile("csrr %0, mie": "=r"(mie));
	return mie;
}

inline void write_mie(uint64_t mie)
{
	asm volatile("csrw mie, %0": : "r"(mie));
}

inline void mask_set_mie(uint64_t mask)
{
	asm volatile("csrs mie, %0": : "r"(mask));
}

inline void mask_clear_mie(uint64_t mask)
{
	asm volatile("csrc mie, %0": : "r"(mask));
}

inline uint64_t read_mscratch()
{
	uint64_t mscratch;
	asm volatile("csrr %0, mscratch": "=r"(mscratch));
	return mscratch;
}

inline void write_mscratch(uint64_t mscratch)
{
	asm volatile("csrw mscratch, %0": : "r"(mscratch));
}

inline void* read_mepc()
{
	void* mepc;
	asm volatile("csrr %0, mepc": "=r"(mepc));
	return mepc;
}

inline void write_mepc(void* mepc)
{
	asm volatile("csrw mepc, %0": : "r"(mepc));
}

inline uint64_t read_mcause()
{
	uint64_t mcause;
	asm volatile("csrr %0, mcause": "=r"(mcause));
	return mcause;
}

inline uint64_t read_mtval()
{
	uint64_t mtval;
	asm volatile("csrr %0, mtval": "=r"(mtval));
	return mtval;
}

inline time_t read_mtime()
{
	return *CLINT_MTIME;
}

inline void write_mtime(time_t mtime)
{
	*CLINT_MTIME = mtime;
}

inline time_t read_mtimecmp(uint64_t hart_id)
{	
	return *CLINT_MTIMECMP(hart_id);
}

inline void write_mtimecmp(uint64_t hart_id, time_t mtimecmp)
{
	*CLINT_MTIMECMP(hart_id) = mtimecmp;
}

inline void mret()
{
	asm volatile ("mret");
}

inline uint64_t read_sstatus()
{
	uint64_t sstatus;
	asm volatile("csrr %0, sstatus": "=r"(sstatus));
	return sstatus;
}

inline void write_sstatus(uint64_t sstatus)
{
	asm volatile("csrw sstatus, %0": : "r"(sstatus));
}

inline void mask_set_sstatus(uint64_t mask)
{
	asm volatile("csrs sstatus, %0": : "r"(mask));
}

inline void mask_clear_sstatus(uint64_t mask)
{
	asm volatile("csrc sstatus, %0": : "r"(mask));
}

inline uint64_t read_sscratch()
{
	uint64_t sscratch;
	asm volatile("csrr %0, sscratch": "=r"(sscratch));
	return sscratch;
}

inline void write_sscratch(uint64_t sscratch)
{
	asm volatile("csrw sscratch, %0": : "r"(sscratch));
}

inline void* read_sepc()
{
	void* sepc;
	asm volatile("csrr %0, sepc": "=r"(sepc));
	return sepc;
}

inline void write_sepc(void* sepc)
{
	asm volatile("csrw sepc, %0": : "r"(sepc));
}

inline void* read_satp()
{
	void* satp;
	asm volatile("csrr %0, satp": "=r"(satp));
	return satp;
}

inline void write_satp(void* satp)
{
	asm volatile("csrw sepc, %0": : "r"(satp));
}

inline void sfence_vma_all()
{
	asm volatile("sfence.vma x0, x0");
}

inline time_t read_time()
{
	time_t time;
	asm volatile("rdtime %0": "=r"(time));
	return time;
}

#endif // !RISCV_H

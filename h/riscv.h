#define MSTATUS_MPP				0x0000000000001800
#define MSTATUS_MPP_MACHINE		0x0000000000001800
#define MSTATUS_MPP_SUPERVISOR	0x0000000000000800
#define MSTATUS_MPP_USER		0x0000000000000000

#define MTVEC_MODE_VECTORED 0b01

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

#define SUPERVISOR_SOFT_INTR_MASK 	(1ull << (SUPERVISOR_SOFT_INTR & ~INTR_MASK))
#define MACHINE_SOFT_INTR_MASK 		(1ull << (MACHINE_SOFT_INTR & ~INTR_MASK))
#define SUPERVISOR_TIMER_INTR_MASK 	(1ull << (SUPERVISOR_TIMER_INTR & ~INTR_MASK))
#define MACHINE_TIMER_INTR_MASK 	(1ull << (MACHINE_TIMER_INTR & ~INTR_MASK))
#define SUPERVISOR_EXT_INTR_MASK 	(1ull << (SUPERVISOR_EXT_INTR & ~INTR_MASK))
#define MACHINE_EXT_INTR_MASK 		(1ull << (MACHINE_EXT_INTR & ~INTR_MASK))

#define INSTR_MISALIGNED_MASK 		(1ull << INSTR_MISALIGNED)
#define	INSTR_ACCESS_FAULT_MASK 	(1ull << INSTR_ACCESS_FAULT)
#define INSTR_ILLEGAL_MASK 			(1ull << INSTR_ILLEGAL)
#define BREAKPOINT_MASK				(1ull << BREAKPOINT)
#define LOAD_MISALIGNED_MASK 		(1ull << LOAD_MISALIGNED)
#define LOAD_ACCESS_FAULT_MASK 		(1ull << LOAD_ACCESS_FAULT)
#define STORE_MISALIGNED_MASK		(1ull << STORE_MISALIGNED)
#define STORE_ACCESS_FAULT_MASK		(1ull << STORE_ACCESS_FAULT)
#define USER_ECALL_MASK				(1ull << USER_ECALL)
#define SUPERVISOR_ECALL_MASK 		(1ull << SUPERVISOR_ECALL)
#define MACHINE_ECALL_MASK	 		(1ull << MACHINE_ECALL)
#define	INSTR_PAGE_FAULT_MASK 		(1ull << INSTR_PAGE_FAULT)
#define LOAD_PAGE_FAULT_MASK		(1ull << LOAD_PAGE_FAULT)
#define STORE_PAGE_FAULT_MASK 		(1ull << STORE_PAGE_FAULT)

#define SSTATUS_SIE 	0x0000000000000002
#define SSTATUS_SPIE 	0x0000000000000020
#define SSTATUS_SPP 	0x0000000000000100

//PMP Flags
#define PMP_R		0x01
#define PMP_W		0x02
#define	PMP_X		0x04

//PMP Address Matching Modes
#define PMP_NAPOT	0x08
#define PMP_NA4		0x10
#define PMP_TOR		0x18

//PMP Lock 
#define PMP_L		0x80

#ifndef __ASSEMBLER__

#ifndef RISCV_H
#define RISCV_H

#include "hw.h"
#include "types.h"

//mhartid register helpers
static inline uint64_t read_mhartid();

//mstatus register helpers
static inline uint64_t read_mstatus();
static inline void write_mstatus(uint64_t mstatus);
static inline void mask_set_mstatus(uint64_t mask);
static inline void mask_clear_mstatus(uint64_t mask);

//mtvec register helpers
static inline void write_mtvec(void* base_addr, uint64_t mode);

//medeleg register helpers
static inline void write_medeleg(uint64_t medeleg);
static inline void mask_set_medeleg(uint64_t mask);
static inline void mask_clear_medeleg(uint64_t mask);

//mideleg register helpers
static inline void write_mideleg(uint64_t mideleg);
static inline void mask_set_mideleg(uint64_t mask);
static inline void mask_clear_mideleg(uint64_t mask);

//mie register helpers
static inline uint64_t read_mie();
static inline void write_mie(uint64_t mie);
static inline void mask_set_mie(uint64_t mask);
static inline void mask_clear_mie(uint64_t mask);

//mscratch register helpers
static inline uint64_t read_mscratch();
static inline void write_mscratch(uint64_t mscratch);

//mepc register helpers
static inline void* read_mepc();
static inline void write_mepc(void* mepc);

//mcause register helpers
static inline uint64_t read_mcause();

//mtval register helpers
static inline uint64_t read_mtval();

//mret instruction wrapper
static inline void mret();

//sstatus register helpers
static inline uint64_t read_sstatus();
static inline void write_sstatus(uint64_t sstatus);
static inline void mask_set_sstatus(uint64_t mask);
static inline void mask_clear_sstatus(uint64_t mask);

//sscratch register helpers
static inline uint64_t read_sscratch();
static inline void write_sscratch(uint64_t sscratch);

//sepc register helpers
static inline void* read_sepc();
static inline void write_sepc(void* sepc);

//satp register helpers
static inline void* read_satp();
static inline void write_satp(void* satp);

static inline void sfence_vma_all();

static inline uint64_t read_mhartid() 
{
	uint64_t mhartid;
	asm volatile("csrr %0, mhartid": "=r"(mhartid));
	return mhartid;
}

static inline uint64_t read_mstatus()
{
	uint64_t mstatus;
	asm volatile("csrr %0, mstatus": "=r"(mstatus));
	return mstatus;
}

static inline void write_mstatus(uint64_t mstatus)
{
	asm volatile("csrw mstatus, %0": : "r"(mstatus));
}

static inline void mask_set_mstatus(uint64_t mask)
{
	asm volatile("csrs mstatus, %0": : "r"(mask));
}

static inline void mask_clear_mstatus(uint64_t mask)
{
	asm volatile("csrc mstatus, %0": : "r"(mask));
}

static inline void write_mtvec(void* base_addr, uint64_t mode)
{
	uint64_t mtvec = (uint64_t)base_addr & ~0b11;
	mtvec |= mode & 0b11;
	asm volatile("csrw mtvec, %0": : "r"(mtvec));
}

static inline uint64_t read_medeleg()
{
	uint64_t medeleg;
	asm volatile("csrr %0, medeleg": "=r"(medeleg));
	return medeleg;
}

static inline void write_medeleg(uint64_t medeleg)
{
	asm volatile("csrw medeleg, %0": : "r"(medeleg));
}

static inline void mask_set_medeleg(uint64_t mask)
{
	asm volatile("csrs medeleg, %0": : "r"(mask));
}

static inline void mask_clear_medeleg(uint64_t mask)
{
	asm volatile("csrc medeleg, %0": : "r"(mask));
}

static inline uint64_t read_mideleg()
{
	uint64_t mideleg;
	asm volatile("csrr %0, mideleg": "=r"(mideleg));
	return mideleg;
}

static inline void write_mideleg(uint64_t mideleg)
{
	asm volatile("csrw mideleg, %0": : "r"(mideleg));
}

static inline void mask_set_mideleg(uint64_t mask)
{
	asm volatile("csrs mideleg, %0": : "r"(mask));
}

static inline void mask_clear_mideleg(uint64_t mask)
{
	asm volatile("csrc mideleg, %0": : "r"(mask));
}

static inline uint64_t read_mip()
{
	uint64_t mip;
	asm volatile("csrr %0, mip": "=r"(mip));
	return mip;
}

static inline void write_mip(uint64_t mip)
{
	asm volatile("csrw mip, %0": : "r"(mip));
}

static inline void mask_set_mip(uint64_t mask)
{
	asm volatile("csrs mip, %0": : "r"(mask));
}

static inline void mask_clear_mip(uint64_t mask)
{
	asm volatile("csrc mip, %0": : "r"(mask));
}

static inline uint64_t read_mie()
{
	uint64_t mie;
	asm volatile("csrr %0, mie": "=r"(mie));
	return mie;
}

static inline void write_mie(uint64_t mie)
{
	asm volatile("csrw mie, %0": : "r"(mie));
}

static inline void mask_set_mie(uint64_t mask)
{
	asm volatile("csrs mie, %0": : "r"(mask));
}

static inline void mask_clear_mie(uint64_t mask)
{
	asm volatile("csrc mie, %0": : "r"(mask));
}

static inline uint64_t read_mscratch()
{
	uint64_t mscratch;
	asm volatile("csrr %0, mscratch": "=r"(mscratch));
	return mscratch;
}

static inline void write_mscratch(uint64_t mscratch)
{
	asm volatile("csrw mscratch, %0": : "r"(mscratch));
}

static inline void* read_mepc()
{
	void* mepc;
	asm volatile("csrr %0, mepc": "=r"(mepc));
	return mepc;
}

static inline void write_mepc(void* mepc)
{
	asm volatile("csrw mepc, %0": : "r"(mepc));
}

static inline uint64_t read_mcause()
{
	uint64_t mcause;
	asm volatile("csrr %0, mcause": "=r"(mcause));
	return mcause;
}

static inline uint64_t read_mtval()
{
	uint64_t mtval;
	asm volatile("csrr %0, mtval": "=r"(mtval));
	return mtval;
}

static inline void mret()
{
	asm volatile ("mret");
}

static inline uint64_t read_sstatus()
{
	uint64_t sstatus;
	asm volatile("csrr %0, sstatus": "=r"(sstatus));
	return sstatus;
}

static inline void write_sstatus(uint64_t sstatus)
{
	asm volatile("csrw sstatus, %0": : "r"(sstatus));
}

static inline void mask_set_sstatus(uint64_t mask)
{
	asm volatile("csrs sstatus, %0": : "r"(mask));
}

static inline void mask_clear_sstatus(uint64_t mask)
{
	asm volatile("csrc sstatus, %0": : "r"(mask));
}

static inline uint64_t read_sscratch()
{
	uint64_t sscratch;
	asm volatile("csrr %0, sscratch": "=r"(sscratch));
	return sscratch;
}

static inline void write_sscratch(uint64_t sscratch)
{
	asm volatile("csrw sscratch, %0": : "r"(sscratch));
}

static inline void* read_sepc()
{
	void* sepc;
	asm volatile("csrr %0, sepc": "=r"(sepc));
	return sepc;
}

static inline void write_sepc(void* sepc)
{
	asm volatile("csrw sepc, %0": : "r"(sepc));
}

static inline void* read_satp()
{
	void* satp;
	asm volatile("csrr %0, satp": "=r"(satp));
	return satp;
}

static inline void write_satp(void* satp)
{
	asm volatile("csrw sepc, %0": : "r"(satp));
}

static inline void sfence_vma_all()
{
	asm volatile("sfence.vma x0, x0");
}

static inline time_t read_time()
{
	time_t time;
	asm volatile("rdtime %0": "=r"(time));
	return time;
}

#endif // !RISCV_H
#endif // !__ASSEMBLER__

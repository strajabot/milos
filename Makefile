
DIR_BUILD = build
DIR_INCLUDE = h
DIR_SOURCE = src

RISCV_ISA = rv64ima
HART_COUNT = 1

DEBUG_FLAG = -D__DEBUG__ -D__DEBUG_LEVEL__=0
KERNEL_IMG = kernel
KERNEL_ASM = kernel.asm

# riscv64-unknown-elf- or riscv64-linux-gnu-
# perhaps in /opt/riscv/bin
TOOL_PREFIX =

# Try to infer the correct TOOLPREFIX if not set
ifndef TOOLPREFIX
TOOL_PREFIX := $(shell if riscv64-unknown-elf-objdump -i 2>&1 | grep 'elf64-big' >/dev/null 2>&1; \
	then echo 'riscv64-unknown-elf-'; \
	elif riscv64-linux-gnu-objdump -i 2>&1 | grep 'elf64-big' >/dev/null 2>&1; \
	then echo 'riscv64-linux-gnu-'; \
	elif riscv64-unknown-linux-gnu-objdump -i 2>&1 | grep 'elf64-big' >/dev/null 2>&1; \
	then echo 'riscv64-unknown-linux-gnu-'; \
	else echo "***" 1>&2; \
	echo "*** Error: Couldn't find a riscv64 version of GCC/binutils." 1>&2; \
	echo "*** To turn off this error, run 'gmake TOOLPREFIX= ...'." 1>&2; \
	echo "***" 1>&2; exit 1; fi)
endif

AS      = ${TOOL_PREFIX}as
CC      = ${TOOL_PREFIX}gcc
LD      = ${TOOL_PREFIX}ld
OBJCOPY = ${TOOL_PREFIX}objcopy
OBJDUMP = ${TOOL_PREFIX}objdump

FLAGS_AS = -march=${RISCV_ISA} -mabi=lp64

FLAGS_CC  = -Wall -Og -ggdb
FLAGS_CC += -nostdlib
FLAGS_CC += -march=${RISCV_ISA} -mabi=lp64 -mcmodel=medany -mno-relax
FLAGS_CC += -fno-omit-frame-pointer -ffreestanding -fno-common
FLAGS_CC += $(shell ${CC} -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)
FLAGS_CC += ${DEBUG_FLAG}
FLAGS_CC += -MMD -MP -MF"${@:%.o=%.d}"

# Disable PIE when possible (for Ubuntu 16.10 toolchain)
ifneq ($(shell ${CC} -dumpspecs 2>/dev/null | grep -e '[^f]no-pie'),)
FLAGS_CC += -fno-pie -no-pie
endif
ifneq ($(shell ${CC} -dumpspecs 2>/dev/null | grep -e '[^f]nopie'),)
FLAGS_CC += -fno-pie -nopie
endif

SCRIPT_LD = kernel.ld
FLAGS_LD  = -z max-page-size=4096 --script ${SCRIPT_LD}

OBJECTS =

SOURCES_S = $(shell find ${DIR_SOURCE} -name "*.S" -printf "%P ")
OBJECTS += $(addprefix ${DIR_BUILD}/,${SOURCES_S:.S=.o})
vpath %.S $(sort $(dir ${SOURCES_S}))

SOURCES_C = $(shell find ${DIR_SOURCE} -name "*.c" -printf "%P ")
OBJECTS += $(addprefix ${DIR_BUILD}/,${SOURCES_C:.c=.o})
vpath %.c $(sort $(dir ${SOURCES_C}))

all: ${KERNEL_IMG}

${KERNEL_IMG}: ${OBJECTS} ${SCRIPT_LD} | ${DIR_BUILD}
	${LD} ${FLAGS_LD} -o ${@} ${OBJECTS}
	${OBJDUMP} --source ${KERNEL_IMG} > ${KERNEL_ASM}

${DIR_BUILD}/%.o: ${DIR_SOURCE}/%.c Makefile | ${DIR_BUILD}
	@mkdir -p $(dir ${@})
	${CC} -c ${FLAGS_CC} -Wa,-a,-ad,-alms=${DIR_BUILD}/${<:.c=.lst} -o ${@} ${<}

${DIR_BUILD}/%.o: ${DIR_SOURCE}/%.s Makefile | ${DIR_BUILD}
	@mkdir -p $(dir ${@})
	${AS} -c ${FLAGS_AS} -o ${@} ${<}

${DIR_BUILD}:
	mkdir ${@}

clean:
	rm -f *.tex *.dvi *.idx *.aux *.log *.ind *.ilg
	rm -f ${KERNEL_IMG} ${KERNEL_ASM}
	rm -fr ${DIR_BUILD}
	rm -f .gdbinit

OCD_PORT = 26000

SPIKE_OPTS = --isa=${RISCV_ISA} -m256 -p${HART_COUNT} ${KERNEL_IMG}
SPIKE_DEBUG = -d
SPIKE_OCD = --rbb-port=${OCD_PORT}

spike: ${KERNEL_IMG}
	@echo "Starting SPIKE RISC-V Simulator"
	spike ${SPIKE_OPTS}

spike-debug: ${KERNEL_IMG}
	@echo "Starting SPIKE RISC-V Simulator in DEBUG Mode"
	spike ${SPIKE_OPTS} ${SPIKE_DEBUG} ${KERNEL_IMG}

spike-ocd: ${KERNEL_IMG}
	@echo "Starting SPIKE RISC-V Simulator in DEBUG Mode, Waiting on: \"localhost:${OCD_PORT}\""
	spike ${SPIKE_OPTS} ${SPIKE_OCD} ${KERNEL_IMG}

GDBPORT = 26000
QEMU = qemu-system-riscv64
QEMUOPTS = -machine virt -bios none -kernel kernel -m 256M -smp $(HART_COUNT) -nographic
QEMUGDB =  -gdb tcp::$(GDBPORT) 

qemu: ${KERNEL_IMG}
	@echo "Starting QEMU RISC-V Emulator"
	$(QEMU) $(QEMUOPTS)

qemu-gdb: ${KERNEL_IMG} 
	@echo "Starting QEMU RISC-V Emulator in DEBUG Mode"
	$(QEMU) $(QEMUOPTS) -S $(QEMUGDB)

# Prevent deletion of intermediate files, e.g. cat.o, after first build, so
# that disk image changes after first build are persistent until clean.
# http://www.gnu.org/software/make/manual/html_node/Chained-Rules.html
.PRECIOUS: %.o

-include $(shell find ${DIR_BUILD} -name "*.d")

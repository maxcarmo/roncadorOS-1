OSNAME := $(shell uname -s)
QEMU = qemu-system-riscv64
ifeq ($(OSNAME), Linux)
	PRE = riscv64-linux-gnu-
# 	QEMU = /vagrant_data/riscv/riscv-qemu-4.2.0-2020.04.0-x86_64-linux-ubuntu14/bin/qemu-system-riscv64	
else
	PRE = riscv64-unknown-elf-
#	QEMU = qemu-system-riscv64
endif
GCC = $(PRE)gcc
LD = $(PRE)ld
SCRIPT = -Tkernel.ld


FLAGS+=-mcmodel=medany
# pedantic: gera o diagnóstico descrito pelo padrão C89 da linguagem C
FLAGS += -Wall -Wextra -pedantic -O0 -g
FLAGS += -march=rv64gc -mabi=lp64
FLAGS += -ffreestanding
LDFLAGS += -nostdlib 

NCPU = 4
# Dispositivos virtio 
DISK = hdd.disco
# Um id qualquer para o drive
DRIVE_ID = disco1
DRIVE = if=none,format=raw,file=$(DISK),id=$(DRIVE_ID)
HDD = virtio-blk-device,drive=$(DRIVE_ID)
RANDON = virtio-rng-device

RAM = 128M
# '\' é continuação da linha
OBJ = \
	boot.o \
	main.o \
	uart.o \
	printf.o \
	memory.o \
	string.o \
	trap_handler.o \
	trap.o \
	syscalls.o \
	plic.o \
	console.o \
	proc.o \
	programs.o \
	virtio.o
#static pattern rules (http://web.mit.edu/gnu/doc/html/make_4.html#SEC37)
# $@ e $< são variáveis automáticas 	
%.o: %.c
	$(GCC) $(FLAGS) -c -o $@ $<	

%.o: %.s
	$(GCC) $(FLAGS) -c -o $@ $<	

kernel: $(OBJ)
	$(LD) $(LDFLAGS) $(SCRIPT) -o $@  $(OBJ)

run: kernel
	$(QEMU) -append 'console=ttyS0' -nographic -serial mon:stdio \
	-bios none \
	-smp $(NCPU) \
	-machine virt -m $(RAM) \
	-drive $(DRIVE) -device $(HDD) -device $(RANDON) \
	-kernel kernel		
debug: kernel
	$(QEMU) -machine virt -m $(RAM) -nographic -serial mon:stdio -bios none \
	-gdb tcp::1234 -S -kernel kernel
clean: 
	rm -rf kernel
	rm -rf *.o

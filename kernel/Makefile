export CC=gcc
export CFLAGS=-std=c99 -finline-functions -fno-stack-protector -ffreestanding -m32 -I $(PWD)/include

export LD=ld
export LDFLAGS=-melf_i386 -Tlink.ld

export AS=nasm
export ASFLAGS=-f elf

export WARNING=-Wall -Wextra -Wno-unused-function -Wno-unused-parameter

SOURCES=idt.o gdt.o boot.o main.o isr.o
SUBDIRS=monitor lib
SUBDIRSOBJS=lib/lib.o monitor/monitor.o

.PHONY: all
all: kernel

.PHONY: clean
clean:
	$(MAKE) -C monitor clean
	$(MAKE) -C lib clean
	-rm kernel
	-rm *.o

.PHONY: subdirs
subdirs:
	for dir in $(SUBDIRS); do \
		cd $$dir && $(MAKE); \
		cd ..; \
	done

kernel: $(SOURCES) subdirs
	$(LD) $(LDFLAGS) $(SOURCES) $(SUBDIRSOBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

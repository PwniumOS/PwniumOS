include ../Makefile.inc

SOURCES=boot/boot.o main.o monitor/monitor.o

LDFLAGS+=-melf_i386 -Tlink.ld
ASFLAGS+=-f elf
CFLAGS+=-I $(PWD)/include


SUBDIRS=boot monitor

.PHONY: all
all: kernel

.PHONY: clean
clean:
	$(MAKE) -C boot clean
	$(MAKE) -C monitor clean
	-rm kernel

.PHONY: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

kernel: $(SUBDIRS) main.o
	$(LD) $(LDFLAGS) boot/boot.o main.o monitor/monitor.o -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

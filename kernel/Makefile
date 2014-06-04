include Makefile.common

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

include ../../Makefile.inc

ASFLAGS+=-f elf

.PHONY: all
all: boot.o

boot.o: boot.asm
	$(NASM) $(ASFLAGS) $< -o $@

.PHONY: clean
clean:
	-rm *.o

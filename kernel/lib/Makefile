CC=gcc
CFLAGS=-std=c99 -finline-functions -fno-stack-protector -ffreestanding -m32 -I $(PWD)/../include

LD=ld
LDFLAGS=-melf_i386 -r

WARNING=-Wall -Wextra -Wno-unused-function -Wno-unused-parameter

OBJECTS := string.o printf.o

all: lib.o

lib.o: $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o lib.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	-$(RM) *.o

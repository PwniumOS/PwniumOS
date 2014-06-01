
.PHONY: all
all: monitor.o

.PHONY: clean
clean:
	-rm *.o

monitor.o: monitor.c
	$(CC) $(CFLAGS) -c $< -o $@

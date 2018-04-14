CC ?= gcc
CFLAGS ?= -Wall -std=gnu99 -g3 -DDEBUG -O0

EXEC = main
.PHONY: all
all: $(EXEC)

main: main.c
	$(CC) $(CFLAGS) -o $@ main.c

.PHONY: clean
clean:
	$(RM) main

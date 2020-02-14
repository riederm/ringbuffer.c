CFLAGS  = -std=c99
CFLAGS += -g
#CFLAGS += -Wall
CFLAGS += -Wextra
#CFLAGS += -pedantic
#CFLAGS += -Werror
CFLAGS += -D UNITY_OUTPUT_COLOR

CC = gcc

VFLAGS  = --quiet
VFLAGS += --tool=memcheck
VFLAGS += --leak-check=full
VFLAGS += --error-exitcode=1

test, all: tests.out
	@./tests.out

memcheck: tests.out
	@valgrind $(VFLAGS) ./tests.out
	@echo "Memory check passed"

clean:
	rm -rf *.o *.out *.out.dSYM

tests.out: test/ringbuffer.test.c src/ringbuffer.c src/ringbuffer.h
	@echo Compiling $@
	@$(CC) $(CFLAGS) src/ringbuffer.c test/vendor/unity.c test/ringbuffer.test.c -o tests.out

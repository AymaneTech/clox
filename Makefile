CC = gcc
CFLAGS = -std=c99 -Wall -Wextra
LDFLAGS = -lcriterion

SOURCES = src/scanner.c src/chunk.c src/compiler.c src/debug.c src/memory.c src/value.c src/vm.c
TEST_SOURCES = tests/scanner_test.c

run: src/main.c  $(SOURCES)
	$(CC) $(CFLAGS) -o clox src/main.c $(SOURCES) -I.
	./clox

test: $(TEST_SOURCES) $(SOURCES)
	$(CC) $(CFLAGS) -o test_runner $(TEST_SOURCES) $(SOURCES) -I. $(LDFLAGS) 
	./test_runner

clean: 
	rm -f test_runner clox

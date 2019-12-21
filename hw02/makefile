# define c compiler
CC = gcc
CFLAGS =
LDFLAGS =

# Suffix rule
.SUFFIXES : .c .o
.c.o :
	$(CC) -c $(CFLAGS) $<

# Macro definition
ALL = hello output input args string

all: $(ALL)

# $@ is the name of the current target
# $< is the name of the current prerequisite
hello: hello.o
	$(CC) -o $@ $< $(LDFLAGS)

output: output.o
	$(CC) -o $@ $< $(LDFLAGS)

input: input.o
	$(CC) -o $@ $< $(LDFLAGS)

args: args.o
	$(CC) -o $@ $< $(LDFLAGS)

string: string.o
	$(CC) -o $@ $< $(LDFLAGS)

# target for rebuild all
clean :
	rm -rf *.o $(ALL)

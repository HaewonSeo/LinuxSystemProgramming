# define C compiler
CC = gcc
CFLAGS =
LDFLAGS =

# suffix rule
.SUFFIXES : .c .o
.c.o :
	$(CC) -c $(CFLAGS) $<

# macro definition (added mylsl)
ALL = stat umask chmod myln mysln myrm mymv mymd myrd myls mylsr mycd mypwd mylsl

all: $(ALL)

stat: stat.o	#dependency line
	$(CC) -o $@ $< $(LDFLAGS)	#command line

umask: umask.o
	$(CC) -o $@ $< $(LDFLAGS)

chmod: chmod.o
	$(CC) -o $@ $< $(LDFLAGS)

myln: myln.o
	$(CC) -o $@ $< $(LDFLAGS)

mysln: mysln.o
	$(CC) -o $@ $< $(LDFLAGS)

myrm: myrm.o
	$(CC) -o $@ $< $(LDFLAGS)

mymv: mymv.o
	$(CC) -o $@ $< $(LDFLAGS)

mymd: mymd.o
	$(CC) -o $@ $< $(LDFLAGS)

myrd: myrd.o
	$(CC) -o $@ $< $(LDFLAGS)

myls: myls.o
	$(CC) -o $@ $< $(LDFLAGS)

mylsr: mylsr.o
	$(CC) -o $@ $< $(LDFLAGS)

mycd: mycd.o
	$(CC) -o $@ $< $(LDFLAGS)

mypwd: mypwd.o
	$(CC) -o $@ $< $(LDFLAGS)

mylsl: mylsl.o
	$(CC) -o $@ $< $(LDFLAGS)

# for rebuild, remove *.o, &(ALL)
clean :
	rm -rf *.o $(ALL)

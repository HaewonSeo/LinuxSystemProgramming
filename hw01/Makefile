# Suffix rule
.SUFFIXES : .c .o

# Macro definition
OBJECTS = main.o input.o output.o

# Macro Substitution  $(MACRO_NAME:OLD=NEW)
SRCS = $(OBJECTS:.o=.c)

# define c compiler
CC = gcc

# define compile time option
CFLAGS = -g

# the build target executable
TARGET = snonwdeerApp

# $@ is the name of the current target
$(TARGET) : $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

# $< is the name of the current prerequisite
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

# target for rebuild all 
clean :
	$(RM) -f $(OBJECTS) $(TARGET) core

# dependency line
main.o : main.c
input.o : input.c
output.o : output.c

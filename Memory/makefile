CC = g++

all: Memory

# Compiles Memory module
Memory:  Memory.o
	del _Memory.o && ren Memory.o _Memory.o

# Compiles Memory class
Memory.o:  Memory.cpp Memory.h
	$(CC) -c Memory.cpp

# Cleans solution
clean: 
	$(RM) gamehub *.o *~

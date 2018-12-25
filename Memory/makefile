CC = g++

all: Memory

# Compiles Memory module
Memory:  Memory.o MemoryBoard.o
	ld -r Memory.o MemoryBoard.o -o _Memory.o && del Memory.o && del MemoryBoard.o

# Compiles Memory class
Memory.o:  Memory.cpp Memory.h MemoryBoard.o
	$(CC) -c Memory.cpp

# Compiles Memory class
MemoryBoard.o:  MemoryBoard.cpp MemoryBoard.h
	$(CC) -c MemoryBoard.cpp

# Cleans solution
clean: 
	$(RM) gamehub *.o *~

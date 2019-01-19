CC = g++

all: Mastermind

# Compiles SimonSays module
Mastermind:  Mastermind.o MMBoard.o
	ld -r Mastermind.o MMBoard.o -o _Mastermind.o && del Mastermind.o && del MMBoard.o

# Compiles SimonSays class
Mastermind.o:  Mastermind.cpp Mastermind.h MMBoard.o
	$(CC) -c Mastermind.cpp

MMBoard.o: MMBoard.cpp MMBoard.h
	$(CC) -c MMBoard.cpp

# Cleans solution
clean: 
	$(RM) gamehub *.o *~

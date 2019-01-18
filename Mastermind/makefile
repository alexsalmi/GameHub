CC = g++

all: Mastermind

# Compiles SimonSays module
Mastermind:  Mastermind.o
	del _Mastermind.o && ren Mastermind.o _Mastermind.o

# Compiles SimonSays class
Mastermind.o:  Mastermind.cpp Mastermind.h
	$(CC) -c Mastermind.cpp

# Cleans solution
clean: 
	$(RM) gamehub *.o *~

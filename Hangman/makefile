CC = g++

all: Hangman

# Compiles SimonSays module
Hangman:  Hangman.o
	del _Hangman.o && ren Hangman.o _Hangman.o

# Compiles SimonSays class
Hangman.o:  Hangman.cpp Hangman.h
	$(CC) -c Hangman.cpp

# Cleans solution
clean: 
	$(RM) gamehub *.o *~

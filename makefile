CC = g++

all: gamehub

# Compiles entire app
gamehub:  GameHub.cpp TicTacToe
	$(CC) -o GameHub GameHub.cpp ./TicTacToe/_TicTacToe.o ./libs/dispANSI.o

# Compiles TicTacToe module
TicTacToe: .\TicTacToe\TicTacToe.cpp .\TicTacToe\TicTacToe.h .\TicTacToe\TTTBoard.cpp .\TicTacToe\TTTBoard.h
	+$(MAKE) -C TicTacToe

# Cleans solution
clean: 
	$(RM) gamehub *.o *~

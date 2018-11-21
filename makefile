CC = g++

all: gamehub

# Compiles entire app
gamehub:  GameHub.cpp TicTacToe SimonSays
	$(CC) -o GameHub GameHub.cpp ./TicTacToe/_TicTacToe.o ./SimonSays/_SimonSays.o ./libs/dispANSI.o

# Compiles TicTacToe module
TicTacToe: .\TicTacToe\TicTacToe.cpp .\TicTacToe\TicTacToe.h .\TicTacToe\TTTBoard.cpp .\TicTacToe\TTTBoard.h
	+$(MAKE) -C TicTacToe

SimonSays: .\SimonSays\SimonSays.cpp .\SimonSays\SimonSays.h
	+$(MAKE) -C SimonSays

# Cleans solution
clean: 
	$(RM) gamehub *.o *~

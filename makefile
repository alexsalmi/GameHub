CC = g++

all: gamehub

# Compiles entire app
gamehub:  GameHub.cpp TicTacToe SimonSays Memory ConnectFour
	$(CC) -o GameHub GameHub.cpp ./TicTacToe/_TicTacToe.o ./SimonSays/_SimonSays.o ./Memory/_Memory.o ./ConnectFour/_ConnectFour.o ./libs/dispANSI.o

# Compiles TicTacToe module
TicTacToe: .\TicTacToe\TicTacToe.cpp .\TicTacToe\TicTacToe.h .\TicTacToe\TTTBoard.cpp .\TicTacToe\TTTBoard.h
	+$(MAKE) -C TicTacToe

SimonSays: .\SimonSays\SimonSays.cpp .\SimonSays\SimonSays.h
	+$(MAKE) -C SimonSays

Memory: .\Memory\Memory.cpp .\Memory\Memory.h .\Memory\MemoryBoard.cpp .\Memory\MemoryBoard.h
	+$(MAKE) -C Memory

ConnectFour: .\ConnectFour\ConnectFour.cpp .\ConnectFour\ConnectFour.h .\ConnectFour\CFBoard.cpp .\ConnectFour\CFBoard.h
	+$(MAKE) -C ConnectFour

# Cleans solution
clean: 
	$(RM) gamehub *.o *~

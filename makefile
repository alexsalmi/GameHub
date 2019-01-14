CC = g++

all: gamehub

# Compiles entire app
gamehub:  GameHub.cpp TicTacToe SimonSays Memory ConnectFour Hangman
	$(CC) -o GameHub GameHub.cpp ./TicTacToe/_TicTacToe.o ./SimonSays/_SimonSays.o ./Memory/_Memory.o ./ConnectFour/_ConnectFour.o ./Hangman/_Hangman.o ./libs/dispANSI.o

# Compiles TicTacToe module
TicTacToe: .\TicTacToe\TicTacToe.cpp .\TicTacToe\TicTacToe.h .\TicTacToe\TTTBoard.cpp .\TicTacToe\TTTBoard.h
	+$(MAKE) -C TicTacToe

# Compiles SimonSays module
SimonSays: .\SimonSays\SimonSays.cpp .\SimonSays\SimonSays.h
	+$(MAKE) -C SimonSays

# Compiles Memory module
Memory: .\Memory\Memory.cpp .\Memory\Memory.h .\Memory\MemoryBoard.cpp .\Memory\MemoryBoard.h
	+$(MAKE) -C Memory

# Compiles ConnectFour module
ConnectFour: .\ConnectFour\ConnectFour.cpp .\ConnectFour\ConnectFour.h .\ConnectFour\CFBoard.cpp .\ConnectFour\CFBoard.h
	+$(MAKE) -C ConnectFour

# Compiles Hangman module
Hangman: .\Hangman\Hangman.cpp .\Hangman\Hangman.h
	+$(MAKE) -C Hangman

# Cleans solution
clean: 
	$(RM) gamehub *.o *~

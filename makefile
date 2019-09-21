CC = g++

all: gamehub

# Compiles entire app
gamehub:  main.cpp ./libs/_dispANSI.o ./TicTacToe/_TicTacToe.o ./SimonSays/_SimonSays.o ./Memory/_Memory.o ./ConnectFour/_ConnectFour.o ./Hangman/_Hangman.o ./Mastermind/_Mastermind.o
	$(CC) -o GameHub main.cpp ./TicTacToe/_TicTacToe.o ./SimonSays/_SimonSays.o ./Memory/_Memory.o ./ConnectFour/_ConnectFour.o ./Hangman/_Hangman.o ./Mastermind/_Mastermind.o ./libs/_dispANSI.o

# Compiles TicTacToe module
./TicTacToe/_TicTacToe.o: .\TicTacToe\TicTacToe.cpp .\TicTacToe\TicTacToe.h .\TicTacToe\TTTBoard.cpp .\TicTacToe\TTTBoard.h
	+$(MAKE) -C TicTacToe

# Compiles SimonSays module
./SimonSays/_SimonSays.o: .\SimonSays\SimonSays.cpp .\SimonSays\SimonSays.h
	+$(MAKE) -C SimonSays

# Compiles Memory module
./Memory/_Memory.o: .\Memory\Memory.cpp .\Memory\Memory.h .\Memory\MemoryBoard.cpp .\Memory\MemoryBoard.h
	+$(MAKE) -C Memory

# Compiles ConnectFour module
./ConnectFour/_ConnectFour.o: .\ConnectFour\ConnectFour.cpp .\ConnectFour\ConnectFour.h .\ConnectFour\CFBoard.cpp .\ConnectFour\CFBoard.h
	+$(MAKE) -C ConnectFour

# Compiles Hangman module
./Hangman/_Hangman.o: .\Hangman\Hangman.cpp .\Hangman\Hangman.h
	+$(MAKE) -C Hangman

# Compiles Mastermind module
./Mastermind/_Mastermind.o: .\Mastermind\Mastermind.cpp .\Mastermind\Mastermind.h .\Mastermind\MMBoard.cpp .\Mastermind\MMBoard.h
	+$(MAKE) -C Mastermind

# Compiles Mastermind module
./libs/_dispANSI.o: .\libs\dispANSI.cpp .\libs\dispANSI.h
	+$(MAKE) -C libs

# Cleans solution
clean:
	$(RM) gamehub *.o *~

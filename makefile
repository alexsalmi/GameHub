CC = g++

all: gamehub

# Compiles entire app
gamehub:  GameHub.cpp TicTacToe.o
	$(CC) -o GameHub GameHub.cpp ./TicTacToe/TicTacToe.o ./TicTacToe/TTTBoard.o

# Compiles TicTacToe module
TicTacToe.o:  ./TicTacToe/TicTacToe.cpp ./TicTacToe/TicTacToe.h ./TicTacToe/TTTBoard.o ./TicTacToe/TTTBoard.cpp ./TicTacToe/TTTBoard.h 
	cd TicTacToe && $(CC) -c TicTacToe.cpp TTTBoard.cpp && cd ..

# Cleans solution
clean: 
	$(RM) gamehub *.o *~

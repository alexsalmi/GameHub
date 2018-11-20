CC = g++

all: TicTacToe

# Compiles TicTacToe module
TicTacToe:  TicTacToe.o TTTBoard.o 
	ld -r TicTacToe.o TTTBoard.o -o _TicTacToe.o && del TicTacToe.o && del TTTBoard.o

# Compiles TTTBoard class
TicTacToe.o:  TicTacToe.cpp TicTacToe.h TTTBoard.o
	$(CC) -c TicTacToe.cpp

# Compiles TTTBoard class
TTTBoard.o:  TTTBoard.cpp TTTBoard.h 
	$(CC) -c TTTBoard.cpp

# Cleans solution
clean: 
	$(RM) gamehub *.o *~

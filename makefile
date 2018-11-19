CC = g++

all: gamehub

# Compiles entire app
gamehub:  GameHub.cpp TicTacToe
	$(CC) -o GameHub GameHub.cpp ./TicTacToe/_TicTacToe.o

# Compiles TicTacToe module
TicTacToe:
	+$(MAKE) -C TicTacToe

# Cleans solution
clean: 
	$(RM) gamehub *.o *~

CC = g++

all: ConnectFour

# Compiles ConnectFour module
ConnectFour:  ConnectFour.o CFBoard.o
	ld -r ConnectFour.o CFBoard.o -o _ConnectFour.o && del ConnectFour.o && del CFBoard.o

# Compiles ConnectFour class
ConnectFour.o:  ConnectFour.cpp ConnectFour.h
	$(CC) -c ConnectFour.cpp

# Compiles CFBoard class
CFBoard.o: CFBoard.cpp CFBoard.h
	$(CC) -c CFBoard.cpp


# Cleans solution
clean: 
	$(RM) gamehub *.o *~

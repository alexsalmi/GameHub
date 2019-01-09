CC = g++

all: ConnectFour

# Compiles ConnectFour module
ConnectFour:  ConnectFour.o
	del _ConnectFour.o && ren ConnectFour.o _ConnectFour.o

# Compiles ConnectFour class
ConnectFour.o:  ConnectFour.cpp ConnectFour.h
	$(CC) -c ConnectFour.cpp

# Cleans solution
clean: 
	$(RM) gamehub *.o *~

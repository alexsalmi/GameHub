CC = g++

all: dispANSI

# Compiles SimonSays module
dispANSI:  dispANSI.o
	del _dispANSI.o && ren dispANSI.o _dispANSI.o

# Compiles SimonSays class
dispANSI.o:  dispANSI.cpp dispANSI.h
	$(CC) -c dispANSI.cpp

# Cleans solution
clean:
	$(RM) gamehub *.o *~

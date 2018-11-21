CC = g++

all: SimonSays

# Compiles SimonSays module
SimonSays:  SimonSays.o
	del _SimonSays.o && ren SimonSays.o _SimonSays.o

# Compiles SimonSays class
SimonSays.o:  SimonSays.cpp SimonSays.h
	$(CC) -c SimonSays.cpp

# Cleans solution
clean: 
	$(RM) gamehub *.o *~


CC = g++
#CFLAGS = -pg -Wall -fprofile-arcs -ftest-coverage
CFLAGS = -Wall
OBJDIR = obj

OBJECTS = grid.o main.o

grid.o: grid.cpp
	$(CC) $(CFLAGS) -c  grid.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

fluid: $(OBJECTS)
	$(CC) $(CFLAGS) -o grid.o $(OBJECTS)

all: fluid


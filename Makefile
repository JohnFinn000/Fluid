
CC = g++
#CFLAGS = -pg -Wall -fprofile-arcs -ftest-coverage
CFLAGS = -Wall
OBJDIR = obj

OBJECTS = $(OBJDIR)/grid.o $(OBJDIR)/main.o

all: $(OBJDIR)/fluid

$(OBJDIR)/grid.o: grid.cpp
	$(CC) $(CFLAGS) -c grid.cpp -o $@

$(OBJDIR)/main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o $@

$(OBJDIR)/fluid: $(OBJECTS)
	$(CC) $(CFLAGS) -o fluid $(OBJECTS)


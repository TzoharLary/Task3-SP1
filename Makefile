CC=gcc
CFLAGS=-I.

# Target to compile the entire program
all: StrList

# Compiles the main executable
StrList: Main.o StrList.o
	$(CC) -o StrList Main.o StrList.o

# Compiles Main.c to an object file
Main.o: Main.c StrList.h
	$(CC) -c Main.c $(CFLAGS)

# Compiles StrList.c to an object file
StrList.o: StrList.c StrList.h
	$(CC) -c StrList.c $(CFLAGS)

# Cleans up compiled files
clean:
	rm -f *.o main

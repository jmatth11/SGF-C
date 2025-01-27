CC=clang
CFLAGS=-Wall -Wextra -std=c11
CLIBS=-lSDL3 -lm -pthread
TARGET=main

all:
	$(CC) $(CFLAGS) $(INCLUDES) $(CLIBS) -o $(TARGET) main.c

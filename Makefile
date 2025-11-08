# Makefile for simple C project
CC=gcc
CFLAGS=-Wall -Wextra -O2
SRC=main.c
TARGET=build/main

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o

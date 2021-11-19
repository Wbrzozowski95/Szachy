CC=gcc
CFLAGS=-g -Wall -pthread
DEPS = game_logic.h
OBJ = game_logic.o server.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

serwer: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

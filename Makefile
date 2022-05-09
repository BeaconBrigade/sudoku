all: main

CFLAGS = -g -Wall -c
SRC = *.c
OBJ = *.o
CC = gcc

main: $(OBJ)
	$(CC) $(OBJ) -o $@

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $(SRC)

clean :
	rm -f main $(OBJ)

all: main

CFLAGS = -g -Wall -c
SRC = *.c
OBJ = *.o
CC = gcc

main: $(OBJ)
	$(CC) $(OBJ) -o $@

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) $(SRC)

release-main: $(SRC)
	$(CC) -O3 $(SRC) -o release-main

install: release-main main
	mv release-main ~/.local/bin/c-sudoku

clean :
	rm -f main $(OBJ)

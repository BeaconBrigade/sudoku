all: main

CFLAGS = -g -Wall -c
SRC = *.c
OBJ = *.o

main: $(OBJ)
	gcc $(OBJ) -o $@

$(OBJ): $(SRC)
	gcc $(CFLAGS) $(SRC)

clean :
	rm -f main $(OBJ)

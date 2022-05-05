#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int parser(char *name, int puzzle[81]);
void solver(int puzzle[81]);

void printpuzzle(int puzzle[81])
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			printf("%d", puzzle[i * 9 + j]);
		putchar('\n');
	}
	putchar('\n');
}

/* Handle command line arguments and call parser and solver */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Using %s FILENAME\n", argv[0]);
		return 1;
	}
	
	int puzzle[81];

	if (parser(argv[1], puzzle) == -1)
		return 1;

	printpuzzle(puzzle);
}

/* Read file into puzzle array */
int parser(char *name, int* puzzle)
{
	FILE *src;
	int i;
	char c[2];
	c[1] = '\0';
	
	if ((src = fopen(name, "r")) == NULL)
	{
		fprintf(stderr, "Sudoku: Error loading file.\n");
		return -1;
	}

	/* Read array */
	for (i = 0; i < 81; )
	{
		if ((*c = fgetc(src)) == EOF)
		{
			fprintf(stderr, "Sudoku: Not enough input.\n");
			return -1;
		}
		
		if (isdigit(*c))
			*puzzle++ = atoi(c);
		else if (isspace(*c) || *c == ',')
			continue;
		else
			*puzzle = -1;
		i++;
	}

	return 0;
}

/* Solve puzzle */
void solver(int puzzle[81])
{

}


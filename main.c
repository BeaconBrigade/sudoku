#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int parser(char *name, int puzzle[81]);
void solver(int puzzle[81]);
void printpuzzle(char *loc, int puzzle[81]);

/* Handle command line arguments and call parser and solver */
int main(int argc, char *argv[])
{
	char *outfile = NULL;
	int i = 2;

	/* -o option is set */
	if (argc == 4)
	{
		for (i = 1; i < 3; i++)
			if (!strcmp(argv[i], "-o"))
			{
				outfile = argv[i + 1];
				break;
			}
	}
	else if (argc != 2)
	{
		fprintf(stderr, "Sudoku: using %s FILENAME\n", argv[0]);
		return 1;
	}

	/* Parse input */
	int puzzle[81];

	if (parser(argv[((i == 2) ? 1 : 3)], puzzle) == -1)
		return 1;

	printpuzzle(outfile, puzzle);
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
			*puzzle++ = -1;
		i++;
	}

	fclose(src);
	return 0;
}

/* Solve puzzle */
void solver(int puzzle[81])
{

}

/* Print output to stdout or specified output file */
void printpuzzle(char *loc, int puzzle[81])
{
	FILE *out;

	if (loc == NULL)
		out = stdout;
	else 
	{
		if ((out = fopen(loc, "w")) == NULL)
		{
			fprintf(stderr, "Sudoku: error opening output file");
			exit(1);
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
			fprintf(out, "%d ", puzzle[i * 9 + j]);
		fputc('\n', out);
	}

	if (out != stdout)
		fclose(out);
}

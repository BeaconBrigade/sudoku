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
		fprintf(stderr, "Using %s FILENAME\n", argv[0]);
		return 1;
	}

	/* Parse input */
	int puzzle[81];

	if (parser(argv[((i == 2) ? 1 : 3)], puzzle) == -1)
		return 1;

	solver(puzzle);
	
	printpuzzle(outfile, puzzle);
}

/* Read file into puzzle array */
int parser(char *name, int* puzzle)
{
	FILE *src;
	int i;

	char c;

	if ((src = fopen(name, "r")) == NULL)
	{
		fprintf(stderr, "Sudoku: Error loading file.\n");
		return -1;
	}

	/* Read array */
	for (i = 0; i < 81; )
	{
		if ((c = fgetc(src)) == EOF)
		{
			fprintf(stderr, "Sudoku: Not enough input.\n");
			return -1;
		}
		
		if (isdigit(c))
			*puzzle++ = c - '0';
		else if (isspace(c) || c == ',')
			continue;
		else
			*puzzle++ = 10;
		i++;
	}

	fclose(src);
	return 0;
}

/* Check if current solution still works */
int stillvalid(const int puzzle[81])
{
	int counter[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int i, j, k, offset;

	/* Check each horizontal row */
	for (i = 0; i < 9; i++)
	{
		/* I was trying to avoid nested for loops :/ */
		counter[puzzle[i * 9]]++;
		counter[puzzle[i * 9 + 1]]++;
		counter[puzzle[i * 9 + 2]]++;
		counter[puzzle[i * 9 + 3]]++;
		counter[puzzle[i * 9 + 4]]++;
		counter[puzzle[i * 9 + 5]]++;
		counter[puzzle[i * 9 + 6]]++;
		counter[puzzle[i * 9 + 7]]++;
		counter[puzzle[i * 9 + 8]]++;

		for (j = 0; j < 10; j++)
		{
			if (counter[j] > 1)
				return 0;
			counter[j] = 0;
		}
	}
	
	/* Check each vertical row */
	for (i = 0; i < 9; i++)
	{
		counter[puzzle[i]]++;
		counter[puzzle[9 + i]]++;
		counter[puzzle[18 + i]]++;
		counter[puzzle[27 + i]]++;
		counter[puzzle[36 + i]]++;
		counter[puzzle[45 + i]]++;
		counter[puzzle[54 + i]]++;
		counter[puzzle[63 + i]]++;
		counter[puzzle[72 + i]]++;

		for (j = 0; j < 10; j++)
		{
			if (counter[j] > 1)
				return 0;
			counter[j] = 0;
		}
	}

	offset = 0;
	/* Traverse each row ... I gave up on avoiding nested for loops */
	for (i = 0; i < 3; i++)
	{
		/* Traverse columns */
		for (j = 0; j < 3; j++)
		{
			offset = (i * 27) + (j * 3); /* calculate which square we're at */
			/* Traverse row in each square */
			for (k = 0; k < 3; k++)
			{
				counter[puzzle[offset]]++;
				counter[puzzle[offset + 1]]++;
				counter[puzzle[offset + 2]]++;
				offset += 9;
			}

			for (k = 0; k < 10; k++)
			{
				if (counter[k] > 1)
					return 0;
				counter[k] = 0;
			}
		}
	}
	
	return 1;
}

/* Solve puzzle using backtracing */
void solver(int puzzle[81])
{
	if (!stillvalid(puzzle))
	{
		fprintf(stderr, "Sudoku: input is not valid puzzle.\n");
		exit(1);
	}

	int curpos = 0;
	
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

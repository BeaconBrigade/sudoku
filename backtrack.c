#include <stdio.h>
#include <stdlib.h>
#include "backtrack.h"

static int reject(const int puzzle[81]);
static int isfull(const int puzzle[81]);

typedef struct
{
	int *children[9];
	int candidate[81];
} node;

/* Solve puzzle using backtracking */
void solver(int root[81])
{
	if (reject(root))
	{
		fprintf(stderr, "Sudoku: input is not valid puzzle.\n");
		exit(1);
	}
	/* Valid solution already exits if it's full and not wrong */
	else if (isfull(root))
		return;

	
	
	
}

/* Reject bad solutions */
static int reject(const int puzzle[81])
{
	int counter[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int i, j, k, offset;

	/* Check each horizontal row */
	for (i = 0; i < 9; i++)
	{
		/* I was trying to avoid nested for loops :p */
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
				return 1;
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
				return 1;
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
					return 1;
				counter[k] = 0;
			}
		}
	}
	
	return 0;
}

/* Check if board is full */
static int isfull(const int puzzle[81])
{
	for (int i = 0; i < 81; i++)
		if (puzzle[i] == 10)
			return 0;
    return 1;
}


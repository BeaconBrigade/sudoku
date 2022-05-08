#include <stdio.h>
#include <stdlib.h>
#include "backtrack.h"

static int reject(const Node *cand);
static int accept(const Node *cand);
static Node *first(Node *parent);
static Node *next(Node *parent, const int tochange, const Node *prev);

/* Solve puzzle using backtracking */
Node *backtrack(Node *candidate)
{
	int tochange;
	/* Base cases */
	if (reject(candidate))
		return NULL;
	else if (accept(candidate))
		return candidate;
		
	/* Recursively create tree */
	Node *s = first(candidate);
	Node *p;
	for (tochange = 0; s != NULL; tochange++)
	{
		if ((p = backtrack(s)) != NULL)
			return p;
		p = s;
		s = next(candidate, tochange, p);
	}

	return NULL;
}

static Node *first(Node *parent)
{
	int i, newspace = 1;

	int *puz = (int *) malloc(sizeof(int) * 81);
	Node *child = (Node *) malloc(sizeof(Node));
	child->candidate = puz;
	child->childindex = 0;

	/* Copy parent into child, and set first unset element to 0 */
	for (i = 0; i < 81; i++)
	{
		child->candidate[i] = parent->candidate[i];
		if ((parent->candidate[i] == 10) && newspace)
		{
			child->candidate[i] = 0;
			newspace = 0;
		}
	}

	parent->children[0] = child;
	parent->childindex++;
	return child;
}

/* Generate next possibility */
static Node *next(Node *parent, const int tochange, const Node *prev)
{
	/* If we've enumerated all children of this type */
	if (prev->childindex == 9)
		return NULL;

	int *puz = (int *) malloc(sizeof(int) * 81);
	Node *child = (Node *) malloc(sizeof(Node));
	child->candidate = puz;
	child->childindex = 0;

	int i;

	for (i = 0; i < 81; i++)
		child->candidate[i] = prev->candidate[i];

	child->candidate[tochange]++;
	parent->children[parent->childindex++] = child;

	return child;
}

/* Check if board is full */
static int accept(const Node *cand)
{
	for (int i = 0; i < 81; i++)
		if (cand->candidate[i] == 10)
			return 0;
	return 1;
}

/* Reject bad solutions */
static int reject(const Node *cand)
{
	int counter[11] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int i, j, k, offset;

	/* Check each horizontal row */
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
			counter[cand->candidate[i * 9 + j]]++;

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
		for (j = 0; j < 9; j++)
			counter[cand->candidate[9 * j + i]]++;

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
				counter[cand->candidate[offset]]++;
				counter[cand->candidate[offset + 1]]++;
				counter[cand->candidate[offset + 2]]++;
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


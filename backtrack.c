#include <stdio.h>
#include <stdlib.h>
#include "backtrack.h"

static int reject(const Node *cand);
static int accept(const Node *cand);
static Node *first(Node *parent, int *tochange);
static Node *next(Node *parent, const int tochange, const Node *prev);

/* Solve puzzle using backtracking */
Node *backtrack(Node *candidate)
{
	int tochange = 0;
	/* Base cases */
	if (reject(candidate))
		return NULL;
	else if (accept(candidate))
		return candidate;
		
	/* Recursively create tree */
	Node *s = first(candidate, &tochange);
	Node *p;
	while (s != NULL)
	{
		if ((p = backtrack(s)) != NULL)
			return p;
		p = s;
		s = next(candidate, tochange, p);
	}

	return NULL;
}

/* Generate first extension of parent */
static Node *first(Node *parent, int *tochange)
{
	int i, newspace = 1;

	int *puz = (int *) calloc(81, sizeof(int));
	Node *child = (Node *) malloc(sizeof(Node));
	child->candidate = puz;
	child->childindex = 0;
	for (i = 0; i < 10; i++)
		child->children[i] = NULL;

	/* Copy parent into child, and set first unset element to 1 */
	for (i = 0; i < 81; i++)
	{
		child->candidate[i] = parent->candidate[i];
		if ((parent->candidate[i] == 0) && newspace)
		{
			child->candidate[i] = 1;
			*tochange = i;
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
	if (parent->childindex == 9)
		return NULL;

	int i;

	int *puz = (int *) calloc(81, sizeof(int));
	Node *child = (Node *) malloc(sizeof(Node));
	child->candidate = puz;
	child->childindex = 0;
	for (i = 0; i < 10; i++)
		child->children[i] = NULL;

	for (i = 0; i < 81; i++)
		child->candidate[i] = prev->candidate[i];

	child->candidate[tochange]++;
	parent->children[parent->childindex++] = child;

	return child;
}

/* Release memory from trees that are invalid */
void releasenode(Node *base)
{
	int i;
	if (base == NULL)
		return;

	for (i = 0; i < 10; i++)
	{
		if (base->children[i] == NULL)
			break;
		else
			releasenode(base->children[i]);
	}

	free(base->candidate);
	free(base);
}

/* Check if board is full */
static int accept(const Node *cand)
{
	for (int i = 0; i < 81; i++)
		if (cand->candidate[i] == 0)
			return 0;
	return 1;
}

/* Reject bad solutions */
static int reject(const Node *cand)
{
	int counter[12] = { 69, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 420 };
	int i, j, k, offset;

	/* Check each horizontal row */
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
			counter[cand->candidate[i * 9 + j]]++;

		for (j = 1; j < 11; j++)
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

		for (j = 1; j < 11; j++)
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

			for (k = 1; k < 11; k++)
			{
				if (counter[k] > 1)
					return 1;
				counter[k] = 0;
			}
		}
	}
	
	return 0;
}

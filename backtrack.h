#ifndef BACKTRACK
#define BACKTRACK
typedef struct NODE
{
	int childindex;
	struct NODE *children[10];
	int *candidate;
} Node;

Node *backtrack(Node *root);
void releasenode(Node *base);

#endif
#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node 
{
	int number;
	struct node *left;
	struct node *right;
}NODE;

void Free(NODE *tree);
void PreOrder(NODE *tree);
void AddLeftRight(NODE *tree, int value1, int value2, int value3);
void search(NODE *root, char tree[100]);

int main_11(void) 
{
	int nodeNumber, value1, value2, value3, searchNumber;
	NODE *root, *tree;
	tree = (NODE*)malloc(sizeof(NODE));
	char searchInfomation[100];
	root = tree;
	scanf("%d", &nodeNumber);

	for (int i = 0; i < nodeNumber; i++) 
	{
		scanf("%d", &value1);
		scanf("%d", &value2);
		scanf("%d", &value3);

		if (i == 0) 
		{
			NODE *leftchild = (struct node*)malloc(sizeof(struct node));
			NODE *rightchild = (struct node*)malloc(sizeof(struct node));
			tree->number = value1;
			leftchild->number = value2;
			rightchild->number = value3;
			leftchild->left = NULL;
			leftchild->right = NULL;
			rightchild->left = NULL;
			rightchild->right = NULL;
			if (value2 != 0) 
			{
				root->left = leftchild;
			}
			else 
			{
				free(leftchild);
			}
			if (value3 != 0) 
			{
				root->right = rightchild;
			}
			else 
			{
				free(rightchild);
			}
		}
		else 
		{
			AddLeftRight(root, value1, value2, value3);
		}
	}
	scanf("%d", &searchNumber);
	for (int i = 0; i < searchNumber; i++) 
	{
		getchar();
		scanf("%s", searchInfomation);
		search(root, searchInfomation);
	}
	Free(root);

	return 0;
}

void Free(NODE *tree)
{
	if (tree == NULL)
	{
		return;
	}
	free(tree->left);
	free(tree->right);
	free(tree);
}

void PreOrder(NODE *tree)
{
	if (tree == NULL)
	{
		return;
	}
	printf(" %d", tree->number);
	PreOrder(tree->left);
	PreOrder(tree->right);
}

void AddLeftRight(NODE *tree, int value1, int value2, int value3)
{
	if (tree == NULL)
	{
		return;
	}
	NODE *leftchild = (struct node*)malloc(sizeof(struct node));
	NODE *rightchild = (struct node*)malloc(sizeof(struct node));

	leftchild->number = value2;
	rightchild->number = value3;
	leftchild->left = NULL;
	leftchild->right = NULL;
	rightchild->left = NULL;
	rightchild->right = NULL;

	if (tree->number == value1)
	{
		if (value2 == 0)
		{
			tree->left = NULL;
			free(leftchild);
		}
		else
		{
			tree->left = leftchild;
		}
		if (value3 == 0)
		{
			tree->right = NULL;
			free(rightchild);
		}
		else
		{
			tree->right = rightchild;
		}
	}
	else
	{
		free(leftchild);
		free(rightchild);
	}
	AddLeftRight(tree->left, value1, value2, value3);
	AddLeftRight(tree->right, value1, value2, value3);
}

void search(NODE *root, char tree[100])
{
	printf(" %d", root->number);
	for (int i = 0; i < strlen(tree); i++)
	{
		if (tree[i] == 'R')
		{
			root = root->right;
		}
		else if (tree[i] == 'L')
		{
			root = root->left;
		}
		else
		{
			return;
		}
		printf(" %d", root->number);
	}
	printf("\n");
}
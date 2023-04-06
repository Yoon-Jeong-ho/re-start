//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct node
//{
//	struct node *left;
//	struct node *right;
//	int data;
//}NODE;
//
//void AddLeft(NODE *parent, int Value);
//void AddRight(NODE *parent, int Value);
//
//int main(void)
//{
//	NODE *Parent, *f[8];
//	int num;
//	Parent = (NODE*)malloc(sizeof(NODE));
//	
//	Parent->data = 20;
//	Parent->left = NULL;
//	Parent->right = NULL;
//	AddLeft(Parent, 30);
//	AddRight(Parent, 50);
//	AddLeft(Parent->left, 70);
//	AddRight(Parent->left, 90);
//	AddRight(Parent->right, 120);
//	AddRight(Parent->right->right, 80);
//	AddLeft(Parent->right->right, 130);
//
//	f[0] = Parent;
//	f[1] = Parent->left;
//	f[2] = Parent->right;
//	f[3] = Parent->left->left;
//	f[4] = Parent->left->right;
//	f[5] = Parent->right->right;
//	f[6] = Parent->right->right->left;
//	f[7] = Parent->right->right->right;
//
//	scanf("%d", &num);
//
//	for (int i = 0; i < 8; i++)
//	{
//		if (i == num - 1)
//		{
//			printf("%d", f[i]->data);
//			if (f[i]->left != NULL)
//			{
//				printf(" %d", f[i]->left->data);
//			}
//			if (f[i]->right != NULL)
//			{
//				printf(" %d", f[i]->right->data);
//			}
//			printf("\n");
//			break;
//		}
//		if (i == 7)
//		{
//			printf("-1\n");
//		}
//	}
//
//	for (int i = 0; i < 8; i++)
//	{
//		free(f[i]);
//	}
//	return 0;
//}
//
//void AddLeft(NODE *parent, int Value)
//{
//	NODE *newnode;
//	newnode = (NODE*)malloc(sizeof(NODE));
//	newnode->data = Value;
//	newnode->left = NULL;
//	newnode->right = NULL;
//	parent->left = newnode;
//}
//
//void AddRight(NODE *parent, int Value)
//{
//	NODE *newnode;
//	newnode = (NODE*)malloc(sizeof(NODE));
//	newnode->data = Value;
//	newnode->left = NULL;
//	newnode->right = NULL;
//	parent->right = newnode;
//}



//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct node
//{
//	struct node *left;
//	struct node *right;
//	int id, data;
//}NODE;
//void PreOrder(NODE *tree);
//void InOrder(NODE *tree);
//void PostOrder(NODE *tree);
//void AddLeft(NODE *Root, int Value, int id);
//void AddRight(NODE *Root, int Value, int id);
//void FindTreeId(NODE *tree, int Order, int InputId);
//int main(void)
//{
//	int Order, InputId;
//
//	struct node *Root, *tree;
//	tree = (struct node*)malloc(sizeof(struct node));
//
//	Root = tree;
//	tree->data = 20;
//	tree->id = 1;
//	tree->left = NULL;
//	tree->right = NULL;
//
//	AddLeft(tree, 30, 2);
//	AddRight(tree, 50, 3);
//	AddLeft(tree->left, 70, 4);
//	AddRight(tree->left, 90, 5);
//	AddRight(tree->right, 120, 6);
//	AddLeft(tree->right->right, 130, 7);
//	AddRight(tree->right->right, 80, 8);
//
//	scanf("%d", &Order);
//
//	scanf("%d", &InputId);
//
//	if (1 <= InputId && InputId <= 8)
//	{
//		FindTreeId(Root, Order, InputId);
//	}
//	else 
//	{
//		printf("-1\n");
//	}
//
//	free(Root);
//	free(Root->left);
//	free(Root->right);
//}
//
//void AddLeft(NODE *Root, int Value, int InputId)
//{
//	NODE *newnode;
//	newnode = (NODE*)malloc(sizeof(NODE));
//	newnode->data = Value;
//	newnode->id = InputId;
//	newnode->left = NULL;
//	newnode->right = NULL;
//	Root->left = newnode;
//}
//
//void AddRight(NODE *Root, int Value, int InputId)
//{
//	NODE *newnode;
//	newnode = (NODE*)malloc(sizeof(NODE));
//	newnode->data = Value;
//	newnode->id = InputId;
//	newnode->left = NULL;
//	newnode->right = NULL;
//	Root->right = newnode;
//}
//
//void PreOrder(NODE *tree) 
//{
//	if (tree == NULL) 
//	{
//		return;
//	}
//	printf(" %d", tree->data);
//	PreOrder(tree->left);
//	PreOrder(tree->right);
//}
//
//void InOrder(NODE *tree) 
//{
//	if (tree == NULL) 
//	{
//		return;
//	}
//	InOrder(tree->left);
//	printf(" %d", tree->data);
//	InOrder(tree->right);
//
//}
//
//void PostOrder(NODE *tree)
//{
//	if (tree == NULL)
//	{
//		return;
//	}
//	PostOrder(tree->left);
//	PostOrder(tree->right);
//	printf(" %d", tree->data);
//}
//
//void FindTreeId(NODE *tree, int Order, int InputId)
//{
//	if (tree == NULL)
//	{
//		return;
//	}
//	if (tree->id == InputId) 
//	{
//		if (Order == 1) 
//		{
//			PreOrder(tree);
//		}
//		else if (Order == 2) 
//		{
//			InOrder(tree);
//		}
//		else if (Order == 3) 
//		{
//			PostOrder(tree);
//		}
//	}
//	else 
//	{
//		FindTreeId(tree->left, Order, InputId);
//		FindTreeId(tree->right, Order, InputId);
//	}
//}


//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct node
//{
//	struct node *left;
//	struct node *right;
//	int id, data;
//}NODE;
//
//int PreOrder(NODE *tree);
//void AddLeft(NODE *Root, int Value, int id);
//void AddRight(NODE *Root, int Value, int id);
//void FindTreeId(NODE *tree, int InputId);
//
//int main(void)
//{
//	int Order, InputId;
//
//	struct node *Root, *tree;
//	tree = (struct node*)malloc(sizeof(struct node));
//
//	Root = tree;
//	tree->data = 20;
//	tree->id = 1;
//	tree->left = NULL;
//	tree->right = NULL;
//
//	AddLeft(tree, 30, 2);
//	AddRight(tree, 50, 3);
//	AddLeft(tree->left, 70, 4);
//	AddRight(tree->left, 90, 5);
//	AddRight(tree->right, 120, 6);
//	AddLeft(tree->right->right, 130, 7);
//	AddRight(tree->right->right, 80, 8);
//
//	scanf("%d", &InputId);
//
//	if (1 <= InputId && InputId <= 8)
//	{
//		FindTreeId(Root, InputId);
//	}
//	else 
//	{
//		printf("-1\n");
//	}
//
//	free(Root);
//	free(Root->left);
//	free(Root->right);
//}
//
//void AddLeft(NODE *Root, int Value, int InputId)
//{
//	NODE *newnode;
//	newnode = (NODE*)malloc(sizeof(NODE));
//	newnode->data = Value;
//	newnode->id = InputId;
//	newnode->left = NULL;
//	newnode->right = NULL;
//	Root->left = newnode;
//}
//
//void AddRight(NODE *Root, int Value, int InputId)
//{
//	NODE *newnode;
//	newnode = (NODE*)malloc(sizeof(NODE));
//	newnode->data = Value;
//	newnode->id = InputId;
//	newnode->left = NULL;
//	newnode->right = NULL;
//	Root->right = newnode;
//}
//
//int PreOrder(NODE *tree) 
//{
//	if (tree == NULL) 
//	{
//		return 0;
//	}
//	return tree->data + PreOrder(tree->right) + PreOrder(tree->left);
//}
//
//void FindTreeId(NODE *tree, int InputId)
//{
//	int total = 0;
//	if (tree == NULL)
//	{
//		return;
//	}
//	if (tree->id == InputId) 
//	{
//		total = PreOrder(tree);
//		printf("%d", total);
//	}
//	else 
//	{
//		FindTreeId(tree->left, InputId);
//		FindTreeId(tree->right, InputId);
//	}
//}


#define	_CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node {
	struct node* left;
	char elem[100];
	struct node* right;
	struct node* up;
}node;

void buildDecisionTree(node* head);
void runDecisionTree(node* head);
int treeDepth(node* a);
node* creatNode(node* a);
void init(node* a);

int main() {
	node* head = (node*)malloc(sizeof(node)); // ��� �ʱ�ȭ;
	init(head);
	printf("***Let��s build a dichotomous QA system\n");
	buildDecisionTree(head);// Ʈ������� �Լ�
	printf("Tree complete.Now Running!!\n");
	for (int i = 0; i < 3; i++) runDecisionTree(head);//Ʈ�� ȣ���Լ�
	free(head); // �Ҵ�����
	return 0;
}

void buildDecisionTree(node* currentnode) {
	printf("Enter question:");
	scanf("%[^\n]%*c", currentnode->elem);//���� �о ����ֱ�
	printf("Question if yes to'%s'?", currentnode->elem);//yes�� �� Ʈ�� ������ ���
	char command[4];
	scanf("%s", command);//����
	getchar();
	if (command[0] == 'y') {
		if (treeDepth(currentnode) >= 4) {// ũ�Ⱑ �ʰ��� ���
			printf("�ʿ��� ������ �ʰ� �߽��ϴ�. Ʈ���� ���̰� 3~5�� �ǵ��� �����Ͻʽÿ�");
			exit(1);//������ ��������
		}
		currentnode->left = creatNode(currentnode);
		buildDecisionTree(currentnode->left);// ���ο� ��忡 ���ؼ� ��� �Ѵ�.
	}
	else /*if (command[0] == 'N')*/ {//�� �̻� �������� �����Ƿ� ���� �̸��� �ش�.
		if (treeDepth(currentnode) < 2) { // 3�� �ȵǴ� ���
			printf("�ʿ��� ������ �� ä���� �� �߽��ϴ�. Ʈ���� ���̰� 3~5�� �ǵ��� �����Ͻʽÿ�");
			exit(1);//������ ��������
		}
		printf("Enter descision:");
		currentnode->left = creatNode(currentnode);
		scanf("%[^\n]%*c", currentnode->left->elem);//���� ���� �ޱ�
	}
	printf("Question if no to'%s'?", currentnode->elem);//���⵵ Ʈ�� �� ������ ���
	scanf("%s", command);//������
	getchar();
	if (command[0] == 'y') {
		if (treeDepth(currentnode) >= 4) {// ũ�Ⱑ �ʰ��� ���
			printf("�ʿ��� ������ �ʰ� �߽��ϴ�. Ʈ���� ���̰� 3~5�� �ǵ��� �����Ͻʽÿ�");
			exit(1);//������ ��������
		}
		currentnode->right = creatNode(currentnode);
		buildDecisionTree(currentnode->right);
	}
	else /*if (command[0] == 'N')*/ {
		if (treeDepth(currentnode) < 2) { // 3�� �ȵǴ� ���
			printf("�ʿ��� ������ �� ä���� �� �߽��ϴ�. Ʈ���� ���̰� 3~5�� �ǵ��� �����Ͻʽÿ�");
			exit(1);//������ ��������
		}
		printf("Enter descision:");
		currentnode->right = creatNode(currentnode);
		scanf("%[^\n]%*c", currentnode->right->elem);//���� ���� �ޱ�
	}
}

int treeDepth(node* prevnode) {//Ʈ�� ���� ���ϴ� �Լ�
	int height = 0; // ���θ� ������ 0���̴ϱ�
	while (prevnode->up != NULL) {//�Ѹ����� ��� �ö󰣴�.
		prevnode = prevnode->up;
		height++;
	}
	return height;
}

void runDecisionTree(node* head) {
	while (head->left != NULL || head->right != NULL) {
		printf("%s", head->elem);
		char command[4];
		scanf("%s", command);
		if (command[0] == 'y') {//��������
			if (head->left == NULL) {
				printf("���� �κ��� ������ϴ�. �ٽ� ���ÿ�\n");//������ ������ ��� ���´�.
				continue;
			}
			head = head->left;
		}
		else if (command[0] == 'n') {//������ ����
			if (head->right == NULL) {
				printf("���� �κ��� ������ϴ�. �ٽ� ���ÿ�\n");
				continue;
			}
			head = head->right;
		}
	}
	printf("%s\n", head->elem);
}

node* creatNode(node* prevnode) {//��� ����� �Լ�
	node* newnode;// ���ο� ���
	newnode = (node*)malloc(sizeof(node));
	if (newnode == NULL) { // ����ó��
		printf("Memory allocation failed.\n");
		exit(1);
	}
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->up = prevnode;
	return newnode;
}

void init(node* head) {
	head->left = NULL;
	head->right = NULL;
	head->up = NULL;
}
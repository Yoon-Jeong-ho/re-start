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
	node* head = (node*)malloc(sizeof(node)); // 헤드 초기화;
	init(head);
	printf("***Let’s build a dichotomous QA system\n");
	buildDecisionTree(head);// 트리만들기 함수
	printf("Tree complete.Now Running!!\n");
	for (int i = 0; i < 3; i++) runDecisionTree(head);//트리 호출함수
	free(head); // 할당해제
	return 0;
}

void buildDecisionTree(node* currentnode) {
	printf("Enter question:");
	scanf("%[^\n]%*c", currentnode->elem);//질문 읽어서 집어넣기
	printf("Question if yes to'%s'?", currentnode->elem);//yes에 또 트리 만들지 물어봄
	char command[4];
	scanf("%s", command);//왼쪽
	getchar();
	if (command[0] == 'y') {
		if (treeDepth(currentnode) >= 4) {// 크기가 초과된 경우
			printf("필요한 조건을 초과 했습니다. 트리의 깊이가 3~5가 되도록 설정하십시오");
			exit(1);//오류시 강제종료
		}
		currentnode->left = creatNode(currentnode);
		buildDecisionTree(currentnode->left);// 새로운 노드에 대해서 재귀 한다.
	}
	else /*if (command[0] == 'N')*/ {//더 이상 진행하지 않으므로 음식 이름을 준다.
		if (treeDepth(currentnode) < 2) { // 3이 안되는 경우
			printf("필요한 조건을 다 채우지 못 했습니다. 트리의 깊이가 3~5가 되도록 설정하십시오");
			exit(1);//오류시 강제종료
		}
		printf("Enter descision:");
		currentnode->left = creatNode(currentnode);
		scanf("%[^\n]%*c", currentnode->left->elem);//음식 종류 받기
	}
	printf("Question if no to'%s'?", currentnode->elem);//여기도 트리 더 만들지 물어봄
	scanf("%s", command);//오른쪽
	getchar();
	if (command[0] == 'y') {
		if (treeDepth(currentnode) >= 4) {// 크기가 초과된 경우
			printf("필요한 조건을 초과 했습니다. 트리의 깊이가 3~5가 되도록 설정하십시오");
			exit(1);//오류시 강제종료
		}
		currentnode->right = creatNode(currentnode);
		buildDecisionTree(currentnode->right);
	}
	else /*if (command[0] == 'N')*/ {
		if (treeDepth(currentnode) < 2) { // 3이 안되는 경우
			printf("필요한 조건을 다 채우지 못 했습니다. 트리의 깊이가 3~5가 되도록 설정하십시오");
			exit(1);//오류시 강제종료
		}
		printf("Enter descision:");
		currentnode->right = creatNode(currentnode);
		scanf("%[^\n]%*c", currentnode->right->elem);//음식 종류 받기
	}
}

int treeDepth(node* prevnode) {//트리 깊이 구하는 함수
	int height = 0; // 본인만 있으면 0층이니까
	while (prevnode->up != NULL) {//뿌리까지 계속 올라간다.
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
		if (command[0] == 'y') {//왼쪽진행
			if (head->left == NULL) {
				printf("없는 부분을 골랐습니다. 다시 고르시오\n");//오류가 생겼을 경우 나온다.
				continue;
			}
			head = head->left;
		}
		else if (command[0] == 'n') {//오른쪽 진행
			if (head->right == NULL) {
				printf("없는 부분을 골랐습니다. 다시 고르시오\n");
				continue;
			}
			head = head->right;
		}
	}
	printf("%s\n", head->elem);
}

node* creatNode(node* prevnode) {//노드 만들기 함수
	node* newnode;// 새로운 노드
	newnode = (node*)malloc(sizeof(node));
	if (newnode == NULL) { // 예외처리
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
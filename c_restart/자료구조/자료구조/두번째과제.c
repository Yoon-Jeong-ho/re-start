#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>

typedef struct node {
	struct node* couponnext;
	struct node* usernext;
	int couponnum;
	char username;
}node;

typedef struct {
	node* userhead[5];
	node* couponhead[4];
}list;

void init(list* L);
void addShare(list*L,int num, char user);
void removeShare(list* L, int num, char user);
void traverseShareElement(list* L, char user);
void traverseShareGroup(list* L, int num);

int main() {
	list* L;
	L = (list*)malloc(sizeof(list)); // ����Ʈ �����Ҵ�
	init(L); // ����Ʈ �ʱ�ȭ
	char cmd, user; 
	int num;
	while (1){
		scanf("%c", &cmd); // Ŀ�ǵ� �Է�
		switch (cmd) {
		case 'a' :
			scanf("%d %c", &num, &user);
			addShare(L, num-1, user);
			break;
		case 'r':
			scanf("%d %c", &num, &user);
			removeShare(L, num-1, user);
			break;
		case 'e':
			scanf("%c %c",&user, &user);
			traverseShareElement(L,user);
			break;
		case 'g':
			scanf("%d", &num);
			traverseShareGroup(L,num-1);
			break;
		case 'q':
			return 0;
		}
	}
	free(L);

	return 0;
}

void init(list *L) { // �ʱ�ȭ �����ֱ�
	struct node** userhead = (node**)malloc(sizeof(node*));
	struct node** couponhead = (node**)malloc(sizeof(node*));

	for (int i = 0; i < 5; i++) {
		userhead[i] = (node*)malloc(sizeof(node));
		L->userhead[i] = userhead[i];
		userhead[i]->usernext = userhead[i];
		userhead[i]->username = 'A' + i;
		userhead[i]->couponnum = 0;
		userhead[i]->couponnext = NULL;
	}
	for (int i = 0; i < 4; i++) {
		couponhead[i] = (node*)malloc(sizeof(node));
		L->couponhead[i] = couponhead[i];
		couponhead[i]->couponnext = couponhead[i];
		couponhead[i]->username = 0;
		couponhead[i]->couponnum = i+1;
		couponhead[i]->usernext = NULL;
	}

}
void addShare(list* L, int num, char user) {
	user = user - 'A'; // 0 1 2 3���� ����� ���� A���ֱ�
	struct node* nextnode;
	node* couponnode, * usernode;
	nextnode = (struct node*)malloc(sizeof(struct node)); // ���� ���� ��� �Ҵ�
	couponnode = L->couponhead[num]; // ���� ��忡 ������� �ֱ�
	usernode = L->userhead[user]; // ��忡 ���� �̸���� �ֱ�
	nextnode->username = user+'A'; // ��忡 �� ���� �ֱ�
	nextnode->couponnum = num+1; // ��忡 �� ���� �ֱ�
	nextnode->couponnext = couponnode->couponnext; // �� ����� ���� �������� ���� ���� ���� �̾��ֱ�
	nextnode->usernext = usernode->usernext; // ���� ����
	couponnode->couponnext = nextnode; // ���� ���� ���� �̾��ֱ�
	usernode->usernext = nextnode; // ���� ����
	printf("OK\n");
}

void removeShare(list* L, int num, char user) {
	user = user - 'A'; // ��忡�� 0 1 2 3 ���� �Ǿ� �����Ƿ�
	node* removenode, * couponnode, * usernode;
	couponnode = L->couponhead[num]; // ���� ���� ������ ���
	usernode = L->userhead[user]; // ���� ���� �̸� ������ ���
	removenode = L->userhead[user];
	while (removenode->couponnum != num+1) { // ��� �������鼭 ���� ���� �̸� ���� ã��
		usernode = removenode; // ���� ��带 ã�� ���ؼ� ��尡 �Ѿ�� ���� ������ �ѱ��
		removenode = removenode->usernext; // ��� ��ĭ�� �ѱ�鼭 �ѹ� �� ã�´�.
	}
	removenode = L->couponhead[num];
	while (removenode->username != user+'A') { // ���� �Ȱ��� ������� ã�´�.
		couponnode = removenode;
		removenode = removenode->couponnext;
	}
	usernode->usernext = removenode->usernext; // ���� ã�����ϱ� ������ ��� �ڸ��� ���� ��带 ���� ���� �������ֱ�
	couponnode->couponnext = removenode->couponnext; // ���� ����.
	free(removenode); // �Ҵ����� �޸� ���ֱ�
	printf("OK\n");
}

void traverseShareElement(list* L, char user) {
	node* usernode;
	user = user - 'A'; // 0 1 2 3 �̹Ƿ�...
	usernode = L->userhead[user]; // ���� ���� ��� �ű��
	usernode = usernode->usernext; // ù��°�� ���̹Ƿ� ���� ������ ����
	while (usernode->couponnum != 0) { // 0�̸� ��
		printf("%d ", usernode->couponnum); // ���� ���� ���� ������
		usernode = usernode->usernext; // ���� ����
	}
	printf("\n");
}

void traverseShareGroup(list* L, int num) {
	node* couponnode;
	couponnode = L->couponhead[num]; // num�� ��� �ѱ��
	couponnode = couponnode->couponnext; // ���⵵ ó���� �� ������ �ѱ��
	while (couponnode->username != 0) { 
		printf("%c ", couponnode->username); // ������ ���ֱ�
		couponnode = couponnode->couponnext; // ���� ���
	}
	printf("\n");
}
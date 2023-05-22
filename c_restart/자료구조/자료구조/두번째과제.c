//#define _crt_secure_no_warnings 
//
//#include<stdio.h>
//#include<stdlib.h>
//
//typedef struct node {
//	struct node* couponnext;
//	struct node* usernext;
//	int couponnum;
//	char username;
//}node;
//
//typedef struct {
//	node* userhead[5];
//	node* couponhead[4];
//}list;
//
//void init(list* l);
//void addshare(list*l,int num, char user);
//void removeshare(list* l, int num, char user);
//void traverseshareelement(list* l, char user);
//void traversesharegroup(list* l, int num);
//
//int main() {
//	list* l;
//	l = (list*)malloc(sizeof(list)); // ����Ʈ �����Ҵ�
//	init(l); // ����Ʈ �ʱ�ȭ
//	char cmd, user; 
//	int num;
//	while (1){
//		scanf("%c", &cmd); // Ŀ�ǵ� �Է�
//		switch (cmd) {
//		case 'a' :
//			scanf("%d %c", &num, &user);
//			addshare(l, num-1, user);
//			break;
//		case 'r':
//			scanf("%d %c", &num, &user);
//			removeshare(l, num-1, user);
//			break;
//		case 'e':
//			scanf("%c %c",&user, &user);
//			traverseshareelement(l,user);
//			break;
//		case 'g':
//			scanf("%d", &num);
//			traversesharegroup(l,num-1);
//			break;
//		case 'q':
//			return 0;
//		}
//	}
//	free(l);
//
//	return 0;
//}
//
//void init(list *l) { // �ʱ�ȭ �����ֱ�
//	struct node** userhead = (node**)malloc(sizeof(node*));
//	struct node** couponhead = (node**)malloc(sizeof(node*));
//
//	for (int i = 0; i < 5; i++) {
//		userhead[i] = (node*)malloc(sizeof(node));
//		l->userhead[i] = userhead[i];
//		userhead[i]->usernext = userhead[i];
//		userhead[i]->username = 'a' + i;
//		userhead[i]->couponnum = 0;
//		userhead[i]->couponnext = null;
//	}
//	for (int i = 0; i < 4; i++) {
//		couponhead[i] = (node*)malloc(sizeof(node));
//		l->couponhead[i] = couponhead[i];
//		couponhead[i]->couponnext = couponhead[i];
//		couponhead[i]->username = 0;
//		couponhead[i]->couponnum = i+1;
//		couponhead[i]->usernext = null;
//	}
//
//}
//void addshare(list* l, int num, char user) {
//	user = user - 'a'; // 0 1 2 3���� ����� ���� a���ֱ�
//	struct node* nextnode;
//	node* couponnode, * usernode;
//	nextnode = (struct node*)malloc(sizeof(struct node)); // ���� ���� ��� �Ҵ�
//	couponnode = l->couponhead[num]; // ���� ��忡 ������� �ֱ�
//	usernode = l->userhead[user]; // ��忡 ���� �̸���� �ֱ�
//	nextnode->username = user+'a'; // ��忡 �� ���� �ֱ�
//	nextnode->couponnum = num+1; // ��忡 �� ���� �ֱ�
//	nextnode->couponnext = couponnode->couponnext; // �� ����� ���� �������� ���� ���� ���� �̾��ֱ�
//	nextnode->usernext = usernode->usernext; // ���� ����
//	couponnode->couponnext = nextnode; // ���� ���� ���� �̾��ֱ�
//	usernode->usernext = nextnode; // ���� ����
//	printf("ok\n");
//}
//
//void removeshare(list* l, int num, char user) {
//	user = user - 'a'; // ��忡�� 0 1 2 3 ���� �Ǿ� �����Ƿ�
//	node* removenode, * couponnode, * usernode;
//	couponnode = l->couponhead[num]; // ���� ���� ������ ���
//	usernode = l->userhead[user]; // ���� ���� �̸� ������ ���
//	removenode = l->userhead[user];
//	while (removenode->couponnum != num+1) { // ��� �������鼭 ���� ���� �̸� ���� ã��
//		usernode = removenode; // ���� ��带 ã�� ���ؼ� ��尡 �Ѿ�� ���� ������ �ѱ��
//		removenode = removenode->usernext; // ��� ��ĭ�� �ѱ�鼭 �ѹ� �� ã�´�.
//	}
//	removenode = l->couponhead[num];
//	while (removenode->username != user+'a') { // ���� �Ȱ��� ������� ã�´�.
//		couponnode = removenode;
//		removenode = removenode->couponnext;
//	}
//	usernode->usernext = removenode->usernext; // ���� ã�����ϱ� ������ ��� �ڸ��� ���� ��带 ���� ���� �������ֱ�
//	couponnode->couponnext = removenode->couponnext; // ���� ����.
//	free(removenode); // �Ҵ����� �޸� ���ֱ�
//	printf("ok\n");
//}
//
//void traverseshareelement(list* l, char user) {
//	node* usernode;
//	user = user - 'a'; // 0 1 2 3 �̹Ƿ�...
//	usernode = l->userhead[user]; // ���� ���� ��� �ű��
//	usernode = usernode->usernext; // ù��°�� ���̹Ƿ� ���� ������ ����
//	while (usernode->couponnum != 0) { // 0�̸� ��
//		printf("%d ", usernode->couponnum); // ���� ���� ���� ������
//		usernode = usernode->usernext; // ���� ����
//	}
//	printf("\n");
//}
//
//void traversesharegroup(list* l, int num) {
//	node* couponnode;
//	couponnode = l->couponhead[num]; // num�� ��� �ѱ��
//	couponnode = couponnode->couponnext; // ���⵵ ó���� �� ������ �ѱ��
//	while (couponnode->username != 0) { 
//		printf("%c ", couponnode->username); // ������ ���ֱ�
//		couponnode = couponnode->couponnext; // ���� ���
//	}
//	printf("\n");
//}
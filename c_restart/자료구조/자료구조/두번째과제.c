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
//	l = (list*)malloc(sizeof(list)); // 리스트 동적할당
//	init(l); // 리스트 초기화
//	char cmd, user; 
//	int num;
//	while (1){
//		scanf("%c", &cmd); // 커맨드 입력
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
//void init(list *l) { // 초기화 시켜주기
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
//	user = user - 'a'; // 0 1 2 3으로 만들기 위해 a빼주기
//	struct node* nextnode;
//	node* couponnode, * usernode;
//	nextnode = (struct node*)malloc(sizeof(struct node)); // 새로 만들 노드 할당
//	couponnode = l->couponhead[num]; // 쿠폰 노드에 쿠폰헤드 넣기
//	usernode = l->userhead[user]; // 노드에 유져 이름헤드 넣기
//	nextnode->username = user+'a'; // 노드에 값 집어 넣기
//	nextnode->couponnum = num+1; // 노드에 값 집어 넣기
//	nextnode->couponnext = couponnode->couponnext; // 뒤 노드의 원래 다음노드랑 새로 생긴 노드랑 이어주기
//	nextnode->usernext = usernode->usernext; // 위와 같다
//	couponnode->couponnext = nextnode; // 이제 이전 노드랑 이어주기
//	usernode->usernext = nextnode; // 위와 같다
//	printf("ok\n");
//}
//
//void removeshare(list* l, int num, char user) {
//	user = user - 'a'; // 노드에는 0 1 2 3 으로 되어 있으므로
//	node* removenode, * couponnode, * usernode;
//	couponnode = l->couponhead[num]; // 여긴 쿠폰 움직일 노드
//	usernode = l->userhead[user]; // 여긴 유저 이름 움직일 노드
//	removenode = l->userhead[user];
//	while (removenode->couponnum != num+1) { // 계속 내려가면서 쿠폰 에서 이름 정보 찾기
//		usernode = removenode; // 이전 노드를 찾기 위해서 노드가 넘어가기 전의 정보를 넘긴다
//		removenode = removenode->usernext; // 노드 한칸을 넘기면서 한번 더 찾는다.
//	}
//	removenode = l->couponhead[num];
//	while (removenode->username != user+'a') { // 위와 똑같은 방식으로 찾는다.
//		couponnode = removenode;
//		removenode = removenode->couponnext;
//	}
//	usernode->usernext = removenode->usernext; // 이제 찾았으니까 리무브 노드 자리의 다음 노드를 이전 노드로 연결해주기
//	couponnode->couponnext = removenode->couponnext; // 위와 같다.
//	free(removenode); // 할당해준 메모리 없애기
//	printf("ok\n");
//}
//
//void traverseshareelement(list* l, char user) {
//	node* usernode;
//	user = user - 'a'; // 0 1 2 3 이므로...
//	usernode = l->userhead[user]; // 유저 노드로 헤드 옮기기
//	usernode = usernode->usernext; // 첫번째는 빈값이므로 다음 노드부터 시작
//	while (usernode->couponnum != 0) { // 0이면 끝
//		printf("%d ", usernode->couponnum); // 가진 쿠폰 숫자 프린팅
//		usernode = usernode->usernext; // 다음 노드로
//	}
//	printf("\n");
//}
//
//void traversesharegroup(list* l, int num) {
//	node* couponnode;
//	couponnode = l->couponhead[num]; // num번 헤드 넘기기
//	couponnode = couponnode->couponnext; // 여기도 처음엔 값 없으니 넘기기
//	while (couponnode->username != 0) { 
//		printf("%c ", couponnode->username); // 프린팅 해주기
//		couponnode = couponnode->couponnext; // 다음 노드
//	}
//	printf("\n");
//}
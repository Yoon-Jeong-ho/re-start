//#define _CRT_SECURE_NO_WARNINGS 
//
//#include<stdio.h>
//#include<stdlib.h>
//
//typedef struct node {
//    char elem;
//    struct node* next; // 다음 노드 주소
//    struct node* prev; // 이전 노드 주소
//}node;
//
//typedef struct list{
//   node* head; // 머리
//   int position;// 리스트 길이
//   node* tail; // 끝
//}list;
//
//void init(list* lptr);
//void addnode(list* lptr, int r,char e);
//void deletnode(list* lprt, int r);
//void getnode(list* lprt,int r);
//void printnode(list* lprt);
//
//int main_05_50_05_90() {
//    int num, count = 1, r;
//    char ch, e;
//    list* L;
//    L = (list*)malloc(sizeof(list));
//    init(L);
//    scanf("%d", &num);
//    while (count <= num) {
//        scanf("%c %c", &ch, &ch);
//        if (ch == 'A') {
//            scanf("%d %c", &r, &e);
//            addnode(L, r, e);
//        }
//        else if (ch == 'D') {
//            scanf("%d", &r);
//            deletnode(L, r);
//
//        }
//        else if (ch == 'P') {
//            printnode(L);
//        }
//        else if (ch == 'G') {
//            scanf("%d", &r);
//            getnode(L,r);
//        }
//        else printf("invalid position\n");
//        count++;
//    }
//	return 0;
//}
//
//void init(list* lptr) // 리스트 초기화하고 리스트 길이에 2 집어넣기
//{
//   node* ohead, *otail;
//   ohead = (node*)malloc(sizeof(node));
//   otail = (node*)malloc(sizeof(node));
//
//   lptr->head = ohead;
//   ohead->prev = NULL;
//   ohead->next = otail;
//
//
//   lptr->tail = otail;
//   otail->next = NULL;
//   otail->prev = ohead;
//
//   lptr->position = 2;
//}
//
//void addnode(list* lptr, int r, char e) {
//    int tposi;
//    //노드를 추가할 위치가 올바르지 않을 경우 error출력
//    if ((lptr->position) - 1 < r){
//      printf("invalid position\n");
//      return;
//    }
//    node* tmp;
//    tmp = lptr->head;
//    //새로운 노드를 동적할당
//    struct node* newnode;
//    newnode = (struct node*)malloc(sizeof(struct node));
//    newnode->elem = e;
//    //for문을 돌아 새 노드의 자리를 찾음
//    for (int i = 0; i < r; i++)tmp = tmp->next;
//    newnode->next = tmp;
//    newnode->prev = tmp->prev;
//    tmp->prev = newnode;
//    tmp = newnode->prev;
//    tmp->next = newnode;
//    lptr->position++;
//
//}
//void deletnode(list *lptr, int r) {
//    int tposi;
//    if ((lptr->position) - 2 < r){
//        printf("invalid position\n");
//        return;
//    }
//    node* tmp, *ptemp, *ntemp;
//    tmp = lptr->head;
//    //for문을 돌아 위치 찾기
//    for (int i = 0; i < r; i++) tmp = tmp->next;
//    ptemp = tmp->prev;
//    ntemp = tmp->next;
//    ptemp->next = ntemp;
//    ntemp->prev = ptemp;
//    free(tmp);//동적할당 해제
//    tposi = (lptr->position);//리스트의 길이도 1 줄여줌
//    tposi--;
//    lptr->position = tposi;
//}
//
//void getnode(list * lptr, int r) {
//       node* temp;
//       temp = lptr->head;
//       
//       //입력받은 위치가 올바르지 않을 때
//       if ((lptr->position) - 2 < r) 
//       {
//          printf("invalid position\n");
//          return;
//       }
//       //위치 찾기
//       for (int i = 0; i < r; i++) 
//       {
//          temp = temp->next;
//       }
//       //해당위치의 노듸의 값만 출력
//       printf("%c\n", temp->elem);
//
//}
//void printnode(list *lptr){
//    node* temp;
//    temp = lptr->head;
//    //노드를 한 번 옮긴 뒤 출력
//    for (int i = 0; i < (lptr->position) - 2; i++) {
//        temp = temp->next;
//        printf("%c", temp->elem);
//    }
//    printf("\n");
//}

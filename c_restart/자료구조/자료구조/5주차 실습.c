//#define _CRT_SECURE_NO_WARNINGS 
//
//#include<stdio.h>
//#include<stdlib.h>
//
//typedef struct node {
//    char elem;
//    struct node* next; // ���� ��� �ּ�
//    struct node* prev; // ���� ��� �ּ�
//}node;
//
//typedef struct list{
//   node* head; // �Ӹ�
//   int position;// ����Ʈ ����
//   node* tail; // ��
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
//void init(list* lptr) // ����Ʈ �ʱ�ȭ�ϰ� ����Ʈ ���̿� 2 ����ֱ�
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
//    //��带 �߰��� ��ġ�� �ùٸ��� ���� ��� error���
//    if ((lptr->position) - 1 < r){
//      printf("invalid position\n");
//      return;
//    }
//    node* tmp;
//    tmp = lptr->head;
//    //���ο� ��带 �����Ҵ�
//    struct node* newnode;
//    newnode = (struct node*)malloc(sizeof(struct node));
//    newnode->elem = e;
//    //for���� ���� �� ����� �ڸ��� ã��
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
//    //for���� ���� ��ġ ã��
//    for (int i = 0; i < r; i++) tmp = tmp->next;
//    ptemp = tmp->prev;
//    ntemp = tmp->next;
//    ptemp->next = ntemp;
//    ntemp->prev = ptemp;
//    free(tmp);//�����Ҵ� ����
//    tposi = (lptr->position);//����Ʈ�� ���̵� 1 �ٿ���
//    tposi--;
//    lptr->position = tposi;
//}
//
//void getnode(list * lptr, int r) {
//       node* temp;
//       temp = lptr->head;
//       
//       //�Է¹��� ��ġ�� �ùٸ��� ���� ��
//       if ((lptr->position) - 2 < r) 
//       {
//          printf("invalid position\n");
//          return;
//       }
//       //��ġ ã��
//       for (int i = 0; i < r; i++) 
//       {
//          temp = temp->next;
//       }
//       //�ش���ġ�� ����� ���� ���
//       printf("%c\n", temp->elem);
//
//}
//void printnode(list *lptr){
//    node* temp;
//    temp = lptr->head;
//    //��带 �� �� �ű� �� ���
//    for (int i = 0; i < (lptr->position) - 2; i++) {
//        temp = temp->next;
//        printf("%c", temp->elem);
//    }
//    printf("\n");
//}

#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>

typedef struct {
	    char elem;
	    struct node* next; // ���� ��� �ּ� ����
	    struct node* prev; // ���� ��� �ּ� ����
}node;

typedef struct {
	node* head;
	int lenlist;
	node* tail;
}list;

void addnode(list* lptr, int r, char e);
void deletnode(list* lprt, int r);
void getnode(list* lprt, int r);
void printnode(list* lprt);

int main_241241() {
    int num, count = 1, r;
    char ch, e;
    list* List;
    List = (list*)malloc(sizeof(list));
    node* head, * tail;
    head = (node*)malloc(sizeof(node)); // �ص� ��� ����
    tail = (node*)malloc(sizeof(node)); // ���� ��� ����
    List->head = head; //����Ʈ ��忡 ��� ���� ����
    head->prev = NULL;// �Ӹ� �տ��� �ƹ��͵� �����ϱ�
    head->next = tail;
    List->tail = tail;// �Ȱ��� ���� ������ ����
    tail->next = NULL; // ���� �ڿ��� �ƹ��͵� �����ϱ�
    tail->prev = head;
    List->lenlist = 2;// �Ӹ��� ���� ���� �ؼ� 2��
    scanf("%d", &num); // �ݺ��� Ƚ�� �Է¹ޱ� 
    while (count <= num) {
        scanf("%c %c", &ch, &ch);// ù��° �Է¿� ���� �Է¹޾Ƽ� �ι� �Է� ����
        if (ch == 'A') { // add�� ���
            scanf("%d %c", &r, &e); // ���� ���̶�, �����Է¹ޱ�
            addnode(List, r, e);
        }
        else if (ch == 'D') { //delet�� ���
            scanf("%d", &r); // ���� �� �Է¹ޱ�
            deletnode(List, r);

        }
        else if (ch == 'P') { // print�� ���
            printnode(List);
        }
        else if (ch == 'G') { //getnode�ϰ��
            scanf("%d", &r); // �ҷ��� �� ã��
            getnode(List, r); 
        }
        else printf("invalid position\n");// ���ܻ�Ȳ ó��
        count++;// ���ѷ��� �ȵǰ� ī��Ʈ �ѹ���
    }
	return 0;
}


void addnode(list* List, int r, char e) { // r�� �� ��, e�� �� ����
    if (r <1 || r> List->lenlist-1) { // 0�� �ȵǴ� ��쳪 ������ ��� ��� ����ó��
        printf("invalid position\n"); // ���ܹ���
        return 0; // �Լ� ��
    }
    node* tmp; // ������ �� ���� �����
    tmp = List->head; // ������ �ص� �ּ� �ֱ�
    for (int i = 0; i < r; i++) tmp = tmp->next; // r ��� ã�ư���
    node* prevnode; // ���� ��� ����
    prevnode = (struct node*)malloc(sizeof(node)); // ��� �����Ҵ� 
    prevnode->next = tmp; // ���� ����� ������ ã�ư� ���
    prevnode->prev = tmp->prev; // ���� ����� ������ ã�ư� ����� ����
    tmp->prev = prevnode; // ���� ���� ã�ư� ����� ����
    tmp = prevnode->prev;// ���� ����� �������� tmp �̵�
    tmp->next = prevnode; // tmp�� ������ ���� ��忡 �̵�
    prevnode->elem = e;
    List->lenlist++; // ���������ϱ� ����Ʈ ���� ���ϱ�
}
void deletnode(list* List, int r) {
    if (r <1 || r> List->lenlist - 2) { // 0�� �ȵǴ� ��쳪 ������ ��� ��� ����ó��
        printf("invalid position\n"); // ���ܹ���
        return 0; // �Լ� ��
    }
    node* tmp, * ntmp, * ptmp; // ������ �� ���� �����
    tmp = List->head; // ������ �ص� �ּ� �ֱ�
    for (int i = 0; i < r; i++) tmp = tmp->next; // r ��� ã�ư��� tmp�� ���� ���
    ptmp = tmp->prev; // ���� ���
    ntmp = tmp->next; // ���� ���
    ptmp->next = ntmp; // ���� ����� ������ �������� �̾��ֱ�
    ntmp->prev = ptmp; // ���� ����� ������ ���� ���� �̾�̱�
    free(tmp); // �Ҵ� ����
    List->lenlist--; // �������ϱ� ����Ʈ ���� ���ֱ�
}
void getnode(list* List, int r) { // r�� �о��
    if (r <1 || r> List->lenlist-2) { // 0�� �ȵǴ� ��쳪 ������ ��� ��� ����ó��
        printf("invalid position\n"); // ���ܹ���
        return 0; // �Լ� ��
    }
    node* tmp; // ������ �� ���� �����
    tmp=List->head; // ������ �ص� �ּ� �ֱ�
    for (int i = 0; i < r; i++) tmp = tmp->next; // r ��� ã�ư���
    printf("%c", tmp->elem); // ������
}
void printnode(list* List) {
    node* tmp; // ������ �� ���� �����
    tmp = List->head; // ������ �ص� �ּ� �ֱ�
    for (int i = 0; i < List->lenlist-2; i++) { // ���� ���� ���ϱ�
        tmp = tmp->next; // ��ĭ�� ����
        printf("%c", tmp->elem); // ������ ����Ʈ!
    }
    printf("\n"); // �߰��� ������ ���̸� ���Ͱ� �ʿ��ϹǷ�
}

int main() {
    double a = 1.1;
    printf("%f", a);
}
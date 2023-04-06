#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)
//���� ���Ḯ��Ʈ 1��
//�ճ��� �޳���� �ּҰ��� ���� ��屸��ü(���߿���)
typedef struct node 
{
	struct node* prev;
	char elem;
	struct node* next;
}node;

//��� ����Ʈ�� ������ ���ϳ��, ����Ʈ�� ���̵��� ���� ����Ʈ
typedef struct _list 
{
	node* head;
	int position;
	node* tail;

}list;

//����Ʈ�� �ʱ�ȭ���ش�
void init(list* lptr) 
{
	node* ohead, *otail;
	ohead = (node*)malloc(sizeof(node));
	otail = (node*)malloc(sizeof(node));

	lptr->head = ohead;
	ohead->prev = NULL;
	ohead->next = otail;


	lptr->tail = otail;
	otail->next = NULL;
	otail->prev = ohead;

	lptr->position = 2;
}
//����Ʈ�� ����Ѱ��� �߰�
void add(list* lptr) 
{
	int tposi;
	char nwel;
	int order;
	scanf("%d %c", &order, &nwel);//�߰��� ����� ��ġ�� ���� �Է¹���
	getchar();
	//��带 �߰��� ��ġ�� �ùٸ��� ���� ��� error���
	if ((lptr->position) - 1 < order) 
	{
		printf("invalid position\n");
		return;
	}
	node* tmp;
	tmp = lptr->head;
	//���ο� ��带 �����Ҵ�
	struct node* newnode;
	newnode = (struct node*)malloc(sizeof(struct node));
	newnode->elem = nwel;
	//for���� ���� �� ����� �ڸ��� ã��
	for (int i = 0; i < order; i++) 
	{
		tmp = tmp->next;
	}
	newnode->next = tmp;
	newnode->prev = tmp->prev;
	tmp->prev = newnode;
	tmp = newnode->prev;
	tmp->next = newnode;
	tposi = (lptr->position);
	tposi++;
	lptr->position = tposi;

}
//��ġ�� �Է¹ް� �ش� ��ġ�� ��带 ����
void delete(list* lptr) {
	int tposi;
	int order;
	scanf("%d", &order);
	getchar();
	//��ġ�� ��Ȯ���� ���� ��
	if ((lptr->position) - 2 < order) 
	{
		printf("invalid position\n");
		return;
	}

	node* tmp, *ptemp, *ntemp;

	tmp = lptr->head;
	//for���� ���� ��ġ ã��
	for (int i = 0; i < order; i++) 
	{
		tmp = tmp->next;
	}
	ptemp = tmp->prev;
	ntemp = tmp->next;
	ptemp->next = ntemp;
	ntemp->prev = ptemp;
	free(tmp);//�����Ҵ� ����
	tposi = (lptr->position);//����Ʈ�� ���̵� 1 �ٿ���
	tposi--;
	lptr->position = tposi;
}
//�ش���ġ�� ��尪�� ����ϴ� �Լ�
void get_entry(list* lptr) 
{
	node* temp;
	temp = lptr->head;
	int getnum;
	scanf("%d", &getnum);
	getchar();
	//�Է¹��� ��ġ�� �ùٸ��� ���� ��
	if ((lptr->position) - 2 < getnum) 
	{
		printf("invalid position\n");
		return;
	}
	//��ġ ã��
	for (int i = 0; i < getnum; i++) 
	{
		temp = temp->next;
	}
	//�ش���ġ�� ����� ���� ���
	printf("%c\n", temp->elem);
}
//����Ʈ�� ������ ���ϱ����� �� ������ ���� ����ϴ� �Լ�
void printlist(list* lptr) {
	node* temp;
	temp = lptr->head;
	//��带 �� �� �ű� �� ���
	for (int i = 0; i < (lptr->position) - 2; i++) 
	{
		temp = temp->next;
		printf("%c", temp->elem);
	}
	printf("\n");
}

int main(void)
{
	int num;
	char command1;

	list* l;
	l = (list*)malloc(sizeof(list));
	init(l);
	//����Ʈ�� ���� �� �����Ҵ��ϰ� �ʱ�ȭ��.
	scanf("%d", &num);
	getchar();
	for (int i = 0; i < num; i++) 
	{
		scanf("%c", &command1);
		getchar();

		if (command1 == 'a') 
		{
			add(l);
			continue;
		}
		else if (command1 == 'g') 
		{ //�ٽ� get_entry�� ... ��͸� �Ẹ�� �ͽ��ϴ�..
			get_entry(l);
			continue;
		}
		else if (command1 == 'd') 
		{
			delete(l);
			continue;
		}

		else if (command1 == 'p') 
		{
			printlist(l);
			continue;
		}
	}

	return 0;
}
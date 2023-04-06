#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)
//이중 연결리스트 1번
//앞노드와 뒷노드의 주소값을 갖는 노드구조체(이중연결)
typedef struct node 
{
	struct node* prev;
	char elem;
	struct node* next;
}node;

//노드 리스트의 헤드노드와 테일노드, 리스트의 길이들을 갖는 리스트
typedef struct _list 
{
	node* head;
	int position;
	node* tail;

}list;

//리스트를 초기화해준다
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
//리스트에 노드한개를 추가
void add(list* lptr) 
{
	int tposi;
	char nwel;
	int order;
	scanf("%d %c", &order, &nwel);//추가할 노드의 위치와 값을 입력받음
	getchar();
	//노드를 추가할 위치가 올바르지 않을 경우 error출력
	if ((lptr->position) - 1 < order) 
	{
		printf("invalid position\n");
		return;
	}
	node* tmp;
	tmp = lptr->head;
	//새로운 노드를 동적할당
	struct node* newnode;
	newnode = (struct node*)malloc(sizeof(struct node));
	newnode->elem = nwel;
	//for문을 돌아 새 노드의 자리를 찾음
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
//위치를 입력받고 해당 위치의 노드를 삭제
void delete(list* lptr) {
	int tposi;
	int order;
	scanf("%d", &order);
	getchar();
	//위치가 정확하지 않을 때
	if ((lptr->position) - 2 < order) 
	{
		printf("invalid position\n");
		return;
	}

	node* tmp, *ptemp, *ntemp;

	tmp = lptr->head;
	//for문을 돌아 위치 찾기
	for (int i = 0; i < order; i++) 
	{
		tmp = tmp->next;
	}
	ptemp = tmp->prev;
	ntemp = tmp->next;
	ptemp->next = ntemp;
	ntemp->prev = ptemp;
	free(tmp);//동적할당 해제
	tposi = (lptr->position);//리스트의 길이도 1 줄여줌
	tposi--;
	lptr->position = tposi;
}
//해당위치의 노드값만 출력하는 함수
void get_entry(list* lptr) 
{
	node* temp;
	temp = lptr->head;
	int getnum;
	scanf("%d", &getnum);
	getchar();
	//입력받은 위치가 올바르지 않을 때
	if ((lptr->position) - 2 < getnum) 
	{
		printf("invalid position\n");
		return;
	}
	//위치 찾기
	for (int i = 0; i < getnum; i++) 
	{
		temp = temp->next;
	}
	//해당위치의 노듸의 값만 출력
	printf("%c\n", temp->elem);
}
//리스트의 헤드부터 테일까지의 각 노드들의 값을 출력하는 함수
void printlist(list* lptr) {
	node* temp;
	temp = lptr->head;
	//노드를 한 번 옮긴 뒤 출력
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
	//리스트를 만든 뒤 동적할당하고 초기화함.
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
		{ //다시 get_entry로 ... 재귀를 써보고 싶습니다..
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
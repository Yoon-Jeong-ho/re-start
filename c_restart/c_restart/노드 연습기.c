#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>

typedef struct {
	    char elem;
	    struct node* next; // 다음 노드 주소 저장
	    struct node* prev; // 이전 노드 주소 저장
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
    head = (node*)malloc(sizeof(node)); // 해드 노드 생성
    tail = (node*)malloc(sizeof(node)); // 테일 노드 생성
    List->head = head; //리스트 헤드에 헤드 정보 저장
    head->prev = NULL;// 머리 앞에는 아무것도 없으니까
    head->next = tail;
    List->tail = tail;// 똑같이 테일 정보도 저장
    tail->next = NULL; // 꼬리 뒤에는 아무것도 없으니까
    tail->prev = head;
    List->lenlist = 2;// 머리와 테일 개수 해서 2개
    scanf("%d", &num); // 반복할 횟수 입력받기 
    while (count <= num) {
        scanf("%c %c", &ch, &ch);// 첫번째 입력에 엔터 입력받아서 두번 입력 받음
        if (ch == 'A') { // add일 경우
            scanf("%d %c", &r, &e); // 더할 곳이랑, 문자입력받기
            addnode(List, r, e);
        }
        else if (ch == 'D') { //delet일 경우
            scanf("%d", &r); // 지울 곳 입력받기
            deletnode(List, r);

        }
        else if (ch == 'P') { // print일 경우
            printnode(List);
        }
        else if (ch == 'G') { //getnode일경우
            scanf("%d", &r); // 불러올 곳 찾기
            getnode(List, r); 
        }
        else printf("invalid position\n");// 예외상황 처리
        count++;// 무한루프 안되게 카운트 한번씩
    }
	return 0;
}


void addnode(list* List, int r, char e) { // r은 들어갈 곳, e는 들어갈 문자
    if (r <1 || r> List->lenlist-1) { // 0이 안되는 경우나 범위를 벗어난 경우 예외처리
        printf("invalid position\n"); // 예외문구
        return 0; // 함수 끝
    }
    node* tmp; // 실행할 빈 공간 만들기
    tmp = List->head; // 공간에 해드 주소 넣기
    for (int i = 0; i < r; i++) tmp = tmp->next; // r 노드 찾아가기
    node* prevnode; // 이전 노드 생성
    prevnode = (struct node*)malloc(sizeof(node)); // 노드 동적할당 
    prevnode->next = tmp; // 만든 노드의 다음은 찾아간 노드
    prevnode->prev = tmp->prev; // 만든 노드의 이전은 찾아간 노드의 이전
    tmp->prev = prevnode; // 만든 노드는 찾아간 노드의 이전
    tmp = prevnode->prev;// 만든 노드의 이전으로 tmp 이동
    tmp->next = prevnode; // tmp의 다음을 만든 노드에 이동
    prevnode->elem = e;
    List->lenlist++; // 더해줬으니까 리스트 길이 더하기
}
void deletnode(list* List, int r) {
    if (r <1 || r> List->lenlist - 2) { // 0이 안되는 경우나 범위를 벗어난 경우 예외처리
        printf("invalid position\n"); // 예외문구
        return 0; // 함수 끝
    }
    node* tmp, * ntmp, * ptmp; // 실행할 빈 공간 만들기
    tmp = List->head; // 공간에 해드 주소 넣기
    for (int i = 0; i < r; i++) tmp = tmp->next; // r 노드 찾아가기 tmp는 지울 노드
    ptmp = tmp->prev; // 다음 노드
    ntmp = tmp->next; // 이전 노드
    ptmp->next = ntmp; // 이전 노드의 다음은 다음노드로 이어주기
    ntmp->prev = ptmp; // 다음 노드의 이전은 이전 노드로 이어ㅜ기
    free(tmp); // 할당 해제
    List->lenlist--; // 빼줬으니까 리스트 길이 빼주기
}
void getnode(list* List, int r) { // r은 읽어낼곳
    if (r <1 || r> List->lenlist-2) { // 0이 안되는 경우나 범위를 벗어난 경우 예외처리
        printf("invalid position\n"); // 예외문구
        return 0; // 함수 끝
    }
    node* tmp; // 실행할 빈 공간 만들기
    tmp=List->head; // 공간에 해드 주소 넣기
    for (int i = 0; i < r; i++) tmp = tmp->next; // r 노드 찾아가기
    printf("%c", tmp->elem); // 프린팅
}
void printnode(list* List) {
    node* tmp; // 실행할 빈 공간 만들기
    tmp = List->head; // 공간에 해드 주소 넣기
    for (int i = 0; i < List->lenlist-2; i++) { // 헤드와 테일 피하기
        tmp = tmp->next; // 한칸씩 증가
        printf("%c", tmp->elem); // 데이터 프린트!
    }
    printf("\n"); // 중간에 실현된 것이면 엔터가 필요하므로
}

int main() {
    double a = 1.1;
    printf("%f", a);
}
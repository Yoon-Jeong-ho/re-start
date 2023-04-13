//#define _CRT_SECURE_NO_WARNINGS 
//
//#include<stdio.h>
//#include<stdlib.h>
//
//
//typedef struct node {
//    int coef, exp;
//    struct node* next; // 다음 노드 주소
//}node;
//void nodeadd(node* head, int coef, int exp, int i); // 다음 노드 만들기
//void addPoly(node* head1, node* head2); // 두 노드 더하기
//
//int main_128746789_09876222() {
//    int num,coef1,exp1;
//    scanf("%d", &num); // 항의 개수 입력받기
//    node* head1, *head2;
//    head1 = (node*)malloc(sizeof(node)); //첫번째 노드 동적할당
//    head2 = (node*)malloc(sizeof(node)); // 두번째 노드 동적할당
//    for (int i = 0; i < num; i++) {
//        scanf("%d %d", &coef1, &exp1); // 차수랑 계수 입력받기
//        nodeadd(head1, coef1, exp1, i); // 차수랑 계수, 몇번째인지 넣어서 노드 만들기
//    }
//    scanf("%d", &num);// 두번째 항의 개수 입력받기
//    for (int i = 0; i < num; i++) {
//        scanf("%d %d", &coef1, &exp1); // 첫번째랑 똑같이 입력받기
//        nodeadd(head2, coef1, exp1, i); // 두번째 해드 넣는 것만 다르다.
//    }
//    addPoly(head1, head2); // add 폴리로 끝내기
//    free(head1);//동적할당 해제
//    free(head2); // 동적할당 해제
//	return 0;
//}
//
//void nodeadd(node* head, int coef1, int exp1, int i) {
//    for (int j = 0; j < i; j++) {
//        head = head->next; // 더할 위치로 가기
//    }
//    node* newnode; 
//    newnode = (node*)malloc(sizeof(node)); // 새로운 노드 동적 할당
//    head->next = newnode; // 더할 곳에 새로운 노드 잇기
//    newnode->coef = coef1; // 값 집어 넣기
//    newnode->exp = exp1; // 지수 넣기
//    newnode->next = NULL; // 다음은 없으니까 널값
//}
//void addPoly(node* head1, node* head2) {
//    node* resultnode; // 결과 노드
//    resultnode = (node*)malloc(sizeof(node)); // 할당해주기
//    resultnode->next = NULL; // 아직은 다음값 없으니까 널값
//    node* i = head1->next;
//    node* j = head2->next;
//    node* k = resultnode;
//    int num = 0; // 이것도 nodeadd에 순서 집어 넣어야 하므로 숫자 집어넣기
//    while ((i != NULL) && (j != NULL)) {
//        if (i->exp > j->exp) {
//            nodeadd(k, i->coef, i->exp, num); // i의 지수값이 더 크므로 i에 현재 있는 값 resultnode에 집어넣기
//            num++; // 순서 값은 항상 1씩 늘려준다
//            i = i->next; // i사용했으므로 다음칸
//        }
//        else if (i->exp < j->exp) {
//            nodeadd(k, j->coef, j->exp, num); // 여긴 j값이 더 크므로 j에 있는 값 resultnode에 집어넣기
//            num++; // 순서 1더하기
//            j = j->next; // j값 사용했으므로 다음 칸
//        }
//        else {
//            int sum = i->coef + j->coef; // 이건 지수가 같을 경우 이므로 둘 계수 더해주기
//            if (sum != 0) { // 0 이 아니라면 집어 넣어야 하니
//                nodeadd(k, sum, j->exp, num); // 노드 에드에 값 집어넣기
//                num++; // 순서 중요하다!
//            }
//            i = i->next; // 사용했으므로 다음칸
//            j = j->next; // 사용했으므로 다으맠ㄴ
//        }
//    }
//    while (i != NULL) { // j가 끝난경우 i만 진행
//        nodeadd(k, i->coef, i->exp, num);  // 하나씩 순서대로 넣기
//        num++; // 순서 중요!
//        i = i->next; // i사용했으므로 다음칸
//    }
//    while (j != NULL) { // 여긴 i 가 끝나서 j혼자 진행
//        nodeadd(k, j->coef, j->exp, num); // 하나씩 순서대로 넣기
//        num++; // 순서 순서 중요합니다
//        j = j->next; // j 사용했으므로 다음칸
//    }
//    while (resultnode->next != NULL) {
//        resultnode = resultnode->next; // 헤드 넘겨주기
//        printf(" %d %d", resultnode->coef, resultnode->exp); // 출력해주기
//    }
//    free(resultnode); // 동적할당 해제
//}
//#define _CRT_SECURE_NO_WARNINGS 
//
//#include<stdio.h>
//#include<stdlib.h>
//
//
//typedef struct node {
//    int coef, exp;
//    struct node* next; // ���� ��� �ּ�
//}node;
//void nodeadd(node* head, int coef, int exp, int i); // ���� ��� �����
//void addPoly(node* head1, node* head2); // �� ��� ���ϱ�
//
//int main_128746789_09876222() {
//    int num,coef1,exp1;
//    scanf("%d", &num); // ���� ���� �Է¹ޱ�
//    node* head1, *head2;
//    head1 = (node*)malloc(sizeof(node)); //ù��° ��� �����Ҵ�
//    head2 = (node*)malloc(sizeof(node)); // �ι�° ��� �����Ҵ�
//    for (int i = 0; i < num; i++) {
//        scanf("%d %d", &coef1, &exp1); // ������ ��� �Է¹ޱ�
//        nodeadd(head1, coef1, exp1, i); // ������ ���, ���°���� �־ ��� �����
//    }
//    scanf("%d", &num);// �ι�° ���� ���� �Է¹ޱ�
//    for (int i = 0; i < num; i++) {
//        scanf("%d %d", &coef1, &exp1); // ù��°�� �Ȱ��� �Է¹ޱ�
//        nodeadd(head2, coef1, exp1, i); // �ι�° �ص� �ִ� �͸� �ٸ���.
//    }
//    addPoly(head1, head2); // add ������ ������
//    free(head1);//�����Ҵ� ����
//    free(head2); // �����Ҵ� ����
//	return 0;
//}
//
//void nodeadd(node* head, int coef1, int exp1, int i) {
//    for (int j = 0; j < i; j++) {
//        head = head->next; // ���� ��ġ�� ����
//    }
//    node* newnode; 
//    newnode = (node*)malloc(sizeof(node)); // ���ο� ��� ���� �Ҵ�
//    head->next = newnode; // ���� ���� ���ο� ��� �ձ�
//    newnode->coef = coef1; // �� ���� �ֱ�
//    newnode->exp = exp1; // ���� �ֱ�
//    newnode->next = NULL; // ������ �����ϱ� �ΰ�
//}
//void addPoly(node* head1, node* head2) {
//    node* resultnode; // ��� ���
//    resultnode = (node*)malloc(sizeof(node)); // �Ҵ����ֱ�
//    resultnode->next = NULL; // ������ ������ �����ϱ� �ΰ�
//    node* i = head1->next;
//    node* j = head2->next;
//    node* k = resultnode;
//    int num = 0; // �̰͵� nodeadd�� ���� ���� �־�� �ϹǷ� ���� ����ֱ�
//    while ((i != NULL) && (j != NULL)) {
//        if (i->exp > j->exp) {
//            nodeadd(k, i->coef, i->exp, num); // i�� �������� �� ũ�Ƿ� i�� ���� �ִ� �� resultnode�� ����ֱ�
//            num++; // ���� ���� �׻� 1�� �÷��ش�
//            i = i->next; // i��������Ƿ� ����ĭ
//        }
//        else if (i->exp < j->exp) {
//            nodeadd(k, j->coef, j->exp, num); // ���� j���� �� ũ�Ƿ� j�� �ִ� �� resultnode�� ����ֱ�
//            num++; // ���� 1���ϱ�
//            j = j->next; // j�� ��������Ƿ� ���� ĭ
//        }
//        else {
//            int sum = i->coef + j->coef; // �̰� ������ ���� ��� �̹Ƿ� �� ��� �����ֱ�
//            if (sum != 0) { // 0 �� �ƴ϶�� ���� �־�� �ϴ�
//                nodeadd(k, sum, j->exp, num); // ��� ���忡 �� ����ֱ�
//                num++; // ���� �߿��ϴ�!
//            }
//            i = i->next; // ��������Ƿ� ����ĭ
//            j = j->next; // ��������Ƿ� ��������
//        }
//    }
//    while (i != NULL) { // j�� ������� i�� ����
//        nodeadd(k, i->coef, i->exp, num);  // �ϳ��� ������� �ֱ�
//        num++; // ���� �߿�!
//        i = i->next; // i��������Ƿ� ����ĭ
//    }
//    while (j != NULL) { // ���� i �� ������ jȥ�� ����
//        nodeadd(k, j->coef, j->exp, num); // �ϳ��� ������� �ֱ�
//        num++; // ���� ���� �߿��մϴ�
//        j = j->next; // j ��������Ƿ� ����ĭ
//    }
//    while (resultnode->next != NULL) {
//        resultnode = resultnode->next; // ��� �Ѱ��ֱ�
//        printf(" %d %d", resultnode->coef, resultnode->exp); // ������ֱ�
//    }
//    free(resultnode); // �����Ҵ� ����
//}
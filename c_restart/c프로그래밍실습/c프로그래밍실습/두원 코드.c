//#pragma warning(disable:4996)
//
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include <math.h>
//
//typedef struct node { //������ ��� ���
//    char value;
//    struct node* next;
//
//} node;
//
//typedef struct nodenum {//���ڴ�� ���
//    int value;
//    struct nodenum* next;
//
//} nodenum;
//
//node* getnode(char value) {//������ ��� ��� ����
//    node* new = (node*)malloc(sizeof(node));
//    new->next = null;
//    new->value = value;
//
//    return new;
//}
//
//nodenum* getnodenum(int value) {//���� ��� ��� ����
//    nodenum* new = (nodenum*)malloc(sizeof(nodenum));
//    new->next = null;
//    new->value = value;
//
//    return new;
//}
//
//char pop(node** top) {//������ ���ÿ��� pop
//    char result = (*top)->value;
//    node* fordel = *top;
//    *top = (*top)->next;
//    free(fordel);
//
//    return result;
//}
//
//int popnum(nodenum** top) {//���ڽ��ÿ��� pop
//    int result = (*top)->value;
//    nodenum* fordel = *top;
//    *top = (*top)->next;
//    free(fordel);
//
//    return result;
//}
//
//node* linknode(node* top, node* temp) {//������ ���ÿ� �ֱ�
//    if (top == null)top = temp;
//    else {
//        temp->next = top;
//        top = temp;
//    }
//    return top;
//}
//
//nodenum* linknodenum(nodenum* top, nodenum* temp) {//���� ���ÿ� �ֱ�
//    if (top == null)top = temp;
//    else {
//        temp->next = top;
//        top = temp;
//    }
//    return top;
//}
//
//int checkpriority(char temp) {//���� ���� ����
//    switch (temp) {
//    case '(':
//        return 8;
//    case ')':
//        return 9;
//    case '!':
//    case 'p':
//    case 'm':
//        return 7;
//    case '^':
//        return 6;
//    case '*':
//    case '/':
//        return 5;
//    case '+':
//    case '-':
//        return 4;
//    case '>':
//    case '<':
//        return 3;
//    case '&':
//        return 2;
//    case '|':
//        return 1;
//    default:
//        return 0;//�ǿ�����
//    }
//}
//
//void printf2(char ch) {//����Ʈ�� ���Ҿ����ϴ�.
//    return;
//    if (ch == '&' || ch == '|') printf("%c%c", ch, ch);
//    else if (ch == 'p') printf("+");
//    else if (ch == 'm') printf("-");
//    else printf("%c", ch);
//}
//
//int calculator(int b, char op, int a) { // ����ϴ� ����
//    switch (op) {
//    case '+':
//        return a + b;
//    case '-':
//        return a - b;
//    case '*':
//        return a * b;
//    case '/':
//        return a / b;
//    case '^':
//        return pow(a, b);
//    }
//}
//
//
//int atoi2(char* a) {//���� �������
//    int result = 0;
//    if ('0' <= *a && *a <= '9')result = *a - '0';//���ڸ����϶�
//    //    else result = atoi(a);
//
//    if ('0' <= *(a + 1) && *(a + 1) <= '9') result = result * 10 + *(a + 1) - '0';//���ڸ����϶�
//
//    return result;
//}
//
//int main() {
//
//    char ch = '\0';
//    char tempch;
//    int chres;
//    int isbraceopened = 0;
//    int i, j, k;
//    node* tempnode;
//    nodenum* tempnodenum;
//    int iter;
//    int resultcal = 0;
//
//
//    scanf("%d", &iter);//����ݺ����� �ް�
//    getchar();
//
//    for (j = 0; j < iter; j++) {
//        node* top = null;
//        nodenum* topcal = null;
//        char formula[201] = { '\0' };
//        scanf("%s", formula);//���Ĺް�
//        getchar();
//
//        i = 0;
//        while (1) {
//            ch = formula[i++];//���� �ѹ��ھ� �޾Ƽ�
//            if (ch == '\0') break; // ���ĳ� ������ ����
//            chres = checkpriority(ch);
//            if (ch == '|' || ch == '&') i++;//Ư�� ������ ó��
//            if (chres == 4 && (i == 1 || (checkpriority(formula[i - 2]) != 8 && checkpriority(formula[i - 2]) != 0))) {
//                if (ch == '+')ch = 'p';//���׿����� ó��
//                else ch = 'm';
//                chres = 7;
//            }
//
//            if (chres == 0) { //�����϶� ���ڽ��ÿ� ����
//                printf2(ch);
//                tempnodenum = getnodenum(atoi2(&formula[i - 1]));
//                if (tempnodenum->value >= 10) {
//                    i++;
//                }
//                topcal = linknodenum(topcal, tempnodenum);
//
//            }
//            else if (chres == 9) {//��ȣ�� ������
//                isbraceopened--;
//                while (1) {
//                    if (top == null) break;
//                    tempch = pop(&top);
//                    if (checkpriority(tempch) == 8) break;
//                    else {
//                        printf2(tempch);
//                        int aa = popnum(&topcal);
//                        int bb = popnum(&topcal);
//                        resultcal = calculator(aa, tempch, bb);
//                        tempnodenum = getnodenum(resultcal);
//                        topcal = linknodenum(topcal, tempnodenum);
//                    }
//
//                }
//            }
//            else if (chres == 8 || isbraceopened > 0) { // ��ȣ����
//                if (chres == 8)isbraceopened++;
//                while (1) {
//                    if (top == null) break;
//                    tempch = top->value;
//                    if (tempch == '(')break;
//
//                    if (checkpriority(tempch) < checkpriority(ch))break;
//                    printf2(pop(&top));
//                    int aa = popnum(&topcal);
//                    int bb = popnum(&topcal);
//                    resultcal = calculator(aa, tempch, bb);
//                    tempnodenum = getnodenum(resultcal);
//                    topcal = linknodenum(topcal, tempnodenum);
//
//                }
//                tempnode = getnode(ch);
//                top = linknode(top, tempnode);
//            }
//            else {//������ ������
//                while (1) {
//                    if (top == null) break; //�����ڽ��� ������� ����
//                    tempch = top->value;
//
//                    if (ch == '^') break; // ������ �켱���� ���
//
//                    if (checkpriority(tempch) < checkpriority(ch))break;//���ÿ� �������� ���κ��� ���ų� ���� ������ ���
//                    printf2(pop(&top));
//                    int aa = popnum(&topcal);
//                    int bb = popnum(&topcal);
//                    resultcal = calculator(aa, tempch, bb);
//                    tempnodenum = getnodenum(resultcal);
//                    topcal = linknodenum(topcal, tempnodenum);
//
//                }
//
//                tempnode = getnode(ch);//������ ���ÿ� �߰�
//                top = linknode(top, tempnode);
//            }
//
//        }
//        while (top != null) {//���� ������ ������ ���� ���
//            tempch = pop(&top);
//            printf2(tempch);
//            int aa = popnum(&topcal);
//            int bb = popnum(&topcal);
//            resultcal = calculator(aa, tempch, bb);
//            tempnodenum = getnodenum(resultcal);
//            topcal = linknodenum(topcal, tempnodenum);
//        }
//        printf("%d\n", popnum(&topcal));//�������
//    }
//    return 0;
//}
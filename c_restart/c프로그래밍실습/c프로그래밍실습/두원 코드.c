//#pragma warning(disable:4996)
//
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include <math.h>
//
//typedef struct node { //연산자 담는 노드
//    char value;
//    struct node* next;
//
//} node;
//
//typedef struct nodenum {//숫자담는 노드
//    int value;
//    struct nodenum* next;
//
//} nodenum;
//
//node* getnode(char value) {//연산자 담는 노드 생성
//    node* new = (node*)malloc(sizeof(node));
//    new->next = null;
//    new->value = value;
//
//    return new;
//}
//
//nodenum* getnodenum(int value) {//숫자 담는 노드 생성
//    nodenum* new = (nodenum*)malloc(sizeof(nodenum));
//    new->next = null;
//    new->value = value;
//
//    return new;
//}
//
//char pop(node** top) {//연산자 스택에서 pop
//    char result = (*top)->value;
//    node* fordel = *top;
//    *top = (*top)->next;
//    free(fordel);
//
//    return result;
//}
//
//int popnum(nodenum** top) {//숫자스택에서 pop
//    int result = (*top)->value;
//    nodenum* fordel = *top;
//    *top = (*top)->next;
//    free(fordel);
//
//    return result;
//}
//
//node* linknode(node* top, node* temp) {//연산자 스택에 넣기
//    if (top == null)top = temp;
//    else {
//        temp->next = top;
//        top = temp;
//    }
//    return top;
//}
//
//nodenum* linknodenum(nodenum* top, nodenum* temp) {//숫자 스택에 넣기
//    if (top == null)top = temp;
//    else {
//        temp->next = top;
//        top = temp;
//    }
//    return top;
//}
//
//int checkpriority(char temp) {//숫자 맵핑 배정
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
//        return 0;//피연산자
//    }
//}
//
//void printf2(char ch) {//프린트는 역할없습니다.
//    return;
//    if (ch == '&' || ch == '|') printf("%c%c", ch, ch);
//    else if (ch == 'p') printf("+");
//    else if (ch == 'm') printf("-");
//    else printf("%c", ch);
//}
//
//int calculator(int b, char op, int a) { // 계산하는 로직
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
//int atoi2(char* a) {//숫자 추출로직
//    int result = 0;
//    if ('0' <= *a && *a <= '9')result = *a - '0';//한자리수일때
//    //    else result = atoi(a);
//
//    if ('0' <= *(a + 1) && *(a + 1) <= '9') result = result * 10 + *(a + 1) - '0';//두자리수일때
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
//    scanf("%d", &iter);//몇번반복할지 받고
//    getchar();
//
//    for (j = 0; j < iter; j++) {
//        node* top = null;
//        nodenum* topcal = null;
//        char formula[201] = { '\0' };
//        scanf("%s", formula);//수식받고
//        getchar();
//
//        i = 0;
//        while (1) {
//            ch = formula[i++];//수식 한문자씩 받아서
//            if (ch == '\0') break; // 수식끝 나오면 종료
//            chres = checkpriority(ch);
//            if (ch == '|' || ch == '&') i++;//특이 연산자 처리
//            if (chres == 4 && (i == 1 || (checkpriority(formula[i - 2]) != 8 && checkpriority(formula[i - 2]) != 0))) {
//                if (ch == '+')ch = 'p';//단항연산자 처리
//                else ch = 'm';
//                chres = 7;
//            }
//
//            if (chres == 0) { //숫자일때 숫자스택에 저장
//                printf2(ch);
//                tempnodenum = getnodenum(atoi2(&formula[i - 1]));
//                if (tempnodenum->value >= 10) {
//                    i++;
//                }
//                topcal = linknodenum(topcal, tempnodenum);
//
//            }
//            else if (chres == 9) {//괄호끝 만나면
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
//            else if (chres == 8 || isbraceopened > 0) { // 괄호열기
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
//            else {//연산자 만나면
//                while (1) {
//                    if (top == null) break; //연산자스택 비었으면 종료
//                    tempch = top->value;
//
//                    if (ch == '^') break; // 제곱시 우선순위 고려
//
//                    if (checkpriority(tempch) < checkpriority(ch))break;//스택에 들어가기위해 본인보다 높거나 같은 연산자 계산
//                    printf2(pop(&top));
//                    int aa = popnum(&topcal);
//                    int bb = popnum(&topcal);
//                    resultcal = calculator(aa, tempch, bb);
//                    tempnodenum = getnodenum(resultcal);
//                    topcal = linknodenum(topcal, tempnodenum);
//
//                }
//
//                tempnode = getnode(ch);//본인을 스택에 추가
//                top = linknode(top, tempnode);
//            }
//
//        }
//        while (top != null) {//수식 끝나면 남은거 전부 계산
//            tempch = pop(&top);
//            printf2(tempch);
//            int aa = popnum(&topcal);
//            int bb = popnum(&topcal);
//            resultcal = calculator(aa, tempch, bb);
//            tempnodenum = getnodenum(resultcal);
//            topcal = linknodenum(topcal, tempnodenum);
//        }
//        printf("%d\n", popnum(&topcal));//정답출력
//    }
//    return 0;
//}
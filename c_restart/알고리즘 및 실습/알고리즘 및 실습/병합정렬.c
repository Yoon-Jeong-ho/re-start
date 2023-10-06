//#define _CRT_SECURE_NO_WARNINGS 
//
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include<time.h>
//
//typedef struct {
//    int elem;
//    struct node* next; // 다음 노드 주소 저장
//}node;
//
//typedef struct {
//    node* head;
//    int lenlist;
//}list;
//
//list* mergeSort(list*);
//list* merge(list* ,list*);
//list* partition(list*, int);
//
//int main() {
//    int n,tmp;
//    scanf("%d", &n);
//    list* List;
//    List = (list*)malloc(sizeof(list));
//    node* head,*tail;
//    head = (node*)malloc(sizeof(node)); // 해드 노드 생성
//    List->head = head; //리스트 헤드에 헤드 정보 저장
//    head->next = NULL;// 머리 앞에는 아무것도 없으니까
//    List->lenlist = 0;
//
//    scanf("%d", &tmp);
//    head->elem = tmp;
//    List->lenlist++;
//
//    for (int i = 0; i < n-1; i++) {
//        scanf("%d", &tmp);
//        tail = (node*)malloc(sizeof(node));
//        head->next = tail;
//        tail->next = NULL;
//        tail->elem = tmp;
//        head = tail;
//        List->lenlist++;
//    }
//    List = mergeSort(List);
//    head = List->head;
//    while (head->next != NULL) {
//        printf("%d ", head->elem);
//        head = head->next;
//    }
//    printf("%d", head->elem);
//    free(List);
//    return 0;
//}
//
//list* mergeSort(list* l1) {
//    list* l2 = NULL;
//    l2 = partition(l1, (float)l1->lenlist / 2+0.5);
//    if (l1->lenlist > 1) l1 = mergeSort(l1);
//    if (l2->lenlist > 1) l2 = mergeSort(l2);
//    return merge(l1, l2);
//}
//list* merge(list* l1, list* l2) {
//    list* l;
//    l = (list*)malloc(sizeof(list));
//    l->head = NULL;
//    node* lnode=NULL,*l2node,*l1node;
//    l1node = l1->head;
//    l2node = l2->head;
//    int a=0, b=0;
//    while (a < l1->lenlist && b < l2->lenlist) {
//        if (l2node->elem > l1node->elem) {
//            a++;
//            if (l->head == NULL) {
//
//                lnode = l1node;
//                l->head= lnode;
//
//            }
//            else {
//                lnode->next = l1node;
//                lnode = lnode->next;
//            }
//            if (a < l1->lenlist) l1node = l1node->next;
//        }
//        else {
//            b++;
//            if (l->head == NULL) {
//                lnode = l2node;
//                l->head= lnode ;
//            }
//            else {
//                lnode->next = l2node;
//                lnode = lnode->next;
//            }
//            if (b < l2->lenlist) l2node = l2node->next;
//        }
//    }
//    while (a < l1->lenlist) {
//        a++;
//        if (l->head == NULL) {
//            lnode = l1node;
//            lnode = l->head;
//        }
//        else {
//            lnode->next = l1node;
//            lnode = lnode->next;
//        }
//        if (a < l1->lenlist) l1node = l1node->next;
//    }
//    while (b < l2->lenlist) {
//        b++;
//        if (l->head == NULL) {
//            lnode = l2node;
//            lnode = l->head;
//        }
//        else {
//            lnode->next = l2node;
//            lnode = lnode->next;
//        }
//        if (b < l2->lenlist) l2node = l2node->next;
//    }
//    l->lenlist = l1->lenlist + l2->lenlist;
//    free(l1);
//    free(l2);
//    return l;
//}
//list* partition(list* l1, int k) {
//    list* l2;
//    l2 = (list*)malloc(sizeof(list));
//    node *head, *tail=NULL;
//    head = l1->head;
//    for (int i = 0; i < k; i++) {
//        tail = head;
//        head = head->next;
//        if (i == k - 1) {
//            tail->next = NULL;
//            l2->head = head;
//        }
//    }
//    l2->lenlist = l1->lenlist - k;
//    l1->lenlist = k;
//    return l2;
//}
//
//
//
//int kk = 0, l = 0;
//int merge_sort(int a[],int p, int r);
//int merge(int a[], int p, int q, int r);
//
//int main() {
//    int i, n, * list;
//    scanf("%d %d", &n, &l);
//    list = (int*)malloc(sizeof(int) * n);
//    for (int j = 0; j < n; j++) scanf("%d", &list[j]);
//    merge_sort(list, 0,n-1);
//    if (kk < l) printf("-1");
//    for (int j = 0; j < n; j++)printf("%d", list[j]);
//    return 0;
//}
//int merge_sort(int a[], int p, int r) {
//    int q;
//    if (p < r) {
//    q =(p + r) / 2;    //   # q는 p, r의 중간 지점
//    merge_sort(a, p, q);    //  # 전반부 정렬
//    merge_sort(a, q + 1, r);//  # 후반부 정렬
//    merge(a, p, q, r);      //  # 병합
//    }
//    return 0;
//}
//int merge(int a[], int p, int q, int r) {
//    int i =p, j =q + 1, t =0,*tmp;
//    tmp = (int*)malloc(sizeof(int) * (r - p + 1));
//    while (i <= q && j <= r) {
//        if (a[i] <= a[j])
//        {
//            tmp[t++] =a[i++]; //# tmp[t] < -a[i]; t++; i++;
//        }
//        else tmp[t++] = a[j++];// # tmp[t] < -a[j]; t++; j++;
//    }
//    while (i <= q)//  # 왼쪽 배열 부분이 남은 경우
//        tmp[t++] =a[i++];
//    while (j <= r)  //# 오른쪽 배열 부분이 남은 경우
//        tmp[t++] =a[j++];
//    i =p; t =0;
//    while (i <= r)//  # 결과를 a[p..r]에 저장
//    {
//        a[i++] = tmp[t++];              kk++;    if (kk == l) printf("%d", a[i-1]);
//    }
//    
//    return 0;
//}
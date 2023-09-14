//#define _CRT_SECURE_NO_WARNINGS 
//
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include<time.h>
//
//int kk = 0, l = 0;
//
//int heap_sort(int A[], int);
//int build_min_heap(int A[], int n);
//int heapify(int A[], int k, int n);
//
//int main() {
//    int i, n, * list;
//    scanf("%d %d", &n, &l);
//    list = (int*)malloc(sizeof(int) * (n+1));
//    for (int j = 1; j <= n; j++) scanf("%d", &list[j]);
//    // 퀵 정렬 수행(left: 배열의 시작 = 0, right: 배열의 끝 = 8)
//    heap_sort(list, n);
//    if (kk < l) printf("-1");
//    //for (int j = 0; j < n; j++)printf("%d", list[j]);
//}
//
//int heap_sort(int A[], int n) {
//    build_min_heap(A, n);
//    int tmp;
//    for (int i =n ; i >= 2 ; i-- ) {
//        tmp = A[i];
//        A[i] = A[1];
//        A[1] = tmp;
//        kk++;    if (kk == l) printf("%d %d", A[i], A[1]);
//
//        heapify(A, 1, i - 1);
//
//    }
//}
//int build_min_heap(int A[], int n) {
//    for (int i = n / 2; i >= 1; i--)  heapify(A, i, n);
//}
//int heapify(int A[], int k, int n) {
//    int left = 2*k; int right  = 2*k + 1,smaller,tmp;
//    if (right <= n) {
//        if (A[left] < A[right]) smaller =left;
//        else smaller = right;
//    }
//    else if (left <= n) smaller = left;
//    else return;
//
//        if (A[smaller] < A[k]) {
//            tmp=A[smaller];
//            A[smaller] = A[k];
//            A[k] = tmp;
//            kk++;    if (kk == l) printf("%d %d", A[k], A[smaller]);
//            heapify(A, smaller, n);
//        }
//}
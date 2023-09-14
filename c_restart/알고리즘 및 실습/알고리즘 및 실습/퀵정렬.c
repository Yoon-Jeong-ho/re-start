//#define _CRT_SECURE_NO_WARNINGS 
//
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include<time.h>
//
////int k = 0, l = 0;
//
//int quick_sort(int A[], int p, int r);
//int partition(int A[],int p,int r);
//
//int mainquick() {
//    int i,n,*list;
//    scanf("%d %d", &n,&l);
//    list = (int*)malloc(sizeof(int) * n);
//    for (int j = 0; j < n; j++) scanf("%d", &list[j]);
//    // 퀵 정렬 수행(left: 배열의 시작 = 0, right: 배열의 끝 = 8)
//    quick_sort(list, 0, n - 1);
//    if (k < l) printf("-1");
//    //for (int j = 0; j < n; j++)printf("%d", list[j]);
//}
//
//int quick_sort(int A[], int p, int r ) {
//    int q;
//    if (p < r) {
//        q = partition(A, p, r);  //분할
//        quick_sort(A, p, q - 1);  // 왼쪽 부분 배열 정렬
//        quick_sort(A, q + 1, r);  // 오른쪽 부분 배열 정렬
//    }
//}
//int partition(int A[], int p, int r) {
//    int x = A[r],tmp;   // # 기준원소
//    int i =p - 1;  // # i는 x보다 작거나 작은 원소들의 끝지점
//    for (int j = p; j <= r - 1;j++) // # j는 아직 정해지지 않은 원소들의 시작 지점
//        if (A[j] <= x) {
//            i++;
//            tmp = A[j];
//            A[j] = A[i];
//            A[i] = tmp;
//            k++;    if (k == l) printf("%d %d", A[i], A[j]);
//
//        } //# i값 증가 후 A[i] < ->A[j] 교환
//    if (i + 1 != r) {
//        tmp = A[i + 1]; 
//       A[i+1] = A[r];
//       A[r] = tmp;
//       k++;    if (k == l) printf("%d %d", A[i+1], A[r]);
//
//    }//# i + 1과 r이 서로 다르면 A[i + 1]과 A[r]을 교환
//    return i + 1;
//}

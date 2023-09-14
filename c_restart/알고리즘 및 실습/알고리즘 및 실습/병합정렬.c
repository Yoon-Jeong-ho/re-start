//#define _CRT_SECURE_NO_WARNINGS 
//
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include<time.h>
//
//int kk = 0, l = 0;
//int merge_sort(int A[],int p, int r);
//int merge(int A[], int p, int q, int r);
//
//int main() {
//    int i, n, * list;
//    scanf("%d %d", &n, &l);
//    list = (int*)malloc(sizeof(int) * n);
//    for (int j = 0; j < n; j++) scanf("%d", &list[j]);
//    merge_sort(list, 0,n-1);
//    if (kk < l) printf("-1");
//    //for (int j = 0; j < n; j++)printf("%d", list[j]);
//    return 0;
//}
//int merge_sort(int A[], int p, int r) {
//    int q;
//    if (p < r) {
//    q =(p + r) / 2;    //   # q는 p, r의 중간 지점
//    merge_sort(A, p, q);    //  # 전반부 정렬
//    merge_sort(A, q + 1, r);//  # 후반부 정렬
//    merge(A, p, q, r);      //  # 병합
//    }
//    return 0;
//}
//int merge(int A[], int p, int q, int r) {
//    int i =p, j =q + 1, t =0,*tmp;
//    tmp = (int*)malloc(sizeof(int) * (r - p + 1));
//    while (i <= q && j <= r) {
//        if (A[i] <= A[j])
//        {
//            tmp[t++] =A[i++]; //# tmp[t] < -A[i]; t++; i++;
//        }
//        else tmp[t++] = A[j++];// # tmp[t] < -A[j]; t++; j++;
//    }
//    while (i <= q)//  # 왼쪽 배열 부분이 남은 경우
//        tmp[t++] =A[i++];
//    while (j <= r)  //# 오른쪽 배열 부분이 남은 경우
//        tmp[t++] =A[j++];
//    i =p; t =0;
//    while (i <= r)//  # 결과를 A[p..r]에 저장
//    {
//        A[i++] = tmp[t++];              kk++;    if (kk == l) printf("%d", A[i-1]);
//    }
//    
//    return 0;
//}
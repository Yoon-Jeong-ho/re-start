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
//    // �� ���� ����(left: �迭�� ���� = 0, right: �迭�� �� = 8)
//    quick_sort(list, 0, n - 1);
//    if (k < l) printf("-1");
//    //for (int j = 0; j < n; j++)printf("%d", list[j]);
//}
//
//int quick_sort(int A[], int p, int r ) {
//    int q;
//    if (p < r) {
//        q = partition(A, p, r);  //����
//        quick_sort(A, p, q - 1);  // ���� �κ� �迭 ����
//        quick_sort(A, q + 1, r);  // ������ �κ� �迭 ����
//    }
//}
//int partition(int A[], int p, int r) {
//    int x = A[r],tmp;   // # ���ؿ���
//    int i =p - 1;  // # i�� x���� �۰ų� ���� ���ҵ��� ������
//    for (int j = p; j <= r - 1;j++) // # j�� ���� �������� ���� ���ҵ��� ���� ����
//        if (A[j] <= x) {
//            i++;
//            tmp = A[j];
//            A[j] = A[i];
//            A[i] = tmp;
//            k++;    if (k == l) printf("%d %d", A[i], A[j]);
//
//        } //# i�� ���� �� A[i] < ->A[j] ��ȯ
//    if (i + 1 != r) {
//        tmp = A[i + 1]; 
//       A[i+1] = A[r];
//       A[r] = tmp;
//       k++;    if (k == l) printf("%d %d", A[i+1], A[r]);
//
//    }//# i + 1�� r�� ���� �ٸ��� A[i + 1]�� A[r]�� ��ȯ
//    return i + 1;
//}

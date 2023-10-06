#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


int process(int*, int, int);
int partition(int*, int, int);
int choose_pivot(int*, int, int);


int main() {
	srand(time(0));
	int n, * a;
	scanf("%d", &n);
	a = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)scanf("%d", &a[i]);
	process(a, 0, n - 1);
	for (int i = 0; i < n; i++) printf("%d ", a[i]);
	return 0;
}
int process(int* a, int p, int r) {
	int q;
	if (p < r) {
		q = partition(a, p, r);
		process(a, p, q-1);
		process(a, q + 1, r);
	}
}
int partition(int* a, int p, int r) {
	int pivot, tmp, i = p, j = r - 1, val;
	pivot = choose_pivot(a, p, r);
	val = a[pivot];
	tmp = a[pivot];
	a[pivot] = a[r];
	a[r] = tmp;
	while (i <= j) {
		while (i <= j && a[i] <= val)i++;
		while (i <= j && a[j] >= val)j--;
		if (i < j) { tmp = a[i]; a[i] = a[j]; a[j] = tmp; }
	}
	tmp = a[i];
	a[i] = a[r];
	a[r] = tmp;
	return i;
}
int choose_pivot(int* a, int p, int r) {
	int num[3] = { 0 };
	for (int i = 0; i < 3; i++) {
		num[i] = (rand() % (r - p)) + p;
	}
	return (num[2]+ num[1]+ num[0])/3;
}

//
//int k = 0, l = 0;
//
//int quick_sort(int A[], int p, int r);
//int partition(int A[],int p,int r);
//
//int mainquick() {
//    int i,n,*list;
//    scanf("%d %d", &n,&l);
//    list = (int*)malloc(sizeof(int) * n);
//    for (int j = 0; j < n; j++) scanf("%d", &list[j]);
//     �� ���� ����(left: �迭�� ���� = 0, right: �迭�� �� = 8)
//    quick_sort(list, 0, n - 1);
//    if (k < l) printf("-1");
//    for (int j = 0; j < n; j++)printf("%d", list[j]);
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

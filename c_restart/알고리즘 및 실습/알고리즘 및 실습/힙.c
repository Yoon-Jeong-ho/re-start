#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int n = 0, H[100] = { 0 };
void insertItem(int key);
int removeMax();
void upHeap(int i);
void downHeap(int i);
void printHeap();
void printArray();
void rBuildHeap(int i);
void inPlaceHeapSort();
int main() {
    inPlaceHeapSort();
    printArray();
    return 0;
}
void inPlaceHeapSort() {
    char c;
    int a, t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) { scanf("%d", &a); insertItem(a); }
    for (int i = 0; i < t; i++) {
        a = removeMax();
        H[n + 1] = a;
    }
    n = t;
}
void rBuildHeap(int i) {
    if (i > n) return;
    rBuildHeap(i * 2);
    rBuildHeap(i * 2+1);
    downHeap(i);
    return;
}
void insertItem(int key) {
    H[++n] = key;
    upHeap(n);
}
int removeMax() {
    int result = H[1];
    H[1] = H[n--];
    downHeap(1);
    return result;
}
void upHeap(int i) {
    int tmp;
    if (i == 1) return;
    if (H[i] <= H[i / 2]) return;
    tmp = H[i];
    H[i] = H[i/2];
    H[i / 2] = tmp;
    upHeap(i / 2);
}
void downHeap(int i) {
    int tmp;
    if (i > n / 2) return;
    if (H[i] >= H[i * 2 + 1] && H[i] >= H[i * 2]) return;
    if (H[i * 2 + 1] > H[i * 2]) {
        tmp = H[i * 2 + 1];
        H[i * 2 + 1] = H[i];
        H[i] = tmp;
        return downHeap(i * 2 + 1);
    }
    else {
        tmp = H[i * 2 ];
        H[i * 2 ] = H[i];
        H[i] = tmp;
        return downHeap(i * 2);
    }
    
}
void printHeap() {
    int i = 1;
    while (i <= n) {
        printf("%d ", H[i++]);
    }
}
void printArray() {
    int i = 1;
    while (i <= n) {
        printf("%d ", H[i++]);
    }
}






int kk = 0, l = 0;

int heap_sort(int A[], int);
int build_min_heap(int A[], int n);
int heapify(int A[], int k, int n);


int main_heap() {
    int i, n, * list;
    scanf("%d %d", &n, &l);
    list = (int*)malloc(sizeof(int) * (n + 1));
    for (int j = 1; j <= n; j++) scanf("%d", &list[j]);
    // 퀵 정렬 수행(left: 배열의 시작 = 0, right: 배열의 끝 = 8)
    heap_sort(list, n);
    if (kk < l) printf("-1");
    //for (int j = 0; j < n; j++)printf("%d", list[j]);
}
int heap_sort(int A[], int n) {
    build_min_heap(A, n);
    int tmp;
    for (int i =n ; i >= 2 ; i-- ) {
        tmp = A[i];
        A[i] = A[1];
        A[1] = tmp;
        kk++;    if (kk == l) printf("%d %d", A[i], A[1]);

        heapify(A, 1, i - 1);

    }
}
int build_min_heap(int A[], int n) {
    for (int i = n / 2; i >= 1; i--)  heapify(A, i, n);
}
int heapify(int A[], int k, int n) {
    int left = 2*k; int right  = 2*k + 1,smaller,tmp;
    if (right <= n) {
        if (A[left] < A[right]) smaller =left;
        else smaller = right;
    }
    else if (left <= n) smaller = left;
    else return;

        if (A[smaller] < A[k]) {
            tmp=A[smaller];
            A[smaller] = A[k];
            A[k] = tmp;
            kk++;    if (kk == l) printf("%d %d", A[k], A[smaller]);
            heapify(A, smaller, n);
        }
}
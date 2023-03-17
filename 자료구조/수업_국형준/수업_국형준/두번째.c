#define _CRT_SECURE_NO_WARNINGS 
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>


int modulo(int a, int b);

int mostOnes(int** a, int n);

int prefixAverages1(int* X, int n, int* A);
int prefixAverages2(int* X, int n, int* B);

int main_2_1() {
	int a, b;
	scanf("%d %d", &a, &b);
	
	printf("%d", modulo(a, b));
	
	return 0;
}

int main_2_2() {
	int n, ** arr;
	scanf("%d", &n);
	arr = (int**)malloc(sizeof(int*) * n);
	for (int i = 0; i < n; i++) arr[i] = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	printf("%d", mostOnes(arr,n));
	return 0;
}

int main() {
	int n, * X, * A,* B;
	scanf("%d", &n);
	X = (int*)malloc(sizeof(int) * n);
	A = (int*)malloc(sizeof(int) * n);
	B = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) scanf("%d", &X[i]);
	prefixAverages1(X, n, A);
	prefixAverages1(X, n, B);
	for (int i = 0; i < n; i++) {
		printf("%d ", A[i]);
	}
	printf("\n");
	for (int i = 0; i < n; i++) {
		printf("%d ", B[i]);
	}	
	free(X);
	free(A);
	free(B);

	return 0;
}



int modulo(int a, int b) {
	return a % b;
}

int mostOnes(int** arr, int n) {
	int max = 0, nonzero = 0;
	for (int i = 0; i < n; i++) {
		while (nonzero < n-1 && arr[nonzero][i] == 0) nonzero++;
		if (arr[nonzero][i] == 1) max = nonzero;
	}
	return max;
}

int prefixAverages1(int* X, int n, int* A) {
	for (int i = 0; i < n; i++) {
		int sum = 0;
		for (int j = 0; j < i+1; j++) {
			sum += X[j];
		}
		A[i] = (int)((float)sum / (i + 1)+0.5);
	}
	return A;
}

int prefixAverages2(int* X, int n, int* B) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += X[i];
		B[i] = (int)((float)sum / (i+1)+0.5);
	}
	return B;
}

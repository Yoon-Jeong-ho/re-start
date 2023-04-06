//[ 巩力 1 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//
//int modulo(int a, int b) {
//	return a % b;
//}
//
//int main()
//{
//	int n, m;
//
//	scanf("%d %d", &n, &m);
//
//	printf("%d", modulo(n, m));
//	
//	return 0;
//}

//[ 巩力 2 ]
//#include<stdio.h>
//
//#pragma warning(disable:4996)
//
//int mostOnes(int **arr, int n) 
//{
//	int row = 0;
//	int i = 0, j = 0;
//
//	while ((i < n) && (j < n))
//	{
//		if (arr[i][j] == 0)
//		{
//			i++;
//		}
//		else
//		{
//			row = i;
//			j++;
//		}
//	}
//	return row;
//}
//
//int main(void) 
//{
//	int n, i, j;
//	int **arr;
//	
//	scanf("%d", &n);
//
//	arr = (int**)malloc(n * sizeof(int*));
//
//	for (i = 0; i < n; i++)
//	{
//		arr[i] = (int*)malloc(n * sizeof(int));
//	}
//
//	for (i = 0; i < n; i++)
//	{
//		for (j = 0; j < n; j++)
//		{
//			scanf("%d", &arr[i][j]);
//		}
//	}
//	printf("%d", mostOnes(arr, n));
//
//	for (i = 0; i < n; i++)
//	{
//		free(arr[i]);
//	}
//	free(arr);
//
//	return 0;
//}


//[ 巩力 3-1]
//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <stdlib.h>
//
//int *prefixAverages1(int *X, int n)
//{
//	double sum = 0;
//	int *A, i, j;
//
//	A = (int*)malloc(n * sizeof(int));
//
//	for (i = 0; i < n; i++)
//	{
//		sum = 0;
//		for (j = 0; j <= i; j++)
//		{
//			sum += X[j];
//		}
//		sum /= (i + 1);
//		sum += 0.5;
//		sum /= 1;
//		A[i] = sum;
//	}
//	return A;
//}
//
//int *prefixAverages2(int *X, int n)
//{
//	double sum = 0;
//	int *A, i;
//
//	A = (int*)malloc(n * sizeof(int));
//
//	for (i = 0; i < n; i++)
//	{
//		sum += X[i];
//		A[i] = (sum / (i + 1) + 0.5) / 1;
//	}
//	return A;
//
//}
//
//int main(void)
//{
//	int *X, n, i;
//	int *K;
//
//	scanf("%d", &n);
//
//	K = (int*)malloc(n * sizeof(int));
//
//	for (i = 0; i < n; i++)
//	{
//		scanf("%d", &K[i]);
//	}
//
//	X = prefixAverages1(K, n);
//
//	for (i = 0; i < n; i++)
//	{
//		printf("%d ", X[i]);
//	}
//	printf("\n");
//	X = prefixAverages2(K, n);
//
//	for (i = 0; i < n; i++)
//	{
//		printf("%d ", X[i]);
//	}
//
//	printf("\n");
//
//	return 0;
//}


//[ 巩力 3-2]
//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <stdlib.h>
//#include <Windows.h>
//
//int *prefixAverages1(int *X, int n)
//{
//	double sum = 0;
//	int *A, i, j;
//
//	A = (int*)malloc(n * sizeof(int));
//
//	for (i = 0; i < n; i++)
//	{
//		sum = 0;
//		for (j = 0; j <= i; j++)
//		{
//			sum += X[j];
//		}
//		sum /= (i + 1);
//		sum += 0.5;
//		sum /= 1;
//		A[i] = sum;
//	}
//	return A;
//}
//
//int *prefixAverages2(int *X, int n)
//{
//	double sum = 0;
//	int *A, i;
//
//	A = (int*)malloc(n * sizeof(int));
//
//	for (i = 0; i < n; i++)
//	{
//		sum += X[i];
//		A[i] = (sum / (i + 1) + 0.5) / 1;
//	}
//	return A;
//
//}
//
//int main(void)
//{
//	LARGE_INTEGER ticksPerSec;
//	LARGE_INTEGER start, finish, diff;
//	int *X, n, i;
//	int *K;
//	QueryPerformanceFrequency(&ticksPerSec);
//
//
//	scanf("%d", &n);
//
//	K = (int*)malloc(n * sizeof(int));
//
//	for (i = 0; i < n; i++)
//	{
//		K[i] = (rand() % 10000) + 1;
//	}
//
//	QueryPerformanceCounter(&start);
//	X = prefixAverages1(K, n);
//	QueryPerformanceCounter(&finish);
//
//	diff.QuadPart = (double)(finish.QuadPart - start.QuadPart);
//
//	printf("%.12fms", (diff.QuadPart / (double)ticksPerSec.QuadPart) * 10000);
//	printf("\n");
//
//	QueryPerformanceCounter(&start);
//	X = prefixAverages2(K, n);
//	QueryPerformanceCounter(&finish);
//
//	diff.QuadPart = (double)(finish.QuadPart - start.QuadPart);
//
//	printf("%.12fms", (diff.QuadPart / (double)ticksPerSec.QuadPart) * 10000);
//
//	printf("\n");
//
//	return 0;
//}
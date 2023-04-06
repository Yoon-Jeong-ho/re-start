#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int *prefixAverages1(int *X, int n)
{
	double sum = 0;
	int *A, i, j;

	A = (int*)malloc(n * sizeof(int));

	for (i = 0; i < n; i++)
	{
		sum = 0;
		for (j = 0; j <= i; j++)
		{
			sum += X[j];
		}
		sum /= (i + 1);
		sum += 0.5;
		sum /= 1;
		A[i] = sum;
	}
	return A;
	free(A);
}

int *prefixAverages2(int *X, int n)
{
	double sum = 0;
	int *A, i;

	A = (int*)malloc(n * sizeof(int));

	for (i = 0; i < n; i++)
	{
		sum += X[i];
		A[i] = (sum / (i + 1) + 0.5) / 1;
	}
	return A;
	free(A);
}

int main(void)
{
	LARGE_INTEGER ticksPerSec;
	LARGE_INTEGER start, finish, diff;
	int *X, n, i;
	int *K;
	QueryPerformanceFrequency(&ticksPerSec);


	scanf("%d", &n);

	K = (int*)malloc(n * sizeof(int));

	for (i = 0; i < n; i++)
	{
		K[i] = (rand() % 10000) + 1;
	}

	QueryPerformanceCounter(&start);
	X = prefixAverages1(K, n);
	QueryPerformanceCounter(&finish);

	diff.QuadPart = (double)(finish.QuadPart - start.QuadPart);

	printf("%.12fms", (diff.QuadPart / (double)ticksPerSec.QuadPart) * 10000);
	printf("\n");

	QueryPerformanceCounter(&start);
	X = prefixAverages2(K, n);
	QueryPerformanceCounter(&finish);

	diff.QuadPart = (double)(finish.QuadPart - start.QuadPart);

	printf("%.12fms", (diff.QuadPart / (double)ticksPerSec.QuadPart) * 10000);

	printf("\n");

	free(K);
	return 0;
}
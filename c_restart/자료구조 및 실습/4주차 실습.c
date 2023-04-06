//[ 문제 1 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <stdlib.h>
//
//void Reverse_Array(int *arr, int a, int b)
//{
//	int i, cnt = 0;
//	int *tmp_arr;
//	tmp_arr = (int*)malloc(sizeof(int)*(b - a + 1));
//	for (i = b; i >= a; i--)
//	{
//		tmp_arr[cnt] = arr[i];
//		cnt++;
//	}
//	cnt = 0;
//	for (i = a; i <= b; i++)
//	{
//		arr[i] = tmp_arr[cnt];
//		cnt++;
//	}
//}
//
//int main(void)
//{
//	int N, i;
//	int *arr = NULL;
//	int Inform_Reverse, a, b;
//
//
//	scanf("%d", &N);
//
//	arr = (int*)malloc(sizeof(int)*N);
//
//	for (i = 0; i < N; i++)
//	{
//		scanf("%d", &arr[i]);
//	}
//
//	scanf("%d", &Inform_Reverse);
//
//	for (i = 0; i < Inform_Reverse; i++)
//	{
//		scanf("%d %d", &a, &b);
//
//		Reverse_Array(arr, a, b);
//	}
//
//	for (i = 0; i < N; i++)
//	{
//		printf(" %d", arr[i]);
//	}
//
//	return 0;
//}


//[ 문제 2 ]
//[ 문제 1 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//
//int add_all(int N)
//{
//	int a;
//
//	if (N <= 0)
//	{
//		return 0;
//	}
//	else
//	{
//		return N % 10 + add_all(N / 10);
//	}
//
//	return a;
//}
//
//int main(void)
//{
//	int N, total;
//
//	scanf("%d", &N);
//
//	total = add_all(N);
//
//	printf("%d", total);
//
//	return 0;
//}


//[ 문제 2 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//int Fibonacci(int N)
//{
//	if (N == 0)
//	{
//		return 0;
//	}
//	else if (N == 1)
//	{
//		return 1;
//	}
//	else
//	{
//		return Fibonacci(N - 1) + Fibonacci(N - 2);
//	}
//}
//
//int main(void)
//{
//	int N, result;
//
//	scanf("%d", &N);
//
//	result = Fibonacci(N);
//
//	printf("%d", result);
//
//	return 0;
//}


//[ 문제 3 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <string.h>
//
//void isPaildrome(char *arr, int a, int b) 
//{
//	if (a >= b) 
//	{
//		printf("%d\n",strlen(arr));
//		printf("Yes");
//	}
//
//	else 
//	{
//		if (arr[a] != arr[b]) 
//		{
//			printf("%d\n", strlen(arr));
//			printf("No");
//			return 0;
//		}
//
//		isPaildrome(arr, a + 1, b - 1);
//
//	}
//
//}
//
//int main(void) 
//{
//
//	char arr[101] = { "\0" };
//	gets(arr);
//
//	isPaildrome(arr, 0, strlen(arr) - 1);
//
//	return 0;
//}
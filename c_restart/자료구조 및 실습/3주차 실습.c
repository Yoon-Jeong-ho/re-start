//[ ���� 1 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//
//int syn(int N) //1���� N������ ���� ���� �Լ� syn
//{
//	if (N <= 1) //N���� 1 ������ ��� 1 ��ȯ
//	{
//		return 1;
//	}
//	return syn(N - 1) + N; // syn�Լ��� N-1�� ������ N�� �������ν� ����Լ� �ۼ�
//}
//
//int main(void) //main�Լ� �ۼ�
//{
//	int N, total; //���� �Է¹��� ������ ���� N�� ����Լ��� ���� ��ü ���� ���� ������ ���� total ����
//
//	scanf("%d", &N); //�� �Է�
//
//	total = syn(N); //�Լ� ȣ��
//
//	printf("%d", total); //�� ���
//
//	return 0;
//}


//[ ���� 2 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//
//void cut(int N)
//{
//	if (N < 10)
//	{
//		printf("%d\n",N);
//	}
//	else
//	{
//		cut(N / 10);
//		printf("%d\n", N % 10);
//
//	}
//}
//
//int main(void)
//{
//	int N;
//
//	scanf("%d", &N);
//
//	cut(N);
//
//	return 0;
//
//}


//[ ���� 3 ] 
//#pragma warning(disable:4996)
//#include <stdio.h>
//
//void cut(int N)
//{
//	if (N < 10)
//	{
//		printf("%d\n", N);
//	}
//	else
//	{
//		printf("%d\n", N % 10);
//
//		cut(N / 10);
//
//	}
//}
//
//int main(void)
//{
//	int N;
//
//	scanf("%d", &N);
//
//	cut(N);
//
//	return 0;
//
//}

//[ ���� 4 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//
//int max_result(int N, int *arr)
//{
//   int a;
//   if (N == 0)
//   {
//      return arr[0];
//   }
//
//   a = max_result(N - 1, arr);
//   if (a < arr[N])
//   {
//      return arr[N];
//   }
//   else
//   {
//      return a;
//   }
//}
//
//int main(void)
//{
//   int N, arr[20], i, max_num = 0;
//
//   scanf("%d", &N);
//
//   for (i = 0; i < N; i++)
//   {
//      scanf("%d", &arr[i]);
//   }
//
//   max_num = max_result(N - 1, arr);
//
//   printf("%d", max_num);
//
//   return 0;
//}


//[ ���� 5 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//
//void hanoi(int N, char ch1, char ch2, char ch3)
//{
//   if (N == 1)
//   {
//      printf("%c %c\n", ch1, ch3);
//   }
//   else
//   {
//      hanoi(N - 1, ch1, ch3, ch2);
//      printf("%c %c\n", ch1, ch3);
//      hanoi(N - 1, ch2, ch1, ch3);
//   }
//}
//
//int main(void)
//{
//   int N;
//
//   scanf("%d", &N);
//   
//   hanoi(N, 'A', 'B', 'C');
//
//   return 0;
//}


//[ ���� 6 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//
//gcd(int N, int M)
//{
//   if (M == 0)
//   {
//      return N;
//   }
//   else
//   {
//      return gcd(M, N % M);
//   }
//}
//
//int main(void)
//{
//   int N, M;
//   int result;
//
//   scanf("%d %d", &N, &M);
//
//   result = gcd(N, M);
//
//   printf("%d", result);
//
//   return 0;
//}


//[ ���� 7 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <string.h>
//
//int check(char *arr, char check_ch,int length)
//{
//   if (length != 0)
//   {
//      if (*(arr + strlen(arr) - 1 - length) == check_ch)
//      {
//         return 1 + check(arr, check_ch, length - 1);
//      }
//      else
//      {
//         return 0 + check(arr, check_ch, length - 1);
//      }
//   }
//   else
//   {
//      if (*(arr + strlen(arr) - 1) == check_ch)
//      {
//         return 1;
//      }
//      else
//      {
//         return 0;
//      }
//   }
//}
//
//int main(void)
//{
//   char arr[101], check_ch;
//   int result;
//
//   scanf("%s", arr);
//   getchar();
//   scanf("%c", &check_ch);
//
//   result = check(arr, check_ch, strlen(arr) - 1);
//
//   printf("%d", result);
//
//   return 0;
//}

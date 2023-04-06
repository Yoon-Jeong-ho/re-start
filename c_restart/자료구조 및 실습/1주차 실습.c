//[ 巩力 1 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//int sum(n);
//int main(void)
//{
//	int X, total = 0;
//	int i;
//	scanf("%d", &X);
//	
//	for (i = 1; i <= X; i++)
//	{
//		total += sum(i);
//	}
//	printf("%d", total);
//	return 0;
//}
//int sum(int n)
//{
//	int i, k = 0;
//	for (i = 1; i <= n; i++)
//	{
//		k += i;
//	}
//	return k;
//}


//[ 巩力 2 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//int ABC(int arr[], int k);
//int main(void)
//{
//	int arr[10];
//	int i;
//
//	for (i = 0; i < 10; i++)
//	{
//		scanf("%d", &arr[i]);
//	}
//	for (i = 0; i < 9; i++)
//	{
//		ABC(arr, i);
//	}
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//	return 0;
//}
//int ABC(int arr[], int k)
//{
//	int i;
//	int tmp, max_num = k;
//	for (i = k; i < 10; i++)
//	{
//		if (arr[max_num] <= arr[i])
//		{
//			max_num = i;
//		}
//	}
//	tmp = arr[k];
//	arr[k] = arr[max_num];
//	arr[max_num] = tmp;
//}


//[ 巩力 3]
//#pragma warning(disable:4996)
//#include <stdio.h>
//swap(int *p, int *pr);
//int main(void)
//{
//	int N, i;
//	int arr[51];
//	int idx_1, idx_2;
//
//	scanf("%d", &N);
//	
//	for (i = 0; i < N; i++)
//	{
//		scanf("%d", &arr[i]);
//	}
//	scanf("%d %d", &idx_1, &idx_2);
//
//	swap(&arr[idx_1], &arr[idx_2]);
//
//	for (i = 0; i < N; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//	return 0;
//}
//swap(int *p, int *pr)
//{
//	int tmp;
//	tmp = *p;
//	*p = *pr;
//	*pr = tmp;
//}


//[ 巩力 4 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <string.h>
//int main(void)
//{
//	char ch[101], tmp;
//	int i, j;
//	
//	scanf("%s", ch);
//	printf("%s\n", ch);
//	for (i = 0; i < strlen(ch) - 1; i++)
//	{
//		for (j = 0; j < strlen(ch) - 1; j++)
//		{
//			tmp = ch[j];
//			ch[j] = ch[j + 1];
//			ch[j + 1] = tmp;
//		}
//		printf("%s\n", ch);
//	}
//	return 0;
//}


//[ 巩力 5 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//struct time
//{
//	int hour;
//	int min;
//	int sec;
//	int total;
//};
//typedef struct time TIME;
//int main(void)
//{
//	TIME time_1,time_2;
//
//	scanf("%d %d %d", &time_1.hour, &time_1.min, &time_1.sec);
//	scanf("%d %d %d", &time_2.hour, &time_2.min, &time_2.sec);
//	time_1.total = (time_1.hour * 3600) + (time_1.min * 60) + time_1.sec;
//	time_2.total = (time_2.hour * 3600) + (time_2.min * 60) + time_2.sec;
//	time_2.total -= time_1.total;
//	time_2.hour = time_2.total / 3600;
//	time_2.total %= 3600;
//	time_2.min = time_2.total / 60;
//	time_2.sec = time_2.total % 60;
//	printf("%d %d %d", time_2.hour, time_2.min, time_2.sec);
//	return 0;
//}


//[ 巩力 6 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <string.h>
//struct exam
//{
//	char name[10];
//	int score;
//};
//typedef struct exam EXAM;
//int main(void)
//{
//	EXAM ex[5];
//	int i;
//	double avg = 0.0;
//	
//	for (i = 0; i < 5; i++)
//	{
//		scanf("%s %d", &ex[i].name, &ex[i].score);
//		avg += ex[i].score;
//	}
//
//	avg /= 5.0;
//
//	for (i = 0; i < 5; i++)
//	{
//		if (ex[i].score <= avg)
//		{
//			printf("%s\n", ex[i].name);
//		}
//	}
//
//	return 0;
//}


//[ 巩力 7 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//int main(void)
//{
//	int N, i, j;
//	int *arr_1, *arr_2, *arr_result;
//
//	scanf("%d", &N);
//
//	arr_1 = (int*)malloc(sizeof(int)*N);
//	for (i = 0; i < N; i++)
//	{
//		scanf("%d", &arr_1[i]);
//	}
//	arr_2 = (int*)malloc(sizeof(int)*N);
//	for (i = 0; i < N; i++)
//	{
//		scanf("%d", &arr_2[i]);
//	}
//	arr_result = (int*)malloc(sizeof(int)*N);
//
//	for (i = 0, j = N - 1; i < N; i++, j--)
//	{
//		arr_result[i] = arr_1[i] + arr_2[j];
//	}
//
//	for (i = 0; i < N; i++)
//	{
//		printf(" %d", arr_result[i]);
//	}
//
//	free(arr_1);
//	free(arr_2);
//	free(arr_result);
//	return 0;
//}


//[ 巩力 8 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <string.h>
//struct student
//{
//	char name[8];
//	int kor, eng, math;
//	double avg;
//};
//typedef struct student STD;
//int main(void)
//{
//	STD *std;
//	int N, i;
//
//	scanf("%d", &N);
//
//	std = (STD*)malloc(sizeof(STD)*N);
//
//	for (i = 0; i < N; i++)
//	{
//		scanf("%s %d %d %d", &std[i].name, &std[i].kor, &std[i].eng, &std[i].math);
//		std[i].avg = (std[i].kor + std[i].eng + std[i].math) / 3.0;
//	}
//	for (i = 0; i < N; i++)
//	{
//		printf("%s %.1f ", std[i].name, std[i].avg);
//		if (std[i].kor >= 90 || std[i].eng >= 90 || std[i].math >= 90)
//		{
//			printf("GREAT ");
//		}
//		if (std[i].kor < 70 || std[i].eng < 70 || std[i].math < 70)
//		{
//			printf("BAD");
//		}
//		printf("\n");
//	}
//
//	free(std);
//	return 0;
//}
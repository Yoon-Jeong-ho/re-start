//[ 문제 1 ]
//#pragma warning(disable:4996)
//#include <stdio.h>
//#include <math.h>
//
//int is_prime(int n)
//{
//	int i;
//	if (n == 1) //1은 소수가 아니므로 예외처리
//	{
//		return 0;
//	}
//	if (n % 2 == 0) //짝수일 경우 소수가 아니므로 false
//	{
//		return n == 2 ? 1 : 0; //다만 짝수 2는 짝수 중 유일한 소수이므로 예외처리
//	}
//	for (i = 3; i * i <= n; i += 2) //홀수인 n이 i의 제곱보다 크거나 같을 경우까지 반복 (i <= sqrt(n))
//	{ //그리고 짝수는 위의 조건문에서 처리했기 때문에 홀수의 경우만 판별 / for문이 sqrt(n)번만큼 반복
//		if (n % i == 0)
//		{
//			return 0;
//		}
//	}
//	return 1;//위의 반복문에서 걸러지지 않은 수는 소수이므로 true
//
//}
//
//int main(void)
//{
//	int n, Confirm_num; //검사받을 자연수 하나와 검사 후 결과를 나타낼 정수형 변수 두개 선언
//
//	scanf("%d", &n); //검사받을 자연수 입력
//
//	Confirm_num = is_prime(n); //소수 판별 함수 호출
//
//	if (Confirm_num == 1) //함수 결과에 따라 소수인지 합성수인지 출력
//	{
//		printf("prime");
//	}
//	else
//	{
//		printf("composite");
//	}
//
//	return 0;
//}
/* 시간복잡도 & Big-Oh 표기*/

/*
시간복잡도 : O(sqrt(n)/2) ( 상수항은 무시하므로 O(sqrt(n)) )
f(n) = sqrt(n) / 2 + 3
*/


//[ 문제 2 ]
//#pragma warning (disable : 4996)
//#include <stdio.h>
//
//int divide_dom(int arr[], int x, int y) //영역을 분할하여 정렬하는 함수
//{
//	int a = arr[x];
//	int k = x + 1;
//	int j = y;
//
//	while (k <= j) //서로 만나기 전까지 계속 반복하는 반복문 이용
//	{
//		while (k <= y && a >= arr[k])  
//		{
//			k++;
//		}
//
//		while (j >= (x + 1) && a <= arr[j])
//		{
//			j--;
//		}
//
//		if (k <= j)
//		{
//			swap(arr, k, j);
//		}
//	}
//	swap(arr, x, j); //교차지점 pivot부분에서의 스왑
//	
//	return j;//j값을 반환
//
//}
//
//void quick_sort(int arr[], int x, int y)//퀵 정렬 함수
//{
//	int a;
//	if (x <= y) //양쪽 영역을 각각 정렬한다.
//	{
//		a = divide_dom(arr, x, y); //함수 호출하여 영역을 나누어 swap함수를 호출해 영역을 교환하도록 한다.
//
//		quick_sort(arr, x, a - 1); //크기가 1이나 0이될때까지 반복할 수 있도록 재귀함수 형성
//
//		quick_sort(arr, a + 1, y);
//	}
//}
//
//void swap(int arr[], int a, int b) //양 영역을 스왑할 swap함수
//{
//	int tmp = arr[a];
//
//	arr[a] = arr[b];
//
//	arr[b] = tmp;
//}
//
//int main(void)
//{
//	int n, i;
//	int arr[100];
//
//	scanf("%d", &n); //총 개수 입력
//
//	for (i = 0; i < n; i++)  //임의의 순서의 정수 입력
//	{
//		scanf("%d", arr + i);
//	}
//
//	quick_sort(arr, 0, n - 1); //퀵 정렬 함수 호출
//
//
//	for (i = 0; i < n; i++)  //퀵 정렬을 통해 정렬된 정수 출력
//	{
//		printf(" %d ", arr[i]);
//	}
//
//	return 0;
//}
/*
사용한 정렬 : 퀵 정렬
기억장소 즉 메모리에는 제한이 없기 때문에 O(N^2)의 시간 복잡도를 갖는
퀵 정렬(Quick sort)를 사용하였다.
시간복잡도 : O(N^2)
식: f(n) = 2n + 2\


식을 구하는 방법에 대해 제대로 이해가 되지 않아 직감적으로 식을 작성하였습니다. 죄송합니다.
*/
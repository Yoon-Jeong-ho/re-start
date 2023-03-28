#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>

int main_04_01() {
	int N, * X, num, * imfo, lenth,tmp;
	scanf("%d", &N);
	X = (int*)malloc(sizeof(int) * N); //X 배열 동적 할당
	for (int i = 0; i < N; i++) scanf("%d", &X[i]); // 입력하기
	scanf("%d", &num); // 뒤집기 정보 개수 입력
	imfo = (int*)malloc(sizeof(int) * num*2); // 정보 저장할 배열 동적 할당
	for (int i = 0; i < num*2; i++) scanf("%d", &imfo[i]); // 정보 입력
	for (int i = 0; i < num*2; i++) {
		lenth = imfo[i+1] - imfo[i]+1; // 길이 정해서 짝수 홀수 상황 넘어갈 수 있도록 설정
		printf("%d %d\n", imfo[i], imfo[i + 1]);
		for (int j = 0; j < lenth/2; j ++) { // 위치 바꾸기
			tmp = X[imfo[i]+j];
			X[imfo[i] + j] = X[imfo[i + 1] - j];
			X[imfo[i + 1] - j] = tmp;
			printf("%d %d\n", X[imfo[i] + j],X[imfo[i + 1] - j]);
		}
		i++;
	}
	for (int i = 0; i < N; i++) printf(" %d", X[i]);
	free(imfo);
	free(X);
	
	return 0;
}

int main_04_02() {
	int N, * X, num, * imfo, *tmp;
	scanf("%d", &N);
	X = (int*)malloc(sizeof(int) * N); //X 배열 동적 할당
	for (int i = 0; i < N; i++) scanf("%d", &X[i]); // 입력하기
	scanf("%d", &num); // 위치 바꾸기 정보 개수 입력
	imfo = (int*)malloc(sizeof(int) * num); // 정보 저장할 배열 동적 할당
	tmp = (int*)malloc(sizeof(int) * num);
	for (int i = 0; i < num; i++) scanf("%d", &imfo[i]); // 정보 입력
	tmp[0] = X[imfo[1]]; // 첫번째 배열의 숫자가 들어갈 곳의 정보 저장하기
	X[imfo[1]] = X[imfo[0]]; // 첫번째 배열의 숫자 집어넣기
	for (int i = 1; i < num-2; i++) { // 차례대로 뒤에 정보 빼고 앞의 숫자 넣기
		tmp[i] = X[imfo[i + 1]]; // i번째 배열의 숫자가 들어갈 곳의 정보 저장하기
		X[imfo[i+1]] = tmp[i - 1];//i번째 배열 숫자 집어넣기		
	}
	if (num == 2) X[imfo[0]] = tmp[num - 2];
	else X[imfo[0]] = tmp[num - 3];
	
	for (int i = 0; i < N; i++) printf(" %d", X[i]);
	free(imfo);
	free(X);
	free(tmp);
	return 0;
}

int main_04_03() {
	int** arr, N,num=1;
	scanf("%d", &N);
	arr = (int**)malloc(sizeof(int*) * N);
	for (int i = 0; i < N; i++) arr[i] = (int*)malloc(sizeof(int) * N); // 동적할당하여 크기 만들어줌
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i % 2 == 0) arr[i][j] = num++; // 
			else arr[i][N - j - 1] = num++;
		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) printf(" %d", arr[i][j]);
		printf("\n");

	}
	free(arr);
	return 0;
}

int main_04_04() {
	int** arr, N,M, num = 1,teg =0;
	scanf("%d %d", &N, &M);
	arr = (int**)malloc(sizeof(int*) * N);
	for (int i = 0; i < N; i++) arr[i] = (int*)malloc(sizeof(int) * M); // 동적할당하여 크기 만들어줌
	int max = N * M, i= 0, j=0;
	while (num <= max) {
		while (num <= max && j < M - teg) arr[i][j++] = num++;// 좌측 상단에서 우로 쭉 진행
		j--; // 오버해서 와일문 깨진것 복구
		i++;
		while (num <= max && i < N - teg)arr[i++][j] = num++;//우측 상단에서 아래로 쭉 진행
		i--;
		j--;
		while (num <= max && j >= teg)arr[i][j--] = num++; // 우측하단에서 좌로 쭉 진행
		j++;
		i--;
		teg++;
		while (num <= max && i >= teg)arr[i--][j] = num++; // 좌측하단에서 위로 쭉 진행
		i++;
		j++;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) printf(" %d", arr[i][j]);
		printf("\n");
		
	}
	free(arr);
	return 0;
}

int main() {
	int** arr, N, M, num = 1, teg = 0, sum=0;
	scanf("%d %d", &N, &M);
	arr = (int**)malloc(sizeof(int*) * N);
	for (int i = 0; i < N; i++) arr[i] = (int*)malloc(sizeof(int) * M); // 동적할당하여 크기 만들어줌
	int max = N * M, i = 0, j = 0;
	while (num <= max) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M ; j++) {
				if (i+j == sum) arr[i][j] = num++; // 대각선의 행과 열의 합은 항상 같다는 점을 이용해서 진행
			}
		}
		sum++;

	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) printf(" %d", arr[i][j]);
		printf("\n");

	}
	free(arr);
	return 0;
}
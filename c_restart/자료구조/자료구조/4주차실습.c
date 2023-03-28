#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>

int main_04_01() {
	int N, * X, num, * imfo, lenth,tmp;
	scanf("%d", &N);
	X = (int*)malloc(sizeof(int) * N); //X �迭 ���� �Ҵ�
	for (int i = 0; i < N; i++) scanf("%d", &X[i]); // �Է��ϱ�
	scanf("%d", &num); // ������ ���� ���� �Է�
	imfo = (int*)malloc(sizeof(int) * num*2); // ���� ������ �迭 ���� �Ҵ�
	for (int i = 0; i < num*2; i++) scanf("%d", &imfo[i]); // ���� �Է�
	for (int i = 0; i < num*2; i++) {
		lenth = imfo[i+1] - imfo[i]+1; // ���� ���ؼ� ¦�� Ȧ�� ��Ȳ �Ѿ �� �ֵ��� ����
		printf("%d %d\n", imfo[i], imfo[i + 1]);
		for (int j = 0; j < lenth/2; j ++) { // ��ġ �ٲٱ�
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
	X = (int*)malloc(sizeof(int) * N); //X �迭 ���� �Ҵ�
	for (int i = 0; i < N; i++) scanf("%d", &X[i]); // �Է��ϱ�
	scanf("%d", &num); // ��ġ �ٲٱ� ���� ���� �Է�
	imfo = (int*)malloc(sizeof(int) * num); // ���� ������ �迭 ���� �Ҵ�
	tmp = (int*)malloc(sizeof(int) * num);
	for (int i = 0; i < num; i++) scanf("%d", &imfo[i]); // ���� �Է�
	tmp[0] = X[imfo[1]]; // ù��° �迭�� ���ڰ� �� ���� ���� �����ϱ�
	X[imfo[1]] = X[imfo[0]]; // ù��° �迭�� ���� ����ֱ�
	for (int i = 1; i < num-2; i++) { // ���ʴ�� �ڿ� ���� ���� ���� ���� �ֱ�
		tmp[i] = X[imfo[i + 1]]; // i��° �迭�� ���ڰ� �� ���� ���� �����ϱ�
		X[imfo[i+1]] = tmp[i - 1];//i��° �迭 ���� ����ֱ�		
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
	for (int i = 0; i < N; i++) arr[i] = (int*)malloc(sizeof(int) * N); // �����Ҵ��Ͽ� ũ�� �������
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
	for (int i = 0; i < N; i++) arr[i] = (int*)malloc(sizeof(int) * M); // �����Ҵ��Ͽ� ũ�� �������
	int max = N * M, i= 0, j=0;
	while (num <= max) {
		while (num <= max && j < M - teg) arr[i][j++] = num++;// ���� ��ܿ��� ��� �� ����
		j--; // �����ؼ� ���Ϲ� ������ ����
		i++;
		while (num <= max && i < N - teg)arr[i++][j] = num++;//���� ��ܿ��� �Ʒ��� �� ����
		i--;
		j--;
		while (num <= max && j >= teg)arr[i][j--] = num++; // �����ϴܿ��� �·� �� ����
		j++;
		i--;
		teg++;
		while (num <= max && i >= teg)arr[i--][j] = num++; // �����ϴܿ��� ���� �� ����
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
	for (int i = 0; i < N; i++) arr[i] = (int*)malloc(sizeof(int) * M); // �����Ҵ��Ͽ� ũ�� �������
	int max = N * M, i = 0, j = 0;
	while (num <= max) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M ; j++) {
				if (i+j == sum) arr[i][j] = num++; // �밢���� ��� ���� ���� �׻� ���ٴ� ���� �̿��ؼ� ����
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
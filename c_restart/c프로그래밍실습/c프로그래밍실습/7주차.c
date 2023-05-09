#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int main_07_09_01() {
	int N,result=0;
	scanf("%d", &N);
	while (N > 0) {
		if (N % 10 == 3) result++;
		N /= 10;
	}
	printf("%d", result);
	return 0;
}

int main_07_09_00() {
	int N, result = 0;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		int num = i;
		while (num > 0) {
			if (num % 10 == 3) result++;
			num/= 10;
		}
	}
	printf("%d", result);
	return 0;
}

int main_7_06_04() {
	int N, result = 0;
	scanf("%d", &N);
	while (N > 0) {
		result += N % 10;
		N /= 10;
	}
	printf("%d", result);
	return 0;
}

int main_07_06_05() {
	int N, result = 0;
	scanf("%d", &N);
	while (N >= 10) {
		while (N > 0) {
			result += N % 10;
			N /= 10;
		}
		N = result;
		result = 0;
	}
	printf("%d",N);
	return 0;
}

int main_07_06_05_01() {
	int num;
	scanf("%d", &num);
	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= 6; j++) {
			for (int k = 1; k <= 6; k++) {
				if (i + j + k == num) printf("%d %d %d\n",i, j, k);
			}
		}
	}
	return 0;
}

int main_07_06_06() {
	int num,result = 0;
	scanf("%d", &num);
	for (int i = 1;; i++) {
		result += i;
		if (i == num)break;
	}

	printf("%d",result);
	return 0;
}
int main_07_06_28282828	() {
	int num,sum=0,len=0;
	double mean = 0;
	while (1) {
		scanf("%d", &num);
		if (num <= 0) break;
		if (num > 100) continue;
		sum += num;
		len++;
	}
	mean = (double)sum / len;
	printf("%d %.2f %d", sum, mean, len);
	return 0;
}

int main_07_19281629812() {
	int num[5],mean=0;
	for (int i = 0; i < 5; i++) {
		scanf("%d", &num[i]);
		mean += num[i];
	}
	mean /= 5;
	for (int i = 0; i < 5; i++) {
		if (num[i] > mean) printf("%d\n", num[i]);
	}

	return 0;
}

int main_029876156172849128476125467() {
	char c[7];
	int count = 0, result = 0;
	for (int i = 0; i < 7; i++) {
		scanf("%c", &c[i]);
		if (count == 0) {
			if (c[i] == 'c') count++;
		}
		else if (count == 1) {
			if (c[i] == 'a') count++;
			else count = 0;
		}
		else if (count == 2) {
			if (c[i] == 't') {
				count=0;
				result++;
			}
			else count = 0;
		}
	}
	printf("%d", result);
	return 0;
}

int main_1738913() {
	int  num[5],tmp;
	for (int i = 0; i < 5; i++) scanf("%d", &num[i]);
	for (int i = 0; i < 5; i++) {
		for (int j = i; j < 5; j++) {
			if (num[i] < num[j]) {
				tmp = num[i];
				num[i] = num[j];
				num[j] = tmp;
			}
		}
	}
	printf("%d\n%d", num[0], num[1]);
	return 0;
}

int main_0987625
() {
	int num1=0, num2=0, num3=0, num[10];
	for (int i = 0; i < 10; i++) {
		scanf("%d", &num[i]);
		if (num[i] == 1) num1++;
		if (num[i] == 2) num2++;
		if (num[i] == 3) num3++;
	}
	printf("1:");
	for (int i = 0; i < num1; i++)printf("*");
	printf("\n");
	printf("2:");
	for (int i = 0; i < num2; i++)printf("*");
	printf("\n");
	printf("3:");
	for (int i = 0; i < num3; i++)printf("*");
	printf("\n");
	return 0;
}

int main_9387656789() {
	char c[5];
	for (int i = 0; i < 5; i++) scanf("%c", &c[i]);
	for (int i = 5; i > 0; i--) {
		for (int j = 0; j <5; j++) {
			printf("%c", c[(i + j) % 5]);
		}
		printf("\n");
	}
	return 0;
}

int main_9876543() {
	char c[3], t;
	int num[3] = { 0,0,0 };
	for (int i = 0; i < 3; i++) scanf("%c", &c[i]);
	getchar();
	for (int i = 0; i < 5; i++) {
		scanf("%c",&t);
		getchar();
		if (c[0] == t) {
			num[0] = 1;
		}
		if (c[1] == t) {
			num[1] = 1;
		}
		if (c[2] == t) {
			num[2] = 1;
		}
		for (int j = 0; j < 3; j++) {
			if (num[j] == 1) printf(" %c", c[j]);
			else printf(" _");
		}
		if (num[0] && num[1] && num[2]) break;
	}

	return 0;
}

int main_987655367845() {
	int num[10], result, isused[10], count = 0, t = 0;;
	for (int i = 0; i < 10; i++) {
		scanf("%d", &num[i]);
	}
	for (int i = 0; i < 10; i++) {
		result = 0;
		for (int j = i; j < 10; j++) {
			if (num[i] == num[j]) result++;
		}
		t = 0;
		for (int j = 0; j < count; j++) {
			if (num[i] == isused[j]) t = 1;
		}
		if (t == 1) continue;
		printf("%d %d\n", num[i], result);
		isused[count++] = num[i];
	}

	return 0;
}


int main_098765456789() {
	int num[5],tmp;
	for (int i = 0; i < 5; i++)  scanf("%d", &num[i]);
	for (int i = 0; i < 4; i++) {
		for (int j = i; j < 5; j++) {
			if (num[i] > num[j]) {
				tmp = num[i];
				num[i] = num[j];
				num[j] = tmp;
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		printf("%d\n", num[i]);
	}

	return 0;
}

int main_9872652678() {
	int arr[5], num[5] = { 1,1,1,1,1 };
	for (int i = 0; i < 5; i++) scanf("%d", &arr[i]);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (arr[i] < arr[j]) num[i]++;
		}
	}
	for (int i = 0; i < 5; i++) printf("%d=r%d ", arr[i], num[i]);
	return 0;
}


int main_2023_9876256789298() {
	int a[100], b[100], c[200], count = 0, same, tmp, aCnt=0,btmp=0;
	for (int i = 0; i < 101; i++) {
		scanf("%d", &tmp);
		if (tmp < 0) break;
		a[aCnt++] = tmp;
		same = 0;
		for (int j = 0; j < count; j++) { // ���� �� �ֳ� ã��
			if (a[i] == c[j]) same = 1; // ������ ������ 1�� �����
		}
		if (same == 0) c[count++] = a[i]; // ���� ���� ������ c�� �ֱ�
	}
	for (int i = 0; i < 101; i++) {
		scanf("%d", &tmp);
		if (tmp < 0) break;
		b[btmp++] = tmp;
		same = 0;
		for (int j = 0; j < count; j++) { // ���� �� �ֳ� ã��
			if (b[i] == c[j]) same = 1; // ������ ������ 1�� �����
		}
		if (same == 0) c[count++] = b[i]; // ���� ���� ������ c�� �ֱ�
	}
	for (int i = 0; i < count; i++) {//���Ľ���
		for (int j = i + 1; j < count; j++) {
			if (c[i] > c[j]) { // ���� ū��� �ڶ� �ٲ۴�.
				tmp = c[i];
				c[i] = c[j];
				c[j] = tmp;
			}
		}
	}
	for (int i = 0; i < count; i++) printf(" %d", c[i]);
	return 0;
}	

int main_ahdml2_128() {
	int N, num[50],same,count;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &num[i]);
	}
	for (int i = 0; i < N; i++) {
		same = 0;// �ߺ� ���� ��� 0
		for (int j = 0; j < i; j++) {
			if (num[i] == num[j]) same = 1; // �ߺ� ���� ��� 1
		}
		if (same == 1) continue; // �ߺ������� ���� i ����
		count = 0; //�ߺ� ��Ƴ���
		for (int j = i; j < N; j++) {
			if (num[i] == num[j]) count++; //�ߺ��� ī��Ʈ �ϳ��� �ø���
		}
		printf("%d %d\n", num[i], count);
	}

	return 0;
}

int main_quiz9_2() {
	int firstcount = 0, secondcount = 0, flag = 0;
	char x[100], y[100], tmp;
	while (1) {
		scanf("%c", &tmp);
		if (flag == 1 && tmp == '*') break; // �ι�° * �Է����� ���̴�.
		else if (tmp == '*') { // ù��° �ܾ� ��
			flag = 1;
			continue; // �Էµ��� �ʰ� ������ ����
		}
		if (flag == 0) { // ù��° �ܾ�
			x[firstcount++] = tmp;
		}
		else if (flag == 1) { // �ι�° �ܾ�
			y[secondcount++] = tmp;
		}
	}
	for (int i = 0; i < firstcount && i < secondcount; i++) {
		if (x[i] > y[i]) { // x�� ū ���
			flag = 0;
		}
		else if (x[i] < y[i]) { // y�� ū ���
			flag = 1;
		}
		else if (i == firstcount - 1 || i == secondcount - 1) { // ������ ���� �Ȱ��� ��� �� ª�� ���� ������.
			if (firstcount < secondcount) flag = 1;
			else if (firstcount > secondcount) flag = 0;
		}
	}
	if (flag == 0) {
		for (int i = 0; i < secondcount; i++) printf("%c", y[i]);
	}
	else {
		for (int i = 0; i < firstcount; i++) printf("%c", x[i]);
	}

	return 0;
}

int main_quiz9_03_02() {
	int N, num[101], max=0,count=1, result[101];
	scanf("%d", &N);
	for (int i = 0; i < N; i++)scanf("%d", &num[i]);
	for (int i = 0; i < N-1; i++) {
		if (num[i] * num[i + 1] < 0) { // ���� �ٲ�� ���
			count++;
		}
		else count = 1;
		if (count >= max && count > 1) { // ���� ū ������ ��ü�ؾ��� ��..
			max = count;
			for (int j = 0; j < max; j++) {
				result[j] = num[i - max+2 + j];
			}
		}
		else if (max == 0 && i == N - 2) {
			result[0] = num[i+1];
			max++;
		}
	}
	printf("%d\n", max);
	for (int i = 0; i < max; i++) printf(" %d", result[i]);
	return 0;
}	

int main_quiz9_04_02() {
	int num, S1[20], S2[20], rank[20],count;
	double mean[20];
	scanf("%d", &num); 
	for (int i = 0; i < num; i++)scanf("%d", &S1[i]); //�Է�
	for (int i = 0; i < num; i++) {
		scanf("%d", &S2[i]); //�Է�
		mean[i] = ((double)S1[i]*40 + S2[i]*60) / 100; // ��� ���
	}
	for (int i = 0; i < num; i++) { // ��� ���
		count = 1;
		for (int j = 0; j < num; j++) {
			if (mean[i] < mean[j]) count++; // ū���� ������ ���ڸ� ���������μ� ��� ����
		}
		rank[i] = count;
	}
	for (int i = 0; i < num; i++) { // ��¹�
		printf("%d %d %d %.1f %d", i + 1, S1[i], S2[i], mean[i], rank[i]);
		if (S2[i] >= 80 || rank[i] <= num * 0.7) printf(" P\n"); // P ����
		else printf(" F\n"); // ���� �̴޽�
	}
	return 0;
}


int main() {
	printf("%d %d",'0' ,'9');

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

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


int main() {
	int a[100], b[100], c[200], count = 0, same, tmp, aCnt=0,btmp=0;
	for (int i = 0; i < 101; i++) {
		scanf("%d", &tmp);
		if (tmp < 0) break;
		a[aCnt++] = tmp;
		same = 0;
		for (int j = 0; j < count; j++) { // 같은 것 있나 찾기
			if (a[i] == c[j]) same = 1; // 있으면 변수를 1로 만들기
		}
		if (same == 0) c[count++] = a[i]; // 같은 것이 없으면 c에 넣기
	}
	for (int i = 0; i < 101; i++) {
		scanf("%d", &tmp);
		if (tmp < 0) break;
		b[btmp++] = tmp;
		same = 0;
		for (int j = 0; j < count; j++) { // 같은 것 있나 찾기
			if (b[i] == c[j]) same = 1; // 있으면 변수를 1로 만들기
		}
		if (same == 0) c[count++] = b[i]; // 같은 것이 없으면 c에 넣기
	}
	for (int i = 0; i < count; i++) {//정렬시작
		for (int j = i + 1; j < count; j++) {
			if (c[i] > c[j]) { // 앞이 큰경우 뒤랑 바꾼다.
				tmp = c[i];
				c[i] = c[j];
				c[j] = tmp;
			}
		}
	}
	for (int i = 0; i < count; i++) printf(" %d", c[i]);
	return 0;
}	
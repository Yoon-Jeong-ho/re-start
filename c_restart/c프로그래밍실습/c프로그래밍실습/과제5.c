#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int max_num(int n, int m);
int min_num(int n, int m);

int main_2023_08_2_2() {
	int n[1000], t, s, e,c=0,tmp,max,min;
	while (1) {
		scanf("%d", &n[c++]); // 0���ö� ���� ���� �Է�
		if (n[c-1] == 0)break;
	}
	scanf("%d", &t);
	
	for (int i = 0; i < t; i++) {// t��ŭ �ݺ�
		scanf("%d %d", &s, &e); // �Է¹ޱ�
		max = n[s];
		min = n[s]; //�񱳸� ���� �ϴ� ����ֱ�
		for (int j = 0; j < (e-s+1) / 2; j++) { // ��ȯ�ϱ� ���� �ݺ���
			tmp = n[s + j];
			n[s + j] = n[e - j];
			n[e - j] = tmp; // ��ȯ�ϱ�
			if (max < max_num(n[s + j], n[e - j])) max = max_num(n[s + j], n[e - j]); // max�� ���� ū ��� max �ٲ��ֱ�
			if (min > min_num(n[s + j], n[e - j])) min = min_num(n[s + j], n[e - j]); // min�� ���� ���� ��� min �ٲ��ֱ�
		}
		if ((e - s) % 2 == 0) { // �߾Ӱ��� ��� ���Ѱ��
			tmp = n[(e + s) / 2];
			max = max_num(tmp, max);
			min = min_num(tmp, min);
		}
		for (int j = 0; j < c - 1; j++) printf("%d ", n[j]);
		printf("\n%d %d\n", max, min);
	}
	return 0;
}


int max_num(int n, int m) {
	if (n > m) return n; //n�� ū ��� n�� ��ȯ�Ѵ�.
	else return m; //���ų� m�� ū ��� m�� ��ȯ�Ѵ�.
}

int min_num(int n, int m) {
	if (n < m) return n; //n�� ���� ��� n�� ��ȯ�Ѵ�.
	else return m; //���ų� m�� ���� ��� m�� ��ȯ�Ѵ�.
}

int multiple(int x,int y);
int maximum(int x, int y);
int digit_maximum(int x);

int main_2023_08_03() {
	int n, m, k,max=0;
	scanf("%d %d %d", &n, &m, &k);
	for (int i = n; i <= m; i++) {
		if (multiple(i, k) == 1) { // ����ΰ���ڸ����� �ִ밪 ���ϱ�
			max = maximum(digit_maximum(i), max);
		}
		else { // ����� �ƴѰ�� �������� �ִ밪
			max = maximum(max, i % k);
		}
	}
	printf("%d ",max);
	return 0;
}

int multiple(int x, int y) {
	int i = 1;
	while (y*i <= x) {
		if (y * i++ == x) return 1; // ����ΰ��
	}
	return 0;//����� �ƴѰ��
}
int maximum(int x, int y) {
	if (x > y) return x;
	else return y;
}
int digit_maximum(int x) {
	int max = 0;
	while (x > 0) {
		if (x % 10 > max) max = x % 10; // ���� ū�� ã�� ����
		x /= 10;//���ڸ� ���̱�
	}
	return max;
}


int count_prime_number(int cnt, int num);
int is_prime_number(int num);

int main_2023_08_04_02() {
	int n, num[1000], count = 0,max = 0,result;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &num[i]);
		count = count_prime_number(count, num[i]);
		if (max < count) {
			max = count;
			result = num[i];
		}
	}
	if (max == 0) printf("0");
	else printf("%d\n%d", max, result);
	return 0;
}

int count_prime_number(int cnt, int num) {
	if (is_prime_number(num) && num < 100) {//�Ҽ��� ���� 100�̸��ΰ��
		return cnt + 1;
	}
	else { // �Ҽ� �ƴѰ�� �ƴϸ� 100�̻��� ���
		return 0;
	}

}
int is_prime_number(int num) {
	if (num == 1) return 0;
	for (int i = 2; i < num; i++) {
		if (num % i == 0) return 0; // �Ҽ��� �ƴѰ��
	}
	return 1; // �Ҽ��� ���
}

int add_digits(int N);

int main_2023_08_05_03() {
	int n,min,result,c=0;
	while (1) {
		scanf("%d", &n);
		if (n < 0)break;
		if (c == 0) { // ó���� ���
			result = n;
			min = add_digits(n);
		}
		if (add_digits(n) < min) { // �ּҰ� ��ü�ؾ� �� ���
			result = n;
			min = add_digits(n);
		}
		c=1;
	}
	printf("%d %d", result, min);
	return 0;
}

int add_digits(int n) {
	int sum = 0;
	do {
		sum = 0;
		while (n > 0) {
			sum += n % 10; //���ڸ��� ���ؼ� ����ֱ�
			n /= 10;//���ڸ� ���ֱ�
		}
		n = sum;
	} while (sum >= 10);
	return sum;
}

int main_2022_02_01_02() {
	int n, num[101], c = 0,tmp,count=0 , max=0,m;
	scanf("%d", &m);
	for(int i = 0 ; i < m ; i++){
		scanf("%d", &n);
		if (n <= 0) continue;
		num[c++] = n; // 0 �ʰ��� ���� �迭�� ����ֱ�
	}
	if (c % 2 == 0) { // ¦������ ��� �������� ������ �Ѵ�
		for (int i = 0; i < c; i++) {
			for (int j = i + 1; j < c; j++) {
				if (num[i] < num[j]) { // �տ��ִ� ���� ���� ��� ��ȯ�ʿ�
					tmp = num[i];
					num[i] = num[j];
					num[j] = tmp;
				}
			}
		}
	}
	else { // Ȧ���� ��� �������� ������ �Ѵ�.
		for (int i = 0; i < c; i++) {
			for (int j = i + 1; j < c; j++) {
				if (num[i] > num[j]) { // �տ��ִ� ���� Ŭ ��� ��ȯ�ʿ�
					tmp = num[i];
					num[i] = num[j];
					num[j] = tmp;
				}
			}
		}
	}
	printf("%d\n", c);
	for (int i = 0; i < c; i++) {
		printf("%d ", num[i]);
		if (num[i] % 2) {//Ȧ���ΰ��
			count++;
			if (max < count) max = count; // �ִ밪 ��ȯ
		}
		else { //¦���� ���
			count = 0; // �ٽ� ī�����ϱ�
		}
	}
	printf("\n%d\n", max);
	return 0;
} 


int main_2022_02_02_02() {
	int n, m, num[100], c, overmean[100], max[100], min[100], count = 0,max1,min1;
	double mean;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d", &num[i]);
	for (int i = 0; i < n/m; i++) {
		mean = 0;
		max1 = num[i * m];
		min1 = num[i * m];
		for (int j = 0; j < m; j++) { // m���� ������ �־���.
			mean += num[i * m + j];//����� ���ϱ� ����
			if (num[i * m + j] > max1) max1 = num[i * m + j]; // �ִ밪 ã��
			if (num[i * m + j] < min1) min1 = num[i * m + j]; // �ּҰ� ã��
		}
		max[i] = max1; // �ִ밪 ����ֱ�
		min[i] = min1; //�ּҰ� ����ֱ�
		mean /= m;
		for (int j = 0; j < m; j++) { // m���� ������ �־���.
			if (num[i * m + j] >= mean) {
				overmean[count++] = num[i * m + j];
			}
		}
	} // ���� �������� ���� ��츦 ���ߴ�.
	for (int i = m*(n/m); i < n; i++) {
		mean += num[i];
		max1 = num[i];
		min1 = num[i];
	}
	mean /= (n - m * (n / m));
	for (int i = m * (n / m); i < n; i++) {
		if (num[i] >= mean) overmean[count++] = num[i];
		if (num[i] > max1) max1 = num[i];
		if (num[i] < min1) min1 = num[i];
		max[n / m] = max1;
		min[n / m] = min1;
	}
	for (int i = 0; i < count; i++) printf(" %d", overmean[i]); // ù��° ���
	printf("\n");
	for (int i = 0; i < (n + m - 1) / m; i++) printf(" %d", max[i]);
	printf("\n");
	for (int i = 0; i < (n + m - 1) / m; i++) printf(" %d", min[i]);
	return 0;
}

int main() {
	int n, s1[20], s2[20],rank[20],c;
	double mean[20],tmp;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", &s1[i]);
	for (int i = 0; i < n; i++) {
		scanf("%d", &s2[i]);
		mean[i] = s1[i]*40 + s2[i]*60; // �ϴ� ���ϱ�
		mean[i] /= 100; // ������ ��ձ��ϱ�
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (mean[i] < mean[j]) { // �ڿ��� ����� �� ũ�Ƿ� ������ ����� ��ü�� ������ �����.
				tmp = mean[i];
				mean[i] = mean[j];
				mean[j] = tmp; // ��� �ٲٱ�
				tmp = s1[i];
				s1[i] = s1[j];
				s1[j] = tmp; // 1�� ���� �ٲٱ�
				tmp = s2[i];
				s2[i] = s2[j];
				s2[j] = tmp; // 2������ �ٲٱ�
			}
		}
		c = 1; // rank�� ���� ����
		for (int j = 0; j < n; j++) {
			if (mean[i] < mean[j])c++;
		}
		rank[i] = c;
	}
	for (int i = 0; i < n; i++) {
		printf("%d %d %.1f %d", s1[i], s2[i], mean[i], rank[i]);
		if (rank[i] <= n * 3 / 10) printf(" A\n");//A�� ���
		else if (s2[i] >= 60 || rank[i] <= n * 7 / 10)printf(" B\n");//B�ΰ��
		else printf(" F\n");
	}

	return 0;
}
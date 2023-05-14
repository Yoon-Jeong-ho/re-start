#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

int max_num(int n, int m);
int min_num(int n, int m);

int main_2023_08_2_2() {
	int n[1000], t, s, e,c=0,tmp,max,min;
	while (1) {
		scanf("%d", &n[c++]); // 0나올때 까지 무한 입력
		if (n[c-1] == 0)break;
	}
	scanf("%d", &t);
	
	for (int i = 0; i < t; i++) {// t만큼 반복
		scanf("%d %d", &s, &e); // 입력받기
		max = n[s];
		min = n[s]; //비교를 위해 일단 집어넣기
		for (int j = 0; j < (e-s+1) / 2; j++) { // 교환하기 위해 반복문
			tmp = n[s + j];
			n[s + j] = n[e - j];
			n[e - j] = tmp; // 교환하기
			if (max < max_num(n[s + j], n[e - j])) max = max_num(n[s + j], n[e - j]); // max값 보다 큰 경우 max 바꿔주기
			if (min > min_num(n[s + j], n[e - j])) min = min_num(n[s + j], n[e - j]); // min값 보다 작은 경우 min 바꿔주기
		}
		if ((e - s) % 2 == 0) { // 중앙값을 계산 안한경우
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
	if (n > m) return n; //n이 큰 경우 n을 반환한다.
	else return m; //같거나 m이 큰 경우 m을 반환한다.
}

int min_num(int n, int m) {
	if (n < m) return n; //n이 작은 경우 n을 반환한다.
	else return m; //같거나 m이 작은 경우 m을 반환한다.
}

int multiple(int x,int y);
int maximum(int x, int y);
int digit_maximum(int x);

int main_2023_08_03() {
	int n, m, k,max=0;
	scanf("%d %d %d", &n, &m, &k);
	for (int i = n; i <= m; i++) {
		if (multiple(i, k) == 1) { // 배수인경우자릿수중 최대값 구하기
			max = maximum(digit_maximum(i), max);
		}
		else { // 배수가 아닌경우 나머지중 최대값
			max = maximum(max, i % k);
		}
	}
	printf("%d ",max);
	return 0;
}

int multiple(int x, int y) {
	int i = 1;
	while (y*i <= x) {
		if (y * i++ == x) return 1; // 배수인경우
	}
	return 0;//배수가 아닌경우
}
int maximum(int x, int y) {
	if (x > y) return x;
	else return y;
}
int digit_maximum(int x) {
	int max = 0;
	while (x > 0) {
		if (x % 10 > max) max = x % 10; // 가장 큰값 찾는 과정
		x /= 10;//한자리 줄이기
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
	if (is_prime_number(num) && num < 100) {//소수일 경우와 100미만인경우
		return cnt + 1;
	}
	else { // 소수 아닌경우 아니면 100이상인 경우
		return 0;
	}

}
int is_prime_number(int num) {
	if (num == 1) return 0;
	for (int i = 2; i < num; i++) {
		if (num % i == 0) return 0; // 소수가 아닌경우
	}
	return 1; // 소수인 경우
}

int add_digits(int N);

int main_2023_08_05_03() {
	int n,min,result,c=0;
	while (1) {
		scanf("%d", &n);
		if (n < 0)break;
		if (c == 0) { // 처음일 경우
			result = n;
			min = add_digits(n);
		}
		if (add_digits(n) < min) { // 최소값 교체해야 할 경우
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
			sum += n % 10; //한자리씩 더해서 집어넣기
			n /= 10;//한자리 없애기
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
		num[c++] = n; // 0 초과인 것인 배열에 집어넣기
	}
	if (c % 2 == 0) { // 짝수개인 경우 내림차순 정리를 한다
		for (int i = 0; i < c; i++) {
			for (int j = i + 1; j < c; j++) {
				if (num[i] < num[j]) { // 앞에있는 것이 작을 경우 교환필요
					tmp = num[i];
					num[i] = num[j];
					num[j] = tmp;
				}
			}
		}
	}
	else { // 홀수인 경우 오름차순 정리를 한다.
		for (int i = 0; i < c; i++) {
			for (int j = i + 1; j < c; j++) {
				if (num[i] > num[j]) { // 앞에있는 것이 클 경우 교환필요
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
		if (num[i] % 2) {//홀수인경우
			count++;
			if (max < count) max = count; // 최대값 교환
		}
		else { //짝수인 경우
			count = 0; // 다시 카운팅하기
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
		for (int j = 0; j < m; j++) { // m개씩 나누어 주었다.
			mean += num[i * m + j];//평균을 구하기 위함
			if (num[i * m + j] > max1) max1 = num[i * m + j]; // 최대값 찾기
			if (num[i * m + j] < min1) min1 = num[i * m + j]; // 최소값 찾기
		}
		max[i] = max1; // 최대값 집어넣기
		min[i] = min1; //최소값 집어넣기
		mean /= m;
		for (int j = 0; j < m; j++) { // m개씩 나누어 주었다.
			if (num[i * m + j] >= mean) {
				overmean[count++] = num[i * m + j];
			}
		}
	} // 아직 나머지가 남은 경우를 안했다.
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
	for (int i = 0; i < count; i++) printf(" %d", overmean[i]); // 첫번째 출력
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
		mean[i] = s1[i]*40 + s2[i]*60; // 일단 더하기
		mean[i] /= 100; // 나눠서 평균구하기
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (mean[i] < mean[j]) { // 뒤에가 평균이 더 크므로 앞으로 땅기기 전체를 앞으로 땅긴다.
				tmp = mean[i];
				mean[i] = mean[j];
				mean[j] = tmp; // 평균 바꾸기
				tmp = s1[i];
				s1[i] = s1[j];
				s1[j] = tmp; // 1차 시험 바꾸기
				tmp = s2[i];
				s2[i] = s2[j];
				s2[j] = tmp; // 2차시험 바꾸기
			}
		}
		c = 1; // rank를 위한 변수
		for (int j = 0; j < n; j++) {
			if (mean[i] < mean[j])c++;
		}
		rank[i] = c;
	}
	for (int i = 0; i < n; i++) {
		printf("%d %d %.1f %d", s1[i], s2[i], mean[i], rank[i]);
		if (rank[i] <= n * 3 / 10) printf(" A\n");//A인 경우
		else if (s2[i] >= 60 || rank[i] <= n * 7 / 10)printf(" B\n");//B인경우
		else printf(" F\n");
	}

	return 0;
}
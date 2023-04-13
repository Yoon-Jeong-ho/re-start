#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main_05_02() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n-i; j++) {
			printf("*");
		}
		printf("\n");
	}
	return 0;
}


int main_05_03() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i*2; j++) {
			printf("*");
		}
		printf("\n");
	}
	return 0;
}

int main_06_05_05_05() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i; j++) {
			printf(" ");
		}
		for (int j = 0; j <=i*2; j++) {
			printf("*");
		}
		for (int j = 0; j < n - i; j++) {
			printf(" ");
		}
		printf("\n");
	}
	return 0;
}

int main_06_01_01() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j || i + j == n - 1) printf("X ");
			else printf("O ");
		}
		printf("\n");
	}
	return 0;
}

int main_06_01_02() {
	int n,num =1;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", num++ % 10);
		}
		printf("\n");
	}
	return 0;
}

int main_06_05_01_01(){
	int n, num = 1;
	scanf("%d", &n);
	for (int i = 1; i < n+1; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", (i+j)% 10);
		}
		printf("\n");
	}
	return 0;
}

int main_06_01_02_07() {
	int n, num = 1;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			printf(" %d", num++ % 10);
		}
		printf("\n");
	}
	return 0;
}

int main_23_3_13_5152() {
	int n, m,num=0	;
	scanf("%d %d", &n, &m);
	for (int i = n; i <= m; i++) {
		int total = 1;
		printf("%d!=", i);
		for (int j = 1; j < i; j++) {
			printf("%d*", j);
			num = j;
			total *= num;
		}		
		num++;
		total *= num;
		printf("%d=%d\n", num,total);
	}
	return 0;
}

int main_24242424() {
	int a = 1, sum = 0;
	for (;sum < 10;a *= 2) {
		sum += a;
	}
	printf("%d %d", a, sum);
	return 0;
}

int main_22121212121() {
	int a = 2020, b = 1;
	while (a < 2030) {
		b *= 2;
		a++;
	}
	printf("%d %d", a, b);
	return 0;
}

int main_2424241424() {
	int a = 20, b = 1;

	while (b) {
		if (a % 7 == 0) b = 0;
		a--;
	}
	printf("%d", a);
	return 0;
}

int main_23523523() {
	int a = 0, b = 0, sum;
	for (a=0; a>-20; a--);
	return 0;
}

int main_00_01_02_03_0282() {
	int N, num=0, M,bignum=0,manynum;
	scanf("%d", &N); // N 입력
	for (int i = 0; i < N; i++) { // 같은 행동 반복하니 반복문 사용
		scanf("%d", &M); // M입력
		printf("%d:", M); // 프린트 맞추기
		num = 0; // 각각 약수 개수 저장할 공간 매번 초기화 시키기
		for (int j = 1; j <= M; j++) {
			if (M % j == 0) { // 약수 찾기
				printf(" %d", j); // 약수 출력
				num++; // 약수 나왔으니 한개씩 더하기
			}
		}
		printf(" %d", num);
		if (num > bignum) {
			bignum = num;// 빅넘에 약수 갯수 저장
			manynum = M; // 누가 약수가 많은지 저장
		}
		printf("\n"); // 띄어쓰기 맞추기
	}
	printf("%d", manynum); //가장 많은 수 저장


	return 0;
}

int main_06_03_02_02() {
	int N, M, bignumofaliquo=0, bigsum=0,bignum=0;
	scanf("%d %d", &N, &M);
	for (int i = N; i <= M; i++) {
		int sum=0, numofaliquo = 1;
		for (int j = 2; j <= i; j++) {
			int num = i,count=0,primenum=0;
			for (int k = 2; k < j; k++) { // 소수를 판별해준다
				if (j % k == 0) primenum++; // 1이상이면 소수가 아님
			}
			while (num % j == 0 && primenum == 0) { // 소수가 아니거나, j로 나누었을때 0이 아니면 와일문 실행하지 않는다.
				
				num = num / j; // 숫자를 계속 나누어서 지수 세기 위함
				count++; // 지수 갯수 샌다.
			}
			if (count != 0) { //와일문을 실행하지 않아 카운터 0이면 실행x 
				numofaliquo *= (count + 1); // 약수의 갯수는 지수+1해서 곱하기
				sum += count; // 총 지수 갯수 
			}
		}
		if (numofaliquo > bignumofaliquo) { // 약수가 현재 1등인 것보다 많을시 전부 교체
			bignumofaliquo = numofaliquo; 
			bignum = i;
			bigsum = sum;
		}
	}
	printf("%d %d %d", bignum, bignumofaliquo, bigsum);
	return 0;
}

int main_06_03_02_01_03_04() {
	int num,prevnum, sumnegative = 1, sumpostive = 1,bigsumpostive=1, bigsumnegative=1;
	scanf("%d", &num); // 이전 숫자와 차이를 두기 위해 밖에다가 한번 입력 받음
	while (num) {
		prevnum = num; // 전에 받은 숫자는 이전 숫자에 넣음 
		scanf("%d", &num); // 새로운 숫자 받는다.
		if (num > 0 && prevnum > 0) sumpostive++; // 이전 숫자와 이번 숫자가 둘다 양수인 경우 포지티브 ++
		else if (num < 0 && prevnum <0) sumnegative++; // 둘다 음수인경우 네거티브 ++
		else if (num > 0 && prevnum < 0) { // 음수에서 양수로 바뀐 경우
			if (sumnegative > bigsumnegative) { // 이번 네거티브가 빅 네거티브보다 큰 경우
				bigsumnegative = sumnegative; // 빅 네거티브 최대값으로 바꾸기
			}
			sumnegative = 1; // 초기화 해줘서 건너 뛰어 있을경우 방지
		}
		else if (num < 0 && prevnum > 0) { // 양수에서 음수로 바뀐 경우
			if (sumpostive > bigsumpostive) { // 이것도 네거티브랑 똑같음
				bigsumpostive = sumpostive;
			}
			sumpostive = 1;
		}
	}
	if (sumnegative > bigsumnegative) { // 숫자가 바뀌지 않고 끝날 경우 방지
		bigsumnegative = sumnegative;
	}
	if (sumpostive > bigsumpostive) { // 위와 같은 이유
		bigsumpostive = sumpostive;
	}
	if (bigsumnegative > bigsumpostive) printf("%d", bigsumnegative);
	if (bigsumnegative < bigsumpostive) printf("%d", bigsumpostive);

	return 0;
}

int main_06_04_02() {
	int T,num,bigt=0,smallt=0,numt=0;
	scanf("%d", &T); // T입력받기
	while (1) {
		scanf("%d", &num); // 숫자 입력받기
		if (num == 0) break; // 0이면 끝낸다
		while (num> 0) { // 0될때까지 나누기 시작
			if (num % 10 > T) bigt++; // T보다 큰 경우
			else if (num % 10 < T)smallt++; // T보다 작은 경우
			else if (num % 10 == T) numt++; // T인경우
			num /= 10; // 한자리수 없애기
		}
	}
	printf("%d %d %d", numt, smallt, bigt);

	return 0;
}

int main_06_05_03() {
	int N, oddnum=0, evennum=0;
	scanf("%d", &N);
	while (N > 0) {
		if (N % 10 % 2 == 0) { // 마지막 자리가 짝수인 경우
			evennum = evennum * 10 + N % 10; // 마지막 자리를 더하기 위해 이전에 있던 수에 10을 곱해준다
		}
		else if (N % 10 % 2 != 0) { // 마지막 자리가 홀수인 경우
			oddnum = oddnum * 10 + N % 10; // 마지막 자리를 더하기 위해 이전에 있던 수에 10을 곱해준다
		}
		N /= 10; // 자리수 하나 없애기
	}
	printf("%d %d", evennum, oddnum);
	return 0;
}

int main_06_06_02() {
	int N;
	while (1) {
		scanf("%d", &N);
		if (N <= 1 || N % 3 == 0) break;
		for (int i = 0; i < N-1; i++) {
			for (int j = 0; j < N - i; j++) printf(" "); // 공백출력
			printf("X"); // X출력
			for (int j = 0; j < i * 2 - 1;j++) printf("O"); // O출력 2개씩 늘어나지만 2번째줄부터 1개 생기는것 생각
			if (i > 0) printf("X"); // 두번째 줄 부터 X가 두개인것 생각
			for (int j = 0; j < N - i; j++) printf(" "); // 공백출력
			printf("\n"); // 엔터 칠기
		}
		for (int i = 0; i < 2 * N - 1;i++) printf("X"); // 제일 밑에줄에 X있는 것
		printf("\n");
	}
	return 0;
}

int main_03_02_01_0202028318461() {
	double test1, test2, avetest;
	scanf("%lf %lf", &test1, &test2); // 입력
	avetest = (test1*40 + test2*60) / 100; // 평균
	if (avetest >= 85.5) printf("A"); // 구간별 학점
	else if (avetest >= 75.5) printf("B");
	else if (avetest >= 60)printf("C");
	else printf("F");
	if (avetest >= 60 || test2 >= 90) printf(" PASS"); // 90점 이상이거나 평균60점 이상
	else printf(" FAIL"); // 아무것도 아닌경우
	return 0;
}

int main_06_2_02_00001982() {
	char ch,resultsmall= 'a', resultbig= 'Z',count=0;
	scanf("%c", &ch);
	if (ch >= 'a' && ch <= 'z') { // 소문자로 시작한 경우
		while (ch != '0') {
			if (ch > resultsmall) resultsmall = ch; // 더 큰 소문자 찾기
			if (ch < resultbig) resultbig = ch, count++; // 대문자가 섞여있을 경우 카운트 늘려서 출력하기
			scanf("%c", &ch);
		}
		if (count > 0) printf("%c %c", resultsmall, resultbig); // 대문자 섞여있을 경우
		else  printf("%c", resultsmall);
	}
	else if (ch >= 'A' && ch <= 'Z') { // 대문자로 시작한경우
		while (ch != '0') {
			if (ch > resultsmall) resultsmall = ch, count++; // 소문자 섞여있을 경우
			if (ch < resultbig) resultbig = ch; // 더 작은 대문자 찾기
			scanf("%c", &ch);
		}
		if (count > 0) printf("%c %c", resultbig, resultsmall); // 소문자 섞여있어서 2개 출력
		else  printf("%c", resultbig);
	}
	return 0;
}

int main_06_1241274126187() {
	int bignum=0, smallnum=0, numnum=0, exnum=0;
	char ch;
	while (1) {
		scanf("%c", &ch);
		if (ch == '*') break;
		if (ch >= 'A' && ch <= 'Z') bignum++; // 대문자인경우
		else if (ch >= 'a' && ch <= 'z') smallnum++; // 소문자인경우
		else if (ch >= '0' && ch <= '9') numnum+=ch-48; // 숫자인경우
		else exnum++; //예외경우
	}
	printf("%d %d %d %d", bignum, smallnum, numnum, exnum);
	return 0;
}

int main_0987654_9876545678_98765() {
	int N, max=0,min,count=0, M = 0; // 와일문 안에 전부 넣었더니 최솟값이 애매해져버렸다..
	while (1) {
		int num3 = 0;
		scanf("%d", &N);
		if (N == 0) break; // 0일경우 와일문 끝
		M = N;
		while (N > 0) {
			if (N % 10 == 3) num3 = num3 + 2; // 하나의 3이 앞뒤로 2개의 3이므로 2를 더한다.
			M = M * 10 + N % 10; // 앞뒤로 이어 붙이는 작업
			N /= 10; // N줄여주기
		}
		printf("%d %d ", M, num3);
		if (count == 0) min = M; // 처음일경우 최소값 설정이 애매해서 이렇게 설정
		if (M > max) max = M; // 최대일 경우
		if (M < min)min = M; // 최소일경우
		count++;
	}
	printf("\n%d %d", min, max);
	return 0;
}

int main_235235235837463789213() {
	int N, max, min, lastnum,num,prevnum,count=1,maxcount = 0, isfaliquo, previsfaliquo;
	scanf("%d", &N);
	isfaliquo = 0;
	scanf("%d", &num);
	max = num;
	min = num;
	if (num < 2||num>=100) previsfaliquo = 1;
	if (num > 0) for (int j = 2; j < num; j++) {
		if (num % j == 0) previsfaliquo=1;// 소수가 아니게됨
	}
	if (isfaliquo != 0) previsfaliquo = 1; // 처음이니 이전으로 넘기기
	if (previsfaliquo == 0) { 
		maxcount = 1; 
		lastnum = num;
	}
	prevnum = num;
	for (int i = 0; i < N-1;i++) {
		isfaliquo = 0; 
		scanf("%d", &num);
		if (num < 2 || num>=100) isfaliquo = 1;
		if (num > 0) for (int j = 2; j < num; j++) {
			if (num % j == 0) isfaliquo=1;// 소수가 아니게됨
		}
		if (num > max) max = num;
		if (num < min) min = num;
		if (isfaliquo + previsfaliquo == 0) {//지금과 이전 모두 소수일 경우
			count++;
			if (count > maxcount) {
				maxcount = count;
				lastnum = num; // 최대 길이의 마지막 값이 라스트 넘이므로 이렇게 한다.
			}//최대 카운트값 바꿔주기
		}
		else if (isfaliquo == 0 && previsfaliquo == 1) {//지금은 소수, 이전은 소수 아닌경우
			count=1;
			if (count > maxcount) {
				maxcount = count;
				lastnum = num; // 최대 길이의 마지막 값이 라스트 넘이므로 이렇게 한다.
			}//최대 카운트값 바꿔주기
		}
		else if (isfaliquo > 0 && previsfaliquo == 0) { // 지금은 소수가 아니고, 이전은 소수인경우
			count = 1;
		}
		prevnum = num;
		previsfaliquo = isfaliquo;
	}
	if (maxcount == 0) printf("0");
	else {
		printf("%d\n%d\n%d %d", maxcount, lastnum, max, min);
	}
	return 0;
}	


int main() {
	char a = 'A';
	a = a - 'A';
	if (a ==0)printf("%d %c", a, a);
	return 0;
}
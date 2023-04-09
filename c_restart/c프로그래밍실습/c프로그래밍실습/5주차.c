#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main_05_00_07() {
	int N, num;
	scanf("%d", &N);
	scanf("%d", &num);
	if (num == N) printf("RIGHT");
	else if (num > N) {
		printf("DOWN");
		scanf("%d", &num);
		if (num == N) printf("RIGHT");
		else if (num > N) printf("DOWN");
		else printf("UP");
	}
	else {
		printf("UP");
		scanf("%d", &num);
		if (num == N) printf("RIGHT");
		else if (num > N) printf("DOWN");
		else printf("UP");
	}
	return 0;
}

int main_05_00_08() {
	int N;
	scanf("%d", &N);
	if (N % 4 != 0) printf("common year");
	if (N % 4 == 0 && N % 100 != 0) printf("leap year");
	if (N % 4 == 0 && N % 100 == 0 && N % 400 != 0) printf("common year");
	if (N % 4 == 0 && N % 100 == 0 && N % 400 == 0)printf("leap year");
	return 0;
}

int main_05_00_09() {
	int year, month, date, year0, month0, date0;
	char a;
	scanf("%d %c %d %c %d", &year, &a, &month, &a, &date);
	scanf("%d %c %d %c %d", &year0, &a, &month0, &a, &date0);
	if (year > year0) printf("%04d/%02d/%02d", year0, month0, date0);
	else if (year < year0) printf("%04d/%02d/%02d", year, month, date);
	else if (month > month0) printf("%04d/%02d/%02d", year0, month0, date0);
	else if (month < month0) printf("%04d/%02d/%02d", year, month, date);
	else if (date > date0) printf("%04d/%02d/%02d", year0, month0, date0);
	else if (date < date0) printf("%04d/%02d/%02d", year, month, date);
	else printf("%d/%02d/%02d*", year, month, date);
	
	return 0;
}

int main_05_00_10() {
	double ko, en, ma, ev;
	scanf("%lf %lf %lf", &ko, &en, &ma);
	ev = (ko + ma + en)/3;
	if (ev >= 91.5) printf("A");
	else if (ev >= 85.5) printf("B");
	else if (ev >= 80.5) printf("C");
	else printf("F");
	if (ko == 100 || ma == 100 || en == 100) printf("Good");
	if (ko < 60 || ma < 60 || en < 60) printf("Bad");

	return 0;
}

int main_05_00_11() {
	int ans[3], num[3],s=0,b=0;
	for (int i = 0; i < 3; i++) scanf("%d", &ans[i]);
	for (int i = 0; i < 3; i++) scanf("%d", &num[i]);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == j) {
				if (ans[i] == num[i]) {
					s++;
				}
			}
			else {
				if (ans[i] == num[j]) {
					b++;
				}
			}
		}
	}
	printf("%dS%dB", s, b);

	return 0;
}

int main_05_00_12() {
	int num, bill;
	scanf("%d %d", &num, &bill);
	if (num == 1) {
		bill -= 500;
		printf("Americano\n");
		printf("%d %d", bill / 500, bill % 500 / 100);
	}
	if (num == 2) {
		bill -= 400;
		printf("Cafe Latte\n");
		printf("%d %d", bill / 500, bill % 500 / 100);
	}
	if (num == 3) {
		bill -= 300;
		printf("Lemon Tea\n");
		printf("%d %d", bill / 500, bill % 500 / 100);
	}
	return 0;
}

int main_05_01_12() {
	int num, bill;
	scanf("%d %d", &num, &bill);
	switch (num) {
		case 1:
			bill -= 500;
			printf("Americano\n");
			printf("%d %d", bill / 500, bill % 500 / 100);
			break;
		case 2:

			bill -= 400;
			printf("Cafe Latte\n");
			printf("%d %d", bill / 500, bill % 500 / 100);
			break;
		case 3:

			bill -= 300;
			printf("Lemon Tea\n");
			printf("%d %d", bill / 500, bill % 500 / 100);
	}
	return 0;
}

int main_05_01_13() {
	double ko, en, ma, ev;
	char grade;
	scanf("%lf %lf %lf", &ko, &en, &ma);
	ev = (ko + ma + en) / 3;
	printf("%.2f\n", ev);
	if (ev >= 75) grade = 'A';
	else if (ev >= 50) grade ='B';
	else grade = 'F';
	switch (grade) {
	case 'A':
		printf("A");
		break;
	case 'B':
		printf("B");
		break;
	case 'F':
		printf("F");
	}

	return 0;
}

int main_06_00_01() {
	int N,i=1;
	scanf("%d", &N);
	while (i<=N) {
		if (N % i == 0) printf("%d ", i);
		i++;
	}


	return 0;
}

int main_06_00_02() {
	int num, result=0;
	while (1) {
		scanf("%d", &num);
		result += num;
		if (num == 0) break;
	}
	printf("%d", result);
	return 0;
}

int main_06_00_03() {
	int ans, num, i = 0;
	scanf("%d", &ans);
	do {
		scanf("%d", &num);
		if (num > ans) printf("%d>?", num);
		else if (num < ans) printf("%d<?", num);
		else printf("%d==?", num);
		i++;
	} while (num != ans);
	printf("%d", i);
	return 0;
}

int main_06_00_04() {
	int N, M,i=1,ans;
	scanf("%d %d", &N, &M);
	while (i < N || i < M) {
		if (N % i == 0 && M % i == 0) ans = i;
		i++;
	}
	printf("%d", ans);
	return 0;
}

int main_06_05_01() {
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j <= i; j++) printf("*");
		printf("\n");
	}

	return 0;
}

int main_02_01_01() {
	int ko, en, ma;
	double ev;
	
	scanf("%d %d %d", &ko, &en, &ma);
	ev = (ko + ma + en) / 3.0;
	if (ev >= 90) printf("A"); // 평균이 몇점 이상일 경우 학점 나누기
	else if (ev >= 80) printf("B"); // B
	else if (ev >= 70) printf("C"); // C
	else if (ev >= 60) printf("D"); // D
	else printf("F"); // 60미만이면 F학점
	printf("\n"); // 위에 전부 줄 넘김을 안해줘서 넣어줬음
	if (ko > en && ko > ma) printf("max: %d\n", ko); // kr가 최대일 경우
	else if (en > ko && en > ma) printf("max: %d\n", en); // en이 최대일 경우
	else printf("max: %d\n", ma); // ma가 최대일경우
	if (ko < en && ko < ma) printf("min: %d\n", ko); // ko가 최소일 경우
	else if (en < ko && en < ma) printf("min: %d\n", en); // en이 최소일경우
	else printf("min: %d\n", ma); // ma가 최소일경우

	return 0;
}

int main_02_01_02() {
	int num1, num2, num3, total = 0;
	scanf("%d %d %d", &num1, &num2, &num3); // 입력받기 
	if (num1 == 1) {  // 입력받은 순서대로 출력 및 총 가격 입력받기
		printf("Pizza\n"); // 1은 피자
		total += 15000; // 가격
	}
	if (num1 == 2) {
		printf("Burger\n"); // 2는 버거
		total += 5000; // 가격
	}
	if (num1 == 3) {
		printf("Salad\n"); // 3은 샐러드
		total += 4500; // 가격
	}
	if (num1 == 4) {
		printf("Ice cream\n"); // 4는 아이스크림
		total += 800; // 가격
	}
	if (num1 == 5) {
		printf("Beverge\n"); //5눈 음료
		total += 500; // 가격
	}
	if (num1 == 0) printf("None\n");
	if (num2 == 1) {  // 두번째로 입력받은 음식
		printf("Pizza\n");// 중복입력 허용받으므로 한번 더 똑같이함
		total += 15000; // 포문 쓰는게 좀 더 깔끔해 보였을 것 같다.
	}
	if (num2 == 2) {
		printf("Burger\n");//2는 버거
		total += 5000; // 버거 가격 더하기
	}
	if (num2 == 3) {
		printf("Salad\n"); // 3은 샐러드
		total += 4500; // 총 가격에 더하기
	}
	if (num2 == 4) {
		printf("Ice cream\n"); // 아이스크림
		total += 800; // 총가격에 더하기
	}
	if (num2 == 5) {
		printf("Beverge\n"); // 음료
		total += 500; // 토탈에 더하기
	}
	if (num2 == 0) printf("None\n"); // 아무것도 아닌 경우
	if (num3 == 1) { // 3번째로 입력받은 음식
		printf("Pizza\n"); // 마지막 피자
		total += 15000; // 총가격에 더하기
	}
	if (num3 == 2) {
		printf("Burger\n"); // 버거
		total += 5000; // 토탈 가격에 더하기
	}
	if (num3 == 3) { 
		printf("Salad\n"); // 샐러드
		total += 4500; // 총가격에 더하기
	}
	if (num3 == 4) {
		printf("Ice cream\n");// 4는 아이스크림
		total += 800; // 총가격에 더하기
	}
	if (num3 == 5) {
		printf("Beverage\n"); // 음료
		total += 500; // 마지막 가격 더하기
	}
	if (num3 == 0) printf("None\n"); // 아무것도 없을경우
	printf("Total:%dwon", total);
	//Pizza 15, 000원, 2. Burger 5, 000원, 3. Salad 4, 500원, 4. Ice cream 800원, 5. Beverage 500원
	return 0;
}

int main_02_01_03() {
	int num, lange;
	char word;
	scanf("%c", &word); // 문자 입력
	scanf("%d", &num); // 건너 뛸 숫자 입력
	if ((word >= 'a' && word <= 'z') || (word >= 'A' && word <= 'Z')) { // 입력 받은 문자가 알파벳인지
		if (word >= 'a' && word <= 'z') lange = 'a'; // 대문자인지 소문자 인지 나누기
		else lange = 'A';
		word = (word + num - lange) % 26 + lange; // 넘어가는 경우가 있으면 다시 되돌려와서 a부터 더하기
		printf("%c", word); // 더해서 출력
	}
	else printf("%c", word); // 알파벳 아니면 그냥 출력
	return 0;
}

int main_02_00_04() {
	int num;
	//scanf("%d", &num);//입력
	num = 0;
	while (num < 101) {
		num++;
		printf("\n");
		if (num < 10 || num>99) printf("none"); // 10의자리 숫자 읽어주기
		else if (num >= 90) printf("ninety"); // 90~ 99
		else if (num >= 80) printf("eighty"); // 80 ~ 89
		else if (num >= 70) printf("seventy"); // 70 ~ 79
		else if (num >= 60) printf("sixty"); // 60 ~ 69
		else if (num >= 50) printf("fifty"); // 50 ~ 59
		else if (num >= 40) printf("forty"); // 40 ~ 49
		else if (num >= 30) printf("thirty"); // 30 ~ 39
		else if (num >= 20) printf("twenty"); // 20 ~ 29

		if (num >= 20 && num < 100) { // 1의자리 숫자 읽어주기
			if (num % 10 == 1) printf("-one");// _1
			if (num % 10 == 2) printf("-two"); // _2
			if (num % 10 == 3) printf("-three"); // _3
			if (num % 10 == 4) printf("-four"); // _4
			if (num % 10 == 5) printf("-five"); // _5
			if (num % 10 == 6) printf("-six"); // _6
			if (num % 10 == 7) printf("-seven"); // _7
			if (num % 10 == 8) printf("-eight"); //_8
			if (num % 10 == 9) printf("-nine"); // _9
		}
		switch (num) { //11 ~ 19는 방식이 달라서 나눠주기
		case 10:
			printf("ten"); //10
			break;
		case 11:
			printf("eleven");//11
			break;
		case 12:
			printf("twelve"); // 12
			break;
		case 13:
			printf("thirteen"); //13
			break;
		case 14:
			printf("fourteen");//14
			break;
		case 15:
			printf("fifteen"); //15
			break;
		case 16:
			printf("sixteen");// 16
			break;
		case 17:
			printf("seventeen"); //17
			break;
		case 18:
			printf("eighteen");//18
			break;
		case 19:
			printf("nineteen");//19
			break;

		}
	}
	return 0;
}

int main_02_00_05() {
	int N;
	scanf("%d", &N);
	if (N == 10000 || N == 10100 || N == 10200) printf("Seoul"); // 100 ~ 102인경우 서울
	else if (N == 10300 || N == 10400)printf("Busan"); // 103,104인경우 부산
	else if (N == 10500)printf("Gwangju"); // 105인경우 광주
	else printf("none"); // 예외값은 전부 논
	return 0;
}

int main_02_02_02_20_0202020202() {
	int num1, num2, num3,result=0;
	scanf("%d %d %d", &num1, &num2, &num3); // 숫자 입력
	if (num1 + num2 == num3) printf("+\n"), result++; // 더하는 경우 중복도 허용하므로 else if 사용하지 않음
	if (num1 - num2 == num3) printf("-\n"), result++; // 빼는경후
	if (num1 * num2 == num3) printf("*\n"), result++; // 곱하는경우
	if (num1 / num2 == num3) printf("/\n"), result++; // 나누는 경우
	if (result == 0) printf("Incorrect"); // 연산이 아닌경우 result 는 0이므로 출력
	return 0;
}
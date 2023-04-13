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
	scanf("%d", &N); // N �Է�
	for (int i = 0; i < N; i++) { // ���� �ൿ �ݺ��ϴ� �ݺ��� ���
		scanf("%d", &M); // M�Է�
		printf("%d:", M); // ����Ʈ ���߱�
		num = 0; // ���� ��� ���� ������ ���� �Ź� �ʱ�ȭ ��Ű��
		for (int j = 1; j <= M; j++) {
			if (M % j == 0) { // ��� ã��
				printf(" %d", j); // ��� ���
				num++; // ��� �������� �Ѱ��� ���ϱ�
			}
		}
		printf(" %d", num);
		if (num > bignum) {
			bignum = num;// ��ѿ� ��� ���� ����
			manynum = M; // ���� ����� ������ ����
		}
		printf("\n"); // ���� ���߱�
	}
	printf("%d", manynum); //���� ���� �� ����


	return 0;
}

int main_06_03_02_02() {
	int N, M, bignumofaliquo=0, bigsum=0,bignum=0;
	scanf("%d %d", &N, &M);
	for (int i = N; i <= M; i++) {
		int sum=0, numofaliquo = 1;
		for (int j = 2; j <= i; j++) {
			int num = i,count=0,primenum=0;
			for (int k = 2; k < j; k++) { // �Ҽ��� �Ǻ����ش�
				if (j % k == 0) primenum++; // 1�̻��̸� �Ҽ��� �ƴ�
			}
			while (num % j == 0 && primenum == 0) { // �Ҽ��� �ƴϰų�, j�� ���������� 0�� �ƴϸ� ���Ϲ� �������� �ʴ´�.
				
				num = num / j; // ���ڸ� ��� ����� ���� ���� ����
				count++; // ���� ���� ����.
			}
			if (count != 0) { //���Ϲ��� �������� �ʾ� ī���� 0�̸� ����x 
				numofaliquo *= (count + 1); // ����� ������ ����+1�ؼ� ���ϱ�
				sum += count; // �� ���� ���� 
			}
		}
		if (numofaliquo > bignumofaliquo) { // ����� ���� 1���� �ͺ��� ������ ���� ��ü
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
	scanf("%d", &num); // ���� ���ڿ� ���̸� �α� ���� �ۿ��ٰ� �ѹ� �Է� ����
	while (num) {
		prevnum = num; // ���� ���� ���ڴ� ���� ���ڿ� ���� 
		scanf("%d", &num); // ���ο� ���� �޴´�.
		if (num > 0 && prevnum > 0) sumpostive++; // ���� ���ڿ� �̹� ���ڰ� �Ѵ� ����� ��� ����Ƽ�� ++
		else if (num < 0 && prevnum <0) sumnegative++; // �Ѵ� �����ΰ�� �װ�Ƽ�� ++
		else if (num > 0 && prevnum < 0) { // �������� ����� �ٲ� ���
			if (sumnegative > bigsumnegative) { // �̹� �װ�Ƽ�갡 �� �װ�Ƽ�꺸�� ū ���
				bigsumnegative = sumnegative; // �� �װ�Ƽ�� �ִ밪���� �ٲٱ�
			}
			sumnegative = 1; // �ʱ�ȭ ���༭ �ǳ� �پ� ������� ����
		}
		else if (num < 0 && prevnum > 0) { // ������� ������ �ٲ� ���
			if (sumpostive > bigsumpostive) { // �̰͵� �װ�Ƽ��� �Ȱ���
				bigsumpostive = sumpostive;
			}
			sumpostive = 1;
		}
	}
	if (sumnegative > bigsumnegative) { // ���ڰ� �ٲ��� �ʰ� ���� ��� ����
		bigsumnegative = sumnegative;
	}
	if (sumpostive > bigsumpostive) { // ���� ���� ����
		bigsumpostive = sumpostive;
	}
	if (bigsumnegative > bigsumpostive) printf("%d", bigsumnegative);
	if (bigsumnegative < bigsumpostive) printf("%d", bigsumpostive);

	return 0;
}

int main_06_04_02() {
	int T,num,bigt=0,smallt=0,numt=0;
	scanf("%d", &T); // T�Է¹ޱ�
	while (1) {
		scanf("%d", &num); // ���� �Է¹ޱ�
		if (num == 0) break; // 0�̸� ������
		while (num> 0) { // 0�ɶ����� ������ ����
			if (num % 10 > T) bigt++; // T���� ū ���
			else if (num % 10 < T)smallt++; // T���� ���� ���
			else if (num % 10 == T) numt++; // T�ΰ��
			num /= 10; // ���ڸ��� ���ֱ�
		}
	}
	printf("%d %d %d", numt, smallt, bigt);

	return 0;
}

int main_06_05_03() {
	int N, oddnum=0, evennum=0;
	scanf("%d", &N);
	while (N > 0) {
		if (N % 10 % 2 == 0) { // ������ �ڸ��� ¦���� ���
			evennum = evennum * 10 + N % 10; // ������ �ڸ��� ���ϱ� ���� ������ �ִ� ���� 10�� �����ش�
		}
		else if (N % 10 % 2 != 0) { // ������ �ڸ��� Ȧ���� ���
			oddnum = oddnum * 10 + N % 10; // ������ �ڸ��� ���ϱ� ���� ������ �ִ� ���� 10�� �����ش�
		}
		N /= 10; // �ڸ��� �ϳ� ���ֱ�
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
			for (int j = 0; j < N - i; j++) printf(" "); // �������
			printf("X"); // X���
			for (int j = 0; j < i * 2 - 1;j++) printf("O"); // O��� 2���� �þ���� 2��°�ٺ��� 1�� ����°� ����
			if (i > 0) printf("X"); // �ι�° �� ���� X�� �ΰ��ΰ� ����
			for (int j = 0; j < N - i; j++) printf(" "); // �������
			printf("\n"); // ���� ĥ��
		}
		for (int i = 0; i < 2 * N - 1;i++) printf("X"); // ���� �ؿ��ٿ� X�ִ� ��
		printf("\n");
	}
	return 0;
}

int main_03_02_01_0202028318461() {
	double test1, test2, avetest;
	scanf("%lf %lf", &test1, &test2); // �Է�
	avetest = (test1*40 + test2*60) / 100; // ���
	if (avetest >= 85.5) printf("A"); // ������ ����
	else if (avetest >= 75.5) printf("B");
	else if (avetest >= 60)printf("C");
	else printf("F");
	if (avetest >= 60 || test2 >= 90) printf(" PASS"); // 90�� �̻��̰ų� ���60�� �̻�
	else printf(" FAIL"); // �ƹ��͵� �ƴѰ��
	return 0;
}

int main_06_2_02_00001982() {
	char ch,resultsmall= 'a', resultbig= 'Z',count=0;
	scanf("%c", &ch);
	if (ch >= 'a' && ch <= 'z') { // �ҹ��ڷ� ������ ���
		while (ch != '0') {
			if (ch > resultsmall) resultsmall = ch; // �� ū �ҹ��� ã��
			if (ch < resultbig) resultbig = ch, count++; // �빮�ڰ� �������� ��� ī��Ʈ �÷��� ����ϱ�
			scanf("%c", &ch);
		}
		if (count > 0) printf("%c %c", resultsmall, resultbig); // �빮�� �������� ���
		else  printf("%c", resultsmall);
	}
	else if (ch >= 'A' && ch <= 'Z') { // �빮�ڷ� �����Ѱ��
		while (ch != '0') {
			if (ch > resultsmall) resultsmall = ch, count++; // �ҹ��� �������� ���
			if (ch < resultbig) resultbig = ch; // �� ���� �빮�� ã��
			scanf("%c", &ch);
		}
		if (count > 0) printf("%c %c", resultbig, resultsmall); // �ҹ��� �����־ 2�� ���
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
		if (ch >= 'A' && ch <= 'Z') bignum++; // �빮���ΰ��
		else if (ch >= 'a' && ch <= 'z') smallnum++; // �ҹ����ΰ��
		else if (ch >= '0' && ch <= '9') numnum+=ch-48; // �����ΰ��
		else exnum++; //���ܰ��
	}
	printf("%d %d %d %d", bignum, smallnum, numnum, exnum);
	return 0;
}

int main_0987654_9876545678_98765() {
	int N, max=0,min,count=0, M = 0; // ���Ϲ� �ȿ� ���� �־����� �ּڰ��� �ָ��������ȴ�..
	while (1) {
		int num3 = 0;
		scanf("%d", &N);
		if (N == 0) break; // 0�ϰ�� ���Ϲ� ��
		M = N;
		while (N > 0) {
			if (N % 10 == 3) num3 = num3 + 2; // �ϳ��� 3�� �յڷ� 2���� 3�̹Ƿ� 2�� ���Ѵ�.
			M = M * 10 + N % 10; // �յڷ� �̾� ���̴� �۾�
			N /= 10; // N�ٿ��ֱ�
		}
		printf("%d %d ", M, num3);
		if (count == 0) min = M; // ó���ϰ�� �ּҰ� ������ �ָ��ؼ� �̷��� ����
		if (M > max) max = M; // �ִ��� ���
		if (M < min)min = M; // �ּ��ϰ��
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
		if (num % j == 0) previsfaliquo=1;// �Ҽ��� �ƴϰԵ�
	}
	if (isfaliquo != 0) previsfaliquo = 1; // ó���̴� �������� �ѱ��
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
			if (num % j == 0) isfaliquo=1;// �Ҽ��� �ƴϰԵ�
		}
		if (num > max) max = num;
		if (num < min) min = num;
		if (isfaliquo + previsfaliquo == 0) {//���ݰ� ���� ��� �Ҽ��� ���
			count++;
			if (count > maxcount) {
				maxcount = count;
				lastnum = num; // �ִ� ������ ������ ���� ��Ʈ ���̹Ƿ� �̷��� �Ѵ�.
			}//�ִ� ī��Ʈ�� �ٲ��ֱ�
		}
		else if (isfaliquo == 0 && previsfaliquo == 1) {//������ �Ҽ�, ������ �Ҽ� �ƴѰ��
			count=1;
			if (count > maxcount) {
				maxcount = count;
				lastnum = num; // �ִ� ������ ������ ���� ��Ʈ ���̹Ƿ� �̷��� �Ѵ�.
			}//�ִ� ī��Ʈ�� �ٲ��ֱ�
		}
		else if (isfaliquo > 0 && previsfaliquo == 0) { // ������ �Ҽ��� �ƴϰ�, ������ �Ҽ��ΰ��
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
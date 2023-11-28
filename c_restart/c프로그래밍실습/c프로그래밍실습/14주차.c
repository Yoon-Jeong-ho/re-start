#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
// #include<string.h>
#include<time.h>
/*
strlen() : 길이
strcpy(a,b) : a에 b를 복사
strcat(a,b) : a 뒤에 b를 붙임
strcmp(a,b) : s1의 순위
b = atoi,l,f(a): 숫자 형에 따른 문자를 숫자로 변환
*/
typedef struct member {
	char name[21], phone[16],birth[9];
}member;
void printMainMenu();
void insertMember(member* , int *);
void sortMember(member*, int, int);
void swapMember(member*);
void printMember(member*, int);
void deleteMember(member*, int*);
void findMemberByBirth(member*, int);
int main() {
	int n = 0, sum = 0, command, num = 0;
	double avg;
	char a[100][100];
	member mem[100];
	while (1) {
		printMainMenu();
		scanf("%d", &command); getchar();
		if (command == 5)break;
		else if (command == 1) {
			insertMember(mem, &num);
		}
		else if (command == 2) {
			printMember(mem, num);

		}
		else if (command == 3) {
			deleteMember(mem, &num);

		}
		else if (command == 4) {
			findMemberByBirth(mem, num);
		}
	}
}

void printMainMenu() {
	printf("*****Menu*****\n");
	printf("<1.Registration><2.ShowAll><3.Delete><4.FindByBirth><5.Exit>\n");
	printf("Enter_the_menu_number:");
}
void insertMember(member* mem, int* n) {
	if (*n >= 100) {
		printf("OVERFLOW\n");
		return;
	}
	printf("Name:"); // 고정
	scanf("%s", mem[*n].name); getchar();
	printf("Phone_number:"); // 고정
	scanf("%s", mem[*n].phone); getchar();
	printf("Birth:"); //고정
	scanf("%s", mem[*n].birth); getchar();

	*n = *n + 1;
	for (int i = *n-2; i >=0; i--) {
		if (strcmp(mem[i].name, mem[i + 1].name) > 0) sortMember(mem,i,i + 1);
	}
	printf("<<%d>>\n", *n);
}
void sortMember(member* mem, int n, int m) {
	member tmp;
	tmp = mem[n];
	mem[n] = mem[m];
	mem[m] = tmp;
}
void printMember(member*mem, int n) {
	for (int i = 0; i < n; i++) printf("%s %s %s\n", mem[i].name, mem[i].phone, mem[i].birth);

}
void deleteMember(member* mem, int* n) {
	char name[22];
	int m=-1;
	if (*n == 0) {
		printf("NO MEMBER\n");
		return;
	}
	printf("Name:"); // 고정
	scanf("%s", name); getchar();
	for (int i = 0; i < *n; i++) {
		if (strcmp(mem[i].name, name) == 0) m = i;
	}
	if (m == -1) printf("NO MEMBER\n");
	else {
		if (m == *n - 1) {
			*n = *n - 1;

		}
		else {
			for (int i = m; i < *n-1; i++)sortMember(mem, i, i + 1);
			*n = *n - 1;

		}
	}

}

void findMemberByBirth(member* mem, int n) {
	printf("Birth:"); // 고정
	int m, a;
	scanf("%d", &m); getchar();
	for (int i = 0; i < n; i++) {
		a = (mem[i].birth[4] - '0') * 10 + mem[i].birth[5] - '0';
		if (a == m)printf("%s %s %s\n",mem[i].name, mem[i].phone,mem[i].birth);
	}
	
}

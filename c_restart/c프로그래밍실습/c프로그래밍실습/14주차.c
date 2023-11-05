#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
/*
strlen() : ����
strcpy(a,b) : a�� b�� ����
strcat(a,b) : a �ڿ� b�� ����
strcmp(a,b) : s1�� ����
b = atoi,l,f(a): ���� ���� ���� ���ڸ� ���ڷ� ��ȯ
*/
struct student {
	char* name; // �̸� ����
	int firstStage; // 1�ܰ� ���� ����
	int interview; // ���� ���� ����
	double sum; // ���� ����
};
int main() {
	int n, m,num=0;
	struct student* st, tmpst;
	char tmp[100];
	scanf("%d %d", &n, &m); getchar(); // �Է�
	st = (struct student*)malloc(sizeof(struct student) * n); // �����Ҵ�
	if (st == NULL) return -1; // ���� Ȯ��
	for (int i = 0; i < n; i++) { // �Է¹ޱ�
		scanf("%s %d %d",tmp,&st[i].firstStage,&st[i].interview); getchar(); // �Է�
		st[i].name = (char*)malloc(sizeof(char) * (strlen(tmp) + 1)); // �����Ҵ�
		strcpy(st[i].name, tmp); // �Ҵ� ���� Ȯ��
		st[i].sum = st[i].firstStage * 7 + st[i].interview * 3; // ���ϱ�
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (st[i].sum < st[j].sum || (st[i].sum == st[j].sum && st[i].firstStage < st[j].firstStage) || (st[i].sum == st[j].sum && st[i].firstStage == st[j].firstStage && strcmp(st[i].name, st[j].name) > 0)) { // ����Ȯ��
				tmpst = st[i];// ���ǿ� ������ �ٲٱ�
				st[i] = st[j];
				st[j] = tmpst;
			}
		}
	}
	for (int i = 0; i < m; i++) {// m���� ����ϱ�
		printf("%s %d %d %.1f\n", st[i].name, st[i].firstStage, st[i].interview, st[i].sum/10);
		num++; // �������� ����� ���� �ø���
		while (i<n-1 && st[i].sum == st[i + 1].sum && st[i].firstStage == st[i + 1].firstStage) {
			i++;// ���� �հ� ù��° ������ ���� ����� ����ϴ� ��
			printf("%s %d %d %.1f\n", st[i].name, st[i].firstStage, st[i].interview, st[i].sum / 10);
			num++;
		}
	}
	printf("%d", num);
	for (int i = 0; i < n; i++) {
		free(st[i].name);//�̸� �Ҵ� ����
	}
	free(st); // ������ �Ҵ� ����
	return 0;
}
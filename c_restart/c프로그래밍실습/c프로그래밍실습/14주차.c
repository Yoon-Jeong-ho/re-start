#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main() {
	int t = 0, c = 0, r = 0;;
	char a[2][255], b[255][255], tmp[255], d[255][255];
	gets(a[0]); // ù��° ���ڿ� �Է¹ޱ�
	gets(a[1]); // �ܾ� �Է¹ޱ�
	for (int i = 0; i < strlen(a[0]); i++) { // �Է¹��� ���ڿ� �ܾ� ������ ������ b�� �����ϱ�
		if (a[0][i] == ' ') { // ������ ��� ���� �ܾ�
			b[t][c] =0;
			t++;
			c = 0;
		}
		else b[t][c++] = a[0][i];
	}
	b[t][c] = 0; // �������� �������� ������ֱ�
	c = 0;
	for (int i = 0; i < strlen(a[1]); i++) { // �Է¹��� ���ڿ� �ܾ� ������ ������ d�� �����ϱ�
		if (a[1][i] == ' ') { // ������ ��� ���� �ܾ�
			d[r][c] = 0;
			r++;
			c = 0;
		}
		else d[r][c++] = a[1][i];
	}
	d[r][c] = 0; // �������� �������� ������ֱ�
	c = 0;
	for (int i = 1; i <= t; i++) {//���� �� ã�� ���� ���� ����
		for (int j = 0; j < i; j++) { // �̰� ������ �ٲ��.
			if (strcmp(b[i], b[j]) == 0) //�������
				strcpy(b[i], d[c++]);//���� ���� d�� ���� c�� �ø��鼭 �ٲ۴�.
		}
	}
	strcpy(tmp, b[0]); // ù��°�� �����ؼ� ��������
	for (int i = 1; i <= t; i++) { // ���̱�
		strcat(tmp, b[i]);


	}
	printf("%s", tmp);// ���
	return 0;
}
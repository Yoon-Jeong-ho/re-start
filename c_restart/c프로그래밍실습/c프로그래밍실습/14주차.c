#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int main() {
	int t = 0, c = 0, r = 0;;
	char a[2][255], b[255][255], tmp[255], d[255][255];
	gets(a[0]); // 첫번째 문자열 입력받기
	gets(a[1]); // 단어 입력받기
	for (int i = 0; i < strlen(a[0]); i++) { // 입력받은 문자열 단어 단위로 나눠서 b에 저장하기
		if (a[0][i] == ' ') { // 공백일 경우 다음 단어
			b[t][c] =0;
			t++;
			c = 0;
		}
		else b[t][c++] = a[0][i];
	}
	b[t][c] = 0; // 마지막은 공백으로 만들어주기
	c = 0;
	for (int i = 0; i < strlen(a[1]); i++) { // 입력받은 문자열 단어 단위로 나눠서 d에 저장하기
		if (a[1][i] == ' ') { // 공백일 경우 다음 단어
			d[r][c] = 0;
			r++;
			c = 0;
		}
		else d[r][c++] = a[1][i];
	}
	d[r][c] = 0; // 마지막은 공백으로 만들어주기
	c = 0;
	for (int i = 1; i <= t; i++) {//같은 것 찾기 위한 시작 기준
		for (int j = 0; j < i; j++) { // 이게 같으면 바뀐다.
			if (strcmp(b[i], b[j]) == 0) //같을경우
				strcpy(b[i], d[c++]);//같은 곳에 d가 들어가고 c를 올리면서 바꾼다.
		}
	}
	strcpy(tmp, b[0]); // 첫번째만 복사해서 가져오기
	for (int i = 1; i <= t; i++) { // 붙이기
		strcat(tmp, b[i]);


	}
	printf("%s", tmp);// 출력
	return 0;
}
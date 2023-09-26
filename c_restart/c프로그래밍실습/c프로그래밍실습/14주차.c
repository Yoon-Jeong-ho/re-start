#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
int main() {
	char c[101],d[100][100],e[100], f[100][100],resultc[100];
	int n,a=0,b=0,i=0,result = 0,x,y;
	scanf("%d %d", &x, &y);
	getchar();
	gets_s(c, 100, stdin);
	gets_s(e, 100, stdin);
	while (c[i] != '\0') {
		if (c[i] == ' ') { d[a][b] = '\0'; a++; b = 0; }
		else d[a][b++] = c[i];
		i++;
	}
	d[a][b] = '\0';
	a = 0; b = 0; i = 0;
	while (e[i] != '\0') {
		if (e[i] == ' ') { f[a][b] = '\0'; a++; b = 0; }
		else f[a][b++] = e[i];
		i++;
	}
	f[a][b] = '\0';
	if (strcmp(d[x], f[y]) <= 0) {
		strcpy(resultc, d[x]);
		resultc[strlen(d[x])] = '\0';
		strcat(resultc, f[y]);
	}
	else {
		strcpy(resultc, f[y]);
		resultc[strlen(f[y])] = '\0';
		strcat(resultc, d[x]);
	}

	printf("%s", resultc);
}
# 1 - 2번
> #define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
int input(int* p);  
int* sel_next(int* p);  
int number(int* p, int* q);  
int main() {  
	int p[1000], * prev = NULL,n,*q,result;  
	n = input(p);  
	q = p;  
	prev = p;  
	while (prev < p + n) {  
		q=sel_next(q);  
		result = number(prev, q);  
		printf("%d*\n", result);  
		prev = q;  
	}  
	return 0;  
}  
int input(int* p) {  
	int result = 0;  
	while (1) {  
		scanf("%d", p);  
		if (*p == -1) break;  
		p++;  
		result++;  
	}  
	return result;  
}  
int* sel_next(int* p) {  
	int* q = p;    
	while (*q != -1 || *q != *p) {  
		q++;  
		if (*q == -1) break;  
		if (*q == *p) break;  
	}  
	q++;  
	return q;   
}  
int number(int* p, int* q) {  
	int result = 0;  
	for (p; p < q; p++) {  
		if (*p == -1) break;  
		result *= 10;    
		result += *p;  
	}  
	return result;  
}  
# 2 - 2 번
> #define _CRT_SECURE_NO_WARNINGS  
#include<stdio.h>  
#include<stdlib.h>  
#include<string.h>  
int main() {  
	char a[10000], b[22][100], c[100000],longc[1000],shortc[1000],hapc[1000],tmp[10000];   
	gets(a);  
	int q = 0, r = 0,e=0,t=0,max=0,min=99999,count=0;  
	for (int i = 0; i < strlen(a); i++) {    
		if (a[i] == ' ') {  
			b[q][r] = '\0';  
			q++; r = 0;   
		}  
		else b[q][r++] = a[i];    
	}  
	b[q][r] = '\0';  
	for (int i = 0; i <= q; i++) {  
		if (strlen(b[i]) > max) {  
			max = strlen(b[i]);  
			e = max;  
			strcpy(longc, b[i]);  
		}  
		if (strlen(b[i]) < min) {  
			min = strlen(b[i]);  
			strcpy(shortc, b[i]);  
		}  
	}  
	for (int i = 0; i <= q; i++) {  
		for (int j = i + 1; j <= q; j++) {  
			if (strcmp(b[i], b[j]) > 0) {  
				strcpy(tmp, b[i]);  
				strcpy(b[i], b[j]);    
				strcpy(b[j],tmp);  
			}  
		}  
	}   
	strcpy(c, b[0]);  
	for (int i = 1; i <= q; i++) {
		strcat(c, " ");
		strcat(c, b[i]);
	}
	for (int i = 0; i <= q; i++) {
		if (strlen(b[i]) == max) count++;
	}
	if (count > 1) {
		count = 0;
		for (int i = 0; i <= q; i++) {
			if (count == 0 && strlen(b[i]) == max) {
				strcpy(hapc, b[i]); count++;
			}
			else if (count == 1 && strlen(b[i]) == max) {
				strcat(hapc, b[i]); count++;
			}
		}
		printf("%s\n%s\n%s\n%s\n", c, longc, shortc, hapc);  
	}
	else {  
		strcpy(hapc, longc);  
		for (int i = 0; i <= q; i++) {  
			if (strlen(b[i]) < max && strlen(b[i]) > t) {  
				t = strlen(b[i]);  
				strcpy(tmp, b[i]);  
			}  
		}  
		if (strcmp(tmp, hapc) < 0) {  
			strcat(tmp, hapc);  
			printf("%s\n%s\n%s\n%s\n", c, longc, shortc, tmp);  
		}  
		else {  
			strcat(hapc, tmp);  
			printf("%s\n%s\n%s\n%s\n", c, longc, shortc, hapc);  
		}  
	}  
	return 0;  
}  

# 3 - 2 번

#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
	char a[10000], b[22][100], c[100000],d[1000],longc[1000],shortc[1000],hapc[1000],tmp[10000],*p,result[10000]="\0";
	gets(a);
	gets(c);
	gets(d);
	int q = 0, r = 0,e=0,t=0,max=0,min=99999,count=0;
	for (int i = 0; i < strlen(a); i++) {
		if (a[i] == ' ') {
			b[q][r] = '\0';
			q++; r = 0;
		}
		else b[q][r++] = a[i];
	}
	b[q][r] = '\0';
	for (int i = 0; i <= q; i++) {
		if (strlen(b[i]) < strlen(c) && strlen(b[i]) < strlen(d)) {
			strcat(result, b[i]);
			strcat(result, " ");
			continue;
		}
		if (strlen(b[i]) == strlen(c) && strcmp(b[i],c)==0) {
			e++;
			strcat(result, "*");
			strcat(result, b[i]);
			strcat(result, "* ");
			continue;
		}
		if (strlen(b[i]) == strlen(d) && strcmp(b[i], d) == 0) {
			t++;
			continue;
		}

		count = 0;
		for (p = b[i]; p < b[i] + strlen(b[i]);p++) {
			if (strncmp(p, c, strlen(c))==0&&count == 0) {
				strcat(result, "*");
				strcat(result, c);
				strcat(result, "*");
				e++;
				p = p + strlen(c);
				count++;
				strcat(result, p);
				break;
			}
			else if(strncmp(p, d, strlen(d)) == 0 && count == 0) {
				t++;
				p = p + strlen(d);
				strcat(result, p);
				count++;
				break;
			}
			else {
				tmp[0] = p[0];
				tmp[1] = '\0';
				strcat(result, tmp);
			}
		}
		strcat(result, " ");
	}
	
	printf("%d %d\n%s", e, t, result);

	return 0;
}


# 4 - 2 번
#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct student {
	char name[100],grad;
	int mid1, mid2, final,total,rank;
};

int main() {
	int n;
	struct student st[25],tmp;
	scanf("%d", &n); getchar();
	for (int i = 0; i < n; i++) {
		scanf("%s %d %d %d", st[i].name, &st[i].mid1, &st[i].mid2, &st[i].final); getchar();
		st[i].total = st[i].mid1 + st[i].mid2 + st[i].final;
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (st[i].total < st[j].total || (st[i].total == st[j].total && st[i].final < st[j].final)) {
				tmp = st[i];
				st[i] = st[j];
				st[j] = tmp;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (i > 0 && st[i].total == st[i - 1].total && st[i].final == st[i - 1].final) st[i].rank = st[i-1].rank;
		else st[i].rank = i + 1;
		if (st[i].rank < n * 0.35) st[i].grad = 'A';
		else if (st[i].rank < n * 0.75) st[i].grad = 'B';
		else st[i].grad = 'F';
		printf("%s %d %d %d %c \n", st[i].name, st[i].rank, st[i].total, st[i].final, st[i].grad);
	}
	return 0;
}

# 5 - 2번

#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct exam1 {
	char name[100];
	int test;
};

struct exam2 {
	char name[100], grad;
	int test[8], cnt, max;
};
int exam_rearrange(struct exam1* p, struct exam2* q, int n);
int main() {
	int n,a=0,b=0;
	struct exam1 st[200];
	struct exam2 stt[200],tmp;
	scanf("%d", &n); getchar();
	for (int i = 0; i < n; i++) {
		scanf("%s %d", st[i].name, &st[i].test); getchar();
	}
	a = exam_rearrange(st, stt, n);
	for (int i = 0; i < a; i++) {
		b = 0;
		for (int j = 0; j < stt[i].cnt; j++) {
			if (stt[i].test[j] >= 70) b++;
		}
		if ((double)stt[i].cnt * 0.5 > b) stt[i].grad = 'F';
		else {
			if (stt[i].max >= 85) stt[i].grad = 'A';
			else stt[i].grad = 'B';
		}
	}
	for (int i = 0; i < a; i++) {
		for (int j = i + 1; j < a; j++) {
			if (stt[i].grad > stt[j].grad || (stt[i].grad == stt[j].grad && stt[i].cnt > stt[j].cnt)) {
				tmp = stt[i];
				stt[i] = stt[j];
				stt[j] = tmp;
			}
		}
	}
	for (int i = 0; i < a; i++) {
		printf("%s %d %d %c ",stt[i].name, stt[i].max, stt[i].cnt, stt[i].grad);
		for (int j = 0; j < stt[i].cnt; j++) {
			printf("%d ", stt[i].test[j]);
		}
		printf("\n");
	}
	return 0;
}
int exam_rearrange(struct exam1* p, struct exam2* q, int n) {
	int a = 0, b=0; 
	struct exam1* r;
	struct exam2* t;
	for (r = p; r < p + n; r++) {
		b = 0;
		for (t = q; t <  q +a; t++) {
			if (strcmp(t -> name, r->name) == 0) {
				t->test[t->cnt] = r ->test;
				if (t->max < t->test[t->cnt]) t->max = t->test[t->cnt];
				t->cnt++;
				b++;
			}
		}
		if (b == 0) {
			t = q + a;
			strcpy(t->name, r ->name);
			t->cnt = 1;
			t->test[0] = r ->test;
			t->max = t->test[0];
			a++;
		}
	}
	return a;
}
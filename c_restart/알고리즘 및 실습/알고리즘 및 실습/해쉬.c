//#define _CRT_SECURE_NO_WARNINGS 
//
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include<time.h>
//
//int main() {
//	int n,m,q,*num,j = 0,x;
//	char c;
//	scanf("%d %d", &m, &n); getchar();
//	num = (int*)malloc(sizeof(int) * m);
//	for (int i = 0; i < m; i++) num[i] = 0;
//	while (1) {
//		scanf("%c", &c);
//		if (c == 'i') {
//			j = 0;
//			scanf("%d", &x); getchar();
//			while (1) {
//				if (num[((x % m)+j)%m] == 0) {
//					num[((x % m) + j) % m] = x;
//					printf("%d\n", ((x % m) + j) % m);
//					break;
//				}
//				printf("C");
//				j++;
//			}
//		}
//		else if (c == 's') {
//			j = 0;
//			scanf("%d", &x); getchar();
//			while (1) {
//				if (num[((x % m) + j) % m] == 0) {
//					printf("-1\n");
//					break;
//				}
//				if (num[((x % m) + j) % m] == x) {
//					printf("%d\n", ((x % m) + j) % m);
//					printf("%d\n", num[((x % m) + j) % m]);
//					break;
//				}
//
//				//printf("%d ", num[(x % m + j * (q - (x % q))) % m]);
//				j++;
//			}
//		}
//		else if (c == 'p') {
//			getchar();
//			for (int i = 0; i < m; i++) {
//				printf(" %d", num[i]);
//			}
//			printf("\n");
//		}
//		else if (c == 'e') {
//			getchar();
//			break;
//		}
//
//	}
//
//	free(num);
//	return 0;
//}
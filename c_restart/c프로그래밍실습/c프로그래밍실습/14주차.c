#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    int n[50][2], x, y, m,c=1;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) scanf("%d %d", &n[i][0], &n[i][1]);
    for (int i = 0; i < m; i++) {
        c = 1;
        for (int k = 0; k < m; k++) {
            if (n[i][0] < n[k][0] && n[i][1] < n[k][1]) c++;
        }
        printf("%d ", c);
    }

    return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
    char x[6][5] = { {'Z', 'E', 'R', 'O', '-'}, {'O', 'N', 'E', '-', '-'}, {'T', 'W', 'O', '-', '-'}, {'T', 'H', 'R', 'E', 'E'}, {'F', 'O', 'U', 'R', '-'},{'F', 'I', 'V', 'E', '-'} };
    int a;

    for (int i = 0; i < 3; i++) {
        scanf("%d", &a);
        for (int j = 0; j < 5; j++) {
            printf("%c", x[a][j]);
        }
        printf("\n");

    }
    return 0;x
}   
#define _CRT_SECURE_NO_WARNINGS 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

int countOnesButSlow(int** a, int n);
int countOnes(int** arr, int n);

int first_h_w_01_main() {
    int n1 = 10000, n2 = 20000, n3 = 30000, ** arr, kTotal1 = 0, kTotal2 = 0, kTotal3 = 0, num1, num2, k, oness1, oness2, oness3, onesf1, onesf2, onesf3;
    double  cputimes1, cputimes2, cputimes3, cputimef1, cputimef2, cputimef3;
    srand(time(NULL)); // �ð� �ʱ�ȭ�Ͽ� ������ ��¥ �������� �����
    arr = (int**)malloc(sizeof(int*) * n1);
    for (int i = 0; i < n1; i++) arr[i] = (int*)malloc(sizeof(int) * n1); // �����Ҵ��Ͽ� ũ�� �������
    k = n1;
    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;

    QueryPerformanceFrequency(&ticksPerSec);
    for (int i = 0; i < n1; i++) {
        kTotal1 = kTotal1 + k; // ���� ���� ����ֱ�
        for (int j = 0; j < n1; j++) {
            if (j < k) arr[i][j] = 1; // k��ŭ 1 ����ֱ�
            else arr[i][j] = 0; // k�Ѿ�� 0����ֱ�
        }
        num1 = k * 0.9; // ���� ���۰�
        num2 = k * 0.1; // ���� ����
        if (num2 == 0) k = num1; // 0���� ���ֱ�
        else k = ((((long)rand() << 15) | rand()) % num2) + num1; // 0.9k ~ 1.0k�� ����
    }
    QueryPerformanceCounter(&start); // �������� 1���� ��� ����
    oness1 = countOnesButSlow(arr, n1); // �������� 1���� ����
    QueryPerformanceCounter(&end); // �������� 1���� ��
    diff.QuadPart = end.QuadPart - start.QuadPart;
    cputimes1 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
    QueryPerformanceCounter(&start); // �������� 1���� ��� ����
    onesf1 = countOnes(arr, n1); // �������� 1���� ����
    QueryPerformanceCounter(&end); // �������� 1���� ��
    diff.QuadPart = end.QuadPart - start.QuadPart;
    cputimef1 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
    free(arr);
    arr = (int**)malloc(sizeof(int*) * n2);
    for (int i = 0; i < n2; i++) arr[i] = (int*)malloc(sizeof(int) * n2); // �����Ҵ��Ͽ� ũ�� ������� 2����
    k = n2;
    for (int i = 0; i < n2; i++) {
        kTotal2 = kTotal2 + k; // ���� ���� ����ֱ�
        for (int j = 0; j < n2; j++) {
            if (j < k) arr[i][j] = 1; // k��ŭ 1 ����ֱ�
            else arr[i][j] = 0; // k�Ѿ�� 0����ֱ�
        }
        num1 = k * 0.9; // ���� ���۰�
        num2 = k * 0.1; // ���� ����
        if (num2 == 0) k = num1; // 0���� ���ֱ�
        else k = ((((long)rand() << 15) | rand()) % num2) + num1; // 0.9k ~ 1.0k�� ����
    }
    QueryPerformanceCounter(&start); // �������� 2���� ��� ����
    oness2 = countOnesButSlow(arr, n2); // �������� 2���� ����
    QueryPerformanceCounter(&end); // �������� 2���� ��
    diff.QuadPart = end.QuadPart - start.QuadPart;
    cputimes2 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
    QueryPerformanceCounter(&start); // �������� 2���� ��� ����
    onesf2 = countOnes(arr, n2); // �������� 2���� ����
    QueryPerformanceCounter(&end); // �������� 2���� ��
    diff.QuadPart = end.QuadPart - start.QuadPart;
    cputimef2 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
    free(arr);
    arr = (int**)malloc(sizeof(int*) * n3);
    for (int i = 0; i < n3; i++) arr[i] = (int*)malloc(sizeof(int) * n3); // �����Ҵ��Ͽ� ũ�� ������� 3����
    k = n3;
    for (int i = 0; i < n3; i++) {
        kTotal3 = kTotal3 + k; // ���� ���� ����ֱ�
        for (int j = 0; j < n3; j++) {
            if (j < k) arr[i][j] = 1; // k��ŭ 1 ����ֱ�
            else arr[i][j] = 0; // k�Ѿ�� 0����ֱ�
        }
        num1 = k * 0.9; // ���� ���۰�
        num2 = k * 0.1; // ���� ����
        if (num2 == 0) k = num1; // 0���� ���ֱ�
        else k = ((((long)rand() << 15) | rand()) % num2) + num1; // 0.9k ~ 1.0k�� ����
    }
    QueryPerformanceCounter(&start); // �������� 3���� ��� ����
    oness3 = countOnesButSlow(arr, n3); // �������� 3���� ����
    QueryPerformanceCounter(&end); // �������� 3���� ��
    diff.QuadPart = end.QuadPart - start.QuadPart;
    cputimes3 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
    QueryPerformanceCounter(&start); // �������� 3���� ��� ����
    onesf3 = countOnes(arr, n3); // �������� 3���� ����
    QueryPerformanceCounter(&end); // �������� 3���� ��
    diff.QuadPart = end.QuadPart - start.QuadPart;
    cputimef3 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
    free(arr);
    printf("%d %d %.12f\n", kTotal3, onesf3, cputimef3); // �������� 30000��
    printf("%d %d %.12f\n", kTotal1, onesf1, cputimef1); // �������� 10000��
    printf("%d %d %.12f\n", kTotal2, onesf2, cputimef2); // �������� 20000��
    printf("%d %d %.12f\n", kTotal3, oness3, cputimes3); // �������� 30000��
    printf("%d %d %.12f\n", kTotal1, oness1, cputimes1); // �������� 10000��
    printf("%d %d %.12f\n", kTotal2, oness2, cputimes2); // �������� 20000��


    return 0;
}



int countOnesButSlow(int** arr, int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] == 1) max++; // 1������ max�� ����
        }
    }
    return max;
}
int countOnes(int** arr, int n) {
    int max = 0;
    int j = n - 1;
    for (int i = 0; i < n; i++) {
        while (j > 0 && arr[j][i] == 0) j = j - 1; // ������ ��� ��������.
        if (arr[j][i] == 1) max = max + j + 1; // 0�ΰ�츦 ���ϴ� ���� �����ϱ� ���� 1������ ����
        else break; // ���� ���Ḧ ���� 0�̸� �극��ũ ���� �־���
    }
    return max;
}
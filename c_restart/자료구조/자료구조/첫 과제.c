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
    srand(time(NULL)); // 시간 초기화하여 랜덤값 진짜 랜덤으로 만들기
    arr = (int**)malloc(sizeof(int*) * n1);
    for (int i = 0; i < n1; i++) arr[i] = (int*)malloc(sizeof(int) * n1); // 동적할당하여 크기 만들어줌
    k = n1;
    LARGE_INTEGER ticksPerSec;
    LARGE_INTEGER start, end, diff;

    QueryPerformanceFrequency(&ticksPerSec);
    for (int i = 0; i < n1; i++) {
        kTotal1 = kTotal1 + k; // 실제 갯수 집어넣기
        for (int j = 0; j < n1; j++) {
            if (j < k) arr[i][j] = 1; // k만큼 1 집어넣기
            else arr[i][j] = 0; // k넘어가면 0집어넣기
        }
        num1 = k * 0.9; // 랜덤 시작값
        num2 = k * 0.1; // 랜덤 끝값
        if (num2 == 0) k = num1; // 0오류 없애기
        else k = ((((long)rand() << 15) | rand()) % num2) + num1; // 0.9k ~ 1.0k로 설정
    }
    QueryPerformanceCounter(&start); // 느린버전 1만번 계산 시작
    oness1 = countOnesButSlow(arr, n1); // 느린버전 1만번 실행
    QueryPerformanceCounter(&end); // 느린버전 1만번 끝
    diff.QuadPart = end.QuadPart - start.QuadPart;
    cputimes1 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
    QueryPerformanceCounter(&start); // 빠른버전 1만번 계산 시작
    onesf1 = countOnes(arr, n1); // 빠른버전 1만번 실행
    QueryPerformanceCounter(&end); // 빠른버전 1만번 끝
    diff.QuadPart = end.QuadPart - start.QuadPart;
    cputimef1 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
    free(arr);
    arr = (int**)malloc(sizeof(int*) * n2);
    for (int i = 0; i < n2; i++) arr[i] = (int*)malloc(sizeof(int) * n2); // 동적할당하여 크기 만들어줌 2만번
    k = n2;
    for (int i = 0; i < n2; i++) {
        kTotal2 = kTotal2 + k; // 실제 갯수 집어넣기
        for (int j = 0; j < n2; j++) {
            if (j < k) arr[i][j] = 1; // k만큼 1 집어넣기
            else arr[i][j] = 0; // k넘어가면 0집어넣기
        }
        num1 = k * 0.9; // 랜덤 시작값
        num2 = k * 0.1; // 랜덤 끝값
        if (num2 == 0) k = num1; // 0오류 없애기
        else k = ((((long)rand() << 15) | rand()) % num2) + num1; // 0.9k ~ 1.0k로 설정
    }
    QueryPerformanceCounter(&start); // 느린버전 2만번 계산 시작
    oness2 = countOnesButSlow(arr, n2); // 느린버전 2만번 실행
    QueryPerformanceCounter(&end); // 느린버전 2만번 끝
    diff.QuadPart = end.QuadPart - start.QuadPart;
    cputimes2 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
    QueryPerformanceCounter(&start); // 빠른버전 2만번 계산 시작
    onesf2 = countOnes(arr, n2); // 빠른버전 2만번 실행
    QueryPerformanceCounter(&end); // 빠른버전 2만번 끝
    diff.QuadPart = end.QuadPart - start.QuadPart;
    cputimef2 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
    free(arr);
    arr = (int**)malloc(sizeof(int*) * n3);
    for (int i = 0; i < n3; i++) arr[i] = (int*)malloc(sizeof(int) * n3); // 동적할당하여 크기 만들어줌 3만번
    k = n3;
    for (int i = 0; i < n3; i++) {
        kTotal3 = kTotal3 + k; // 실제 갯수 집어넣기
        for (int j = 0; j < n3; j++) {
            if (j < k) arr[i][j] = 1; // k만큼 1 집어넣기
            else arr[i][j] = 0; // k넘어가면 0집어넣기
        }
        num1 = k * 0.9; // 랜덤 시작값
        num2 = k * 0.1; // 랜덤 끝값
        if (num2 == 0) k = num1; // 0오류 없애기
        else k = ((((long)rand() << 15) | rand()) % num2) + num1; // 0.9k ~ 1.0k로 설정
    }
    QueryPerformanceCounter(&start); // 느린버전 3만번 계산 시작
    oness3 = countOnesButSlow(arr, n3); // 느린버전 3만번 실행
    QueryPerformanceCounter(&end); // 느린버전 3만번 끝
    diff.QuadPart = end.QuadPart - start.QuadPart;
    cputimes3 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
    QueryPerformanceCounter(&start); // 빠른버전 3만번 계산 시작
    onesf3 = countOnes(arr, n3); // 빠른버전 3만번 실행
    QueryPerformanceCounter(&end); // 빠른버전 3만번 끝
    diff.QuadPart = end.QuadPart - start.QuadPart;
    cputimef3 = ((double)diff.QuadPart / (double)ticksPerSec.QuadPart);
    free(arr);
    printf("%d %d %.12f\n", kTotal3, onesf3, cputimef3); // 빠른버전 30000번
    printf("%d %d %.12f\n", kTotal1, onesf1, cputimef1); // 빠른버전 10000번
    printf("%d %d %.12f\n", kTotal2, onesf2, cputimef2); // 빠른버전 20000번
    printf("%d %d %.12f\n", kTotal3, oness3, cputimes3); // 느린버전 30000번
    printf("%d %d %.12f\n", kTotal1, oness1, cputimes1); // 느린버전 10000번
    printf("%d %d %.12f\n", kTotal2, oness2, cputimes2); // 느린버전 20000번


    return 0;
}



int countOnesButSlow(int** arr, int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (arr[i][j] == 1) max++; // 1있으면 max값 증가
        }
    }
    return max;
}
int countOnes(int** arr, int n) {
    int max = 0;
    int j = n - 1;
    for (int i = 0; i < n; i++) {
        while (j > 0 && arr[j][i] == 0) j = j - 1; // 없으면 계속 내려간다.
        if (arr[j][i] == 1) max = max + j + 1; // 0인경우를 더하는 것을 방지하기 위해 1조건을 넣음
        else break; // 빠른 종료를 위해 0이면 브레이크 문을 넣었음
    }
    return max;
}
#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<windows.h>

void DPCMDecoder(int* prsy, int q, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);
void read_matrix_from_file(const char* filename, int* matrix, int rows, int cols);
void makeOutFile(BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, char* fileName, double* y);


int main() {
	BITMAPFILEHEADER bmpFile ;
	BITMAPINFOHEADER bmpInfo;
	FILE* inputFile = NULL;
	inputFile = fopen("AICenterY.bmp", "rb"); // 원본 영상

	fread(&bmpFile, sizeof(BITMAPFILEHEADER), 1, inputFile);
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, inputFile);

	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage, bitCnt = bmpInfo.biBitCount, stride = (((bitCnt / 8) * width) + 3) / 4 * 4, max;


	// q = 20, 저장할 공간 만들기
	int* prsy, q = 20;
	prsy = (int*)calloc(width * height, sizeof(int));

	// 디코더 시작
	DPCMDecoder(prsy, q, bmpFile, bmpInfo);

	free(prsy);


	return 0;
}


void DPCMDecoder(int* prsy, int q, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo) {
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage;
	double* rs;

	rs = (double*)calloc(width * height, sizeof(double));
	// prsy에 값 받아오기
	read_matrix_from_file("bitstream.txt", prsy, height, width);

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (i == 0) {
				// 0위치는 128에서 더하기
				rs[j * width + i] = 128 + prsy[j * width + i] * q;
			}
			else {
				// 나머지 위치는 직전 값에서 더하기
				rs[j * width + i] = rs[j * width + i - 1] + prsy[j * width + i] * q;

			}

		}
	}

	// 파일 만들기
	makeOutFile(bmpFile, bmpInfo, "reconDecY.bmp", rs);
	free(rs);

}

void read_matrix_from_file(const char* filename, int* matrix, int height, int width) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		perror("파일 열기 실패");
		return;
	}
	int a[3];

	// 파일 읽기 시작
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			for (int k = 0; k < 3; k++) {
				// 값 한개씩 읽어서 저장하기
				a[k]=fgetc(file);
			}
			
			if (a[0] == '0') { // 0
				if (a[1] == '0') { // 00
					if (a[2] == '0') { //000
						matrix[j * width + i] = -4;
					}
					else { //001
						matrix[j * width + i] = -3;
					}
				}
				else { // 01
					if (a[2] == '0') { //010
						matrix[j * width + i] = -2;
					}
					else { //011
						matrix[j * width + i] = -1;
					}
				}
			}
			else { //1
				if (a[1] == '0') { // 10
					if (a[2] == '0') { //100
						matrix[j * width + i] = 0;
					}
					else { //101
						matrix[j * width + i] = 1;
					}
				}
				else {// 11
					if (a[2] == '0') {//110
						matrix[j * width + i] = 2;
					}
					else { // 111
						matrix[j * width + i] = 3;
					}
				}
			}
			
		}
	}

	fclose(file);
}

// 사진 만들어서 내보내기
void makeOutFile(BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, char* fileName, double* y) {
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage, bitCnt = bmpInfo.biBitCount, stride = (((bitCnt / 8) * width) + 3) / 4 * 4;
	unsigned char* outputImg = NULL;
	outputImg = (unsigned char*)calloc(size, sizeof(unsigned char));
	// Y값 넘기기
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			for (int k = 0; k < 3; k++) outputImg[j * stride + 3 * i + k] = (unsigned char)(y[j * width + i] > 255 ? 255 : (y[j * width + i] < 0 ? 0 : y[j * width + i]));
		}
	}
	// 파일 만드기
	FILE* outputFile = fopen(fileName, "wb");

	// 파일 작성
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile);
	fwrite(outputImg, sizeof(unsigned char), size, outputFile);

	// 변수 제거 
	fclose(outputFile);
	free(outputImg);
}

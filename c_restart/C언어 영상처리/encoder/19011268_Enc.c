#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<windows.h>

void DPCMEncoder(double*, int*, int, BITMAPFILEHEADER, BITMAPINFOHEADER);
void write_matrix_to_file(const char* filename, int* matrix, int height, int width);
void makeOutFile(BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, char* fileName, double* y);


int main() {
	BITMAPFILEHEADER bmpFile, bmpFile2;
	BITMAPINFOHEADER bmpInfo, bmpInfo2;
	FILE* inputFile = NULL, * inputFile2 = NULL;
	inputFile = fopen("AICenterY.bmp", "rb"); // 원본 영상

	fread(&bmpFile, sizeof(BITMAPFILEHEADER), 1, inputFile);
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, inputFile);

	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage, bitCnt = bmpInfo.biBitCount, stride = (((bitCnt / 8) * width) + 3) / 4 * 4, max;

	double* y;
	y = (double*)calloc(width * height, sizeof(double));

	unsigned char* inputImg = NULL;
	inputImg = (unsigned char*)calloc(size, sizeof(unsigned char));

	fread(inputImg, sizeof(unsigned char), size, inputFile);

	// 값 받아오기
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			y[j * width + i] = inputImg[j * stride + 3 * i];
		}
	}

	// 저장 공간, q값 정하기
	int* prsy, q = 20;
	prsy = (int*)calloc(width * height, sizeof(int));

	// 인코딩 시작
	DPCMEncoder(y, prsy, q, bmpFile, bmpInfo);

	return 0;
}



void DPCMEncoder(double* org, int* prsy, int q, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo) {
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage;
	double* pe, * rs;
	pe = (double*)calloc(width * height, sizeof(double));
	rs = (double*)calloc(width * height, sizeof(double));
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			// 여긴 시작이라 128을 빼줄 곳
			if (i == 0) {
				pe[j * width + i] = org[j * width + i] - 128;
				// q로 나누기
				prsy[j * width + i] = (int)(pe[j * width + i] / q);
				// bit 범위 넘어가는 곳은 제한해주기
				if (prsy[j * width + i] < -3) prsy[j * width + i] = -4;
				else if (prsy[j * width + i] > 2)prsy[j * width + i] = 3;
				rs[j * width + i] = 128 + prsy[j * width + i] * q;
			}
			// 여기는 시작 부분이 아니라 직전 값으로 더한다.
			else {
				pe[j * width + i] = org[j * width + i] - rs[j * width + i - 1];
				// q로 나누기
				prsy[j * width + i] = (int)(pe[j * width + i] / q);
				//bit 범위 넘어가는 곳은 제한해주기
				if (prsy[j * width + i] < -3) prsy[j * width + i] = -4;
				else if (prsy[j * width + i] > 2)prsy[j * width + i] = 3;

				rs[j * width + i] = rs[j * width + i - 1] + prsy[j * width + i] * q;
			}

		}
	}
	// 사진 출력
	makeOutFile(bmpFile, bmpInfo, "reconEncY.bmp", rs);


	// 양자화 값 출력
	write_matrix_to_file("bitstream.txt", prsy, height, width);


	free(rs);
	free(pe);
}

void write_matrix_to_file(const char* filename, int* matrix, int height, int width) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		perror("파일 열기 실패");
		return;
	}
	
	// 값에 따라 000 ~ 111 txt 파일에 작성하기
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (matrix[j * width + i] == -4) fprintf(file, "%s","000");
			if (matrix[j * width + i] == -3) fprintf(file, "%s", "001");
			if (matrix[j * width + i] == -2) fprintf(file, "%s", "010");
			if (matrix[j * width + i] == -1) fprintf(file, "%s", "011");
			if (matrix[j * width + i] == 0) fprintf(file, "%s", "100");
			if (matrix[j * width + i] == 1) fprintf(file, "%s", "101");
			if (matrix[j * width + i] == 2) fprintf(file, "%s", "110");
			if (matrix[j * width + i] == 3) fprintf(file, "%s", "111");
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
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile);
	fwrite(outputImg, sizeof(unsigned char), size, outputFile);

	// 변수 제거 
	fclose(outputFile);
	free(outputImg);
}

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
	inputFile = fopen("AICenterY.bmp", "rb"); // ���� ����

	fread(&bmpFile, sizeof(BITMAPFILEHEADER), 1, inputFile);
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, inputFile);

	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage, bitCnt = bmpInfo.biBitCount, stride = (((bitCnt / 8) * width) + 3) / 4 * 4, max;

	double* y;
	y = (double*)calloc(width * height, sizeof(double));

	unsigned char* inputImg = NULL;
	inputImg = (unsigned char*)calloc(size, sizeof(unsigned char));

	fread(inputImg, sizeof(unsigned char), size, inputFile);

	// �� �޾ƿ���
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			y[j * width + i] = inputImg[j * stride + 3 * i];
		}
	}

	// ���� ����, q�� ���ϱ�
	int* prsy, q = 20;
	prsy = (int*)calloc(width * height, sizeof(int));

	// ���ڵ� ����
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
			// ���� �����̶� 128�� ���� ��
			if (i == 0) {
				pe[j * width + i] = org[j * width + i] - 128;
				// q�� ������
				prsy[j * width + i] = (int)(pe[j * width + i] / q);
				// bit ���� �Ѿ�� ���� �������ֱ�
				if (prsy[j * width + i] < -3) prsy[j * width + i] = -4;
				else if (prsy[j * width + i] > 2)prsy[j * width + i] = 3;
				rs[j * width + i] = 128 + prsy[j * width + i] * q;
			}
			// ����� ���� �κ��� �ƴ϶� ���� ������ ���Ѵ�.
			else {
				pe[j * width + i] = org[j * width + i] - rs[j * width + i - 1];
				// q�� ������
				prsy[j * width + i] = (int)(pe[j * width + i] / q);
				//bit ���� �Ѿ�� ���� �������ֱ�
				if (prsy[j * width + i] < -3) prsy[j * width + i] = -4;
				else if (prsy[j * width + i] > 2)prsy[j * width + i] = 3;

				rs[j * width + i] = rs[j * width + i - 1] + prsy[j * width + i] * q;
			}

		}
	}
	// ���� ���
	makeOutFile(bmpFile, bmpInfo, "reconEncY.bmp", rs);


	// ����ȭ �� ���
	write_matrix_to_file("bitstream.txt", prsy, height, width);


	free(rs);
	free(pe);
}

void write_matrix_to_file(const char* filename, int* matrix, int height, int width) {
	FILE* file = fopen(filename, "w");
	if (file == NULL) {
		perror("���� ���� ����");
		return;
	}
	
	// ���� ���� 000 ~ 111 txt ���Ͽ� �ۼ��ϱ�
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

// ���� ���� ��������
void makeOutFile(BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, char* fileName, double* y) {
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage, bitCnt = bmpInfo.biBitCount, stride = (((bitCnt / 8) * width) + 3) / 4 * 4;
	unsigned char* outputImg = NULL;
	outputImg = (unsigned char*)calloc(size, sizeof(unsigned char));
	// Y�� �ѱ��
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			for (int k = 0; k < 3; k++) outputImg[j * stride + 3 * i + k] = (unsigned char)(y[j * width + i] > 255 ? 255 : (y[j * width + i] < 0 ? 0 : y[j * width + i]));
		}
	}
	// ���� �����
	FILE* outputFile = fopen(fileName, "wb");
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile);
	fwrite(outputImg, sizeof(unsigned char), size, outputFile);

	// ���� ���� 
	fclose(outputFile);
	free(outputImg);
}

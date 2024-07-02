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
	inputFile = fopen("AICenterY.bmp", "rb"); // ���� ����

	fread(&bmpFile, sizeof(BITMAPFILEHEADER), 1, inputFile);
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, inputFile);

	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage, bitCnt = bmpInfo.biBitCount, stride = (((bitCnt / 8) * width) + 3) / 4 * 4, max;


	// q = 20, ������ ���� �����
	int* prsy, q = 20;
	prsy = (int*)calloc(width * height, sizeof(int));

	// ���ڴ� ����
	DPCMDecoder(prsy, q, bmpFile, bmpInfo);

	free(prsy);


	return 0;
}


void DPCMDecoder(int* prsy, int q, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo) {
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage;
	double* rs;

	rs = (double*)calloc(width * height, sizeof(double));
	// prsy�� �� �޾ƿ���
	read_matrix_from_file("bitstream.txt", prsy, height, width);

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (i == 0) {
				// 0��ġ�� 128���� ���ϱ�
				rs[j * width + i] = 128 + prsy[j * width + i] * q;
			}
			else {
				// ������ ��ġ�� ���� ������ ���ϱ�
				rs[j * width + i] = rs[j * width + i - 1] + prsy[j * width + i] * q;

			}

		}
	}

	// ���� �����
	makeOutFile(bmpFile, bmpInfo, "reconDecY.bmp", rs);
	free(rs);

}

void read_matrix_from_file(const char* filename, int* matrix, int height, int width) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		perror("���� ���� ����");
		return;
	}
	int a[3];

	// ���� �б� ����
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			for (int k = 0; k < 3; k++) {
				// �� �Ѱ��� �о �����ϱ�
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

	// ���� �ۼ�
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile);
	fwrite(outputImg, sizeof(unsigned char), size, outputFile);

	// ���� ���� 
	fclose(outputFile);
	free(outputImg);
}

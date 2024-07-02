#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<windows.h>

#define PI 3.141592
double threshold = 0;

void histo(int height, int width, double* y, int size, int stride, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);
void CumulativeHisto(int height, int width, double* y, int size, int stride, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);

void GammaOut(double*, double, BITMAPFILEHEADER, BITMAPINFOHEADER);

void applyPadding(double* paddedImg, int height, int width, int padding, double* origImg);
void applyPaddingWithAverage(double* paddedImg, int height, int width, int padding, double* origImg);
void getPadding(double* py, int height, int width, int padding, int pheight, int pwidth, double* y2);

void calFilter(double* y3, double* py, int fsize, double* filter, int height, int width, int pwidth);
double median(double* arr, int size);
void calMedianFilter(double* y3, double* py, int fsize, int height, int width, int pwidth);

void getQulity(double* y, double* y3, int width, int height, int bitCnt);

void downsampling(int raito, double* org, double* dws, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);
void averageDownsampling(int ratio, double* org, double* dws, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);

void upSp(int ratio, double* org, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);
void upsampling(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);
void bilinearUpsampling(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);
void bilinearUpsample(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);

void makeOutFile(BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, char* fileName, double* y);
void GammaOut(double* y, double g, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);

void Rotation(double* y, int width, int height, double theta, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);
void edgeMap(double* y, int width, int height, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* edgey);
void sobelEdgeMap(double* y, int width, int height, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* edgey);

int main() {
	BITMAPFILEHEADER bmpFile, bmpFile2;
	BITMAPINFOHEADER bmpInfo, bmpInfo2;
	FILE* inputFile = NULL, * inputFile2 = NULL;
	inputFile = fopen("b3.bmp", "rb"); // 원본 영상


	fread(&bmpFile, sizeof(BITMAPFILEHEADER), 1, inputFile);
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, inputFile);


	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage, bitCnt = bmpInfo.biBitCount, stride = (((bitCnt / 8) * width) + 3) / 4 * 4, max;

	double* y, * y2, mse = 0, psnr = 0, * edgey;
	y = (double*)calloc(width * height, sizeof(double));
	edgey = (double*)calloc(width * height, sizeof(double));
	/*
	printf("width,height,size,bitCnt,stride\n");
	printf("%d %d %d %d %d\n",width,height,size,bitCnt,stride);
	printf("%d %d %d %d %d\n", width2, height2, size2, bitCnt2, stride2);
	*/

	unsigned char* inputImg = NULL, * inputImg2 = NULL;
	inputImg = (unsigned char*)calloc(size, sizeof(unsigned char));
	inputImg2 = (unsigned char*)calloc(size, sizeof(unsigned char));

	fread(inputImg, sizeof(unsigned char), size, inputFile);

	// input 
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			//y[j * width + i] = inputImg[j * stride + 3 * i];
			y[j * width + i] = 0.299 * inputImg[j * stride + 3 * i + 2] + 0.587 * inputImg[j * stride + 3 * i + 1] + 0.114 * inputImg[j * stride + 3 * i + 0];
		}
	}


	// Algorithm

	// sampling
	int ratio = 2;
	double* dws;
	dws = (double*)calloc(width * height / ratio / ratio, sizeof(double));
	downsampling(ratio, y, dws, bmpFile, bmpInfo);
	makeOutFile(bmpFile, bmpInfo, "y.bmp", y);
	return 0;
}






void downsampling(int ratio, double* org, double* dws, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo) {
	int width2 = bmpInfo.biWidth >> ratio, height2 = bmpInfo.biHeight >> ratio, stride2 = (((bmpInfo.biBitCount / 8) * width2) + 3) / 4 * 4, size2 = stride2 * height2;
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight;

	for (int j = 0; j < height2; j++) {
		for (int i = 0; i < width2; i++) {
			dws[j * width2 + i] = org[(j << ratio) * width + (i << ratio)];
		}
	}
	int Err = 55;
	double error_Y;
	for (int j = 0; j < height2; j++) {
		for (int i = 0; i < width2; i++) {
			error_Y = dws[j * width2 + i];
			error_Y += rand() % Err - (Err >> 1);
			dws[j * width2 + i] = error_Y;
		}
	}
	bmpInfo.biWidth = width2;
	bmpInfo.biHeight = height2;
	bmpInfo.biSizeImage = size2;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size2;
	makeOutFile(bmpFile, bmpInfo, "yy.bmp", dws);

}

void makeOutFile(BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, char* fileName, double* y) {
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage, bitCnt = bmpInfo.biBitCount, stride = (((bitCnt / 8) * width) + 3) / 4 * 4;
	unsigned char* outputImg = NULL;
	outputImg = (unsigned char*)calloc(size, sizeof(unsigned char));
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			for (int k = 0; k < 3; k++) outputImg[j * stride + 3 * i + k] = (unsigned char)(y[j * width + i] > 255 ? 255 : (y[j * width + i] < 0 ? 0 : y[j * width + i]));

			//outputImg[j * stride + 3 * i + 1] = (unsigned char)(y3[j * width + i] > 255 ? 255 : (y3[j * width + i] < 0 ? 0 : y3[j * width + i]));
			//outputImg[j * stride + 3 * i + 2] = (unsigned char)(y3[j * width + i] > 255 ? 255 : (y3[j * width + i] < 0 ? 0 : y3[j * width + i]));
		}
	}
	FILE* outputFile = fopen(fileName, "wb");
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile);
	fwrite(outputImg, sizeof(unsigned char), size, outputFile);
	fclose(outputFile);
	free(outputImg);
}
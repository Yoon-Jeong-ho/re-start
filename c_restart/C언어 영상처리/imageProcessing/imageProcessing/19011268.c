#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<windows.h>
#include<math.h>

int main1() { // 이거 하나 제출하면 된다.
	BITMAPFILEHEADER bmpFile, bmpFile2;
	BITMAPINFOHEADER bmpInfo, bmpInfo2;
	FILE* inputFile = NULL, * inputFile2 = NULL;
	inputFile = fopen("originalY.bmp", "rb"); // 파일명 확실하게
	inputFile2 = fopen("testY.bmp", "rb"); // 경로도 확실하게

	fread(&bmpFile, sizeof(BITMAPFILEHEADER), 1, inputFile);
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, inputFile);
	fread(&bmpFile2, sizeof(BITMAPFILEHEADER), 1, inputFile2);
	fread(&bmpInfo2, sizeof(BITMAPINFOHEADER), 1, inputFile2);

	int width = bmpInfo.biWidth;
	int height = bmpInfo.biHeight;
	int size = bmpInfo.biSizeImage;
	int bitCnt = bmpInfo.biBitCount;
	int stride = (((bitCnt / 8) * width) + 3) / 4 * 4;
	double * y, * y2, mse = 0, psnr = 0;
	unsigned char* inputImg = NULL, * inputImg2 = NULL;

	int width2 = bmpInfo2.biWidth;
	int height2 = bmpInfo2.biHeight;
	int size2 = bmpInfo2.biSizeImage;
	int bitCnt2 = bmpInfo2.biBitCount;
	int stride2 = (((bitCnt2 / 8) * width2) + 3) / 4 * 4, max;

	inputImg = (unsigned char*)calloc(size, sizeof(unsigned char));
	inputImg2 = (unsigned char*)calloc(size, sizeof(unsigned char));
	y = (double*)calloc(width * height, sizeof(double));
	y2 = (double*)calloc(width2 * height2, sizeof(double));

	fread(inputImg, sizeof(unsigned char), size, inputFile);
	fread(inputImg2, sizeof(unsigned char), size2, inputFile2);
	// input 
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			y[j * width + i] = inputImg[j * stride + 3 * i];
			y2[j * width2 + i] = inputImg2[j * stride2 + 3 * i];
		}
	}


	

	//get Quality
	unsigned char org, out;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			org = (unsigned char)(y[j * width + i] > 255 ? 255 : (y[j * width + i] < 0 ? 0 : y[j * width + i]));
			out = (unsigned char)(y2[j * width + i] > 255 ? 255 : (y2[j * width + i] < 0 ? 0 : y2[j * width + i]));
			mse += (double)((org - out) * (org - out));

		}
	}
	mse /= (height * width);
	max = pow(2, bitCnt / 3) - 1;
	psnr = mse != 0.0 ? 10.0 * log10(max * max / mse) : 99.99;
	printf("psnr = %.2lf\n", psnr); //PSNR 값만 출력

	free(inputImg);
	free(inputImg2);
	free(y);
	free(y2);
	fclose(inputFile);
	fclose(inputFile2);

	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "dirent.h"  // Include dirent.h
# define M_PI  3.14159265359
double threshold = 0;

void CumulativeHisto(int height, int width, double* y, int size, int stride, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);
void applyPaddingWithAverage(double* paddedImg, int height, int width, int padding, double* origImg);
void calFilter(double* y3, double* py, int fsize, double* filter, int height, int width, int pwidth);
double median(double* arr, int size);
void calMedianFilter(double* y3, double* py, int fsize, int height, int width, int pwidth);
void bilateralFilter(double* paddedImg, double* outputImg, int width, int height, int pwidth, int pheight, int d, double sigmaColor, double sigmaSpace);
void getQulity(double* y, double* y3, int width, int height, int bitCnt, double* psnr);
void upSp(int ratio, double* org, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* upy);
void bilinearUpsampling(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* upy);
void bilinearUpsample(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* upy);
void nTapInterpolation(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, int n, double* upy);
void makeOutFile(BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, char* fileName, double* y);
void sobelEdgeMap(double* y, int width, int height, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* edgey);
void hybridFilter(double* y3, double* py, double* edgey, int fsize, int height, int width, int pwidth, double* gFilter);
double cubicInterpolate(double p0, double p1, double p2, double p3, double x);
double bicubicInterpolate(double p[4][4], double x, double y);
void bicubicUpsample(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* upy);
void generateGaussianFilter(int n, double sigma, double filter[]) {
	double sum = 0.0;
	int half = n / 2;

	// Calculate the Gaussian filter
	for (int x = -half; x <= half; x++) {
		for (int y = -half; y <= half; y++) {
			filter[(x + half) * n + (y + half)] = (1 / (2 * M_PI * sigma * sigma)) * exp(-(x * x + y * y) / (2 * sigma * sigma));
			sum += filter[(x + half) * n + (y + half)];
		}
	}

	// Normalize the filter
	for (int i = 0; i < n * n; i++) {
		filter[i] /= sum;
	}
}

void processImagePairs(const char* dirPath) {
	DIR* dir;
	struct dirent* ent;
	FILE* inputFile = NULL, * inputFile2 = NULL;
	BITMAPFILEHEADER bmpFile, bmpFile2;
	BITMAPINFOHEADER bmpInfo, bmpInfo2;

	double totalPsnr = 0;
	int count = 0;

	if ((dir = opendir(dirPath)) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			if (strstr(ent->d_name, "y.bmp") != NULL && !strstr(ent->d_name, "yy.bmp")) {
				// Construct the corresponding "yy" file name
				char filePath1[256], filePath2[256];
				snprintf(filePath1, sizeof(filePath1), "%s/%s", dirPath, ent->d_name);
				// Replace "y.bmp" with "yy.bmp"
				strcpy(filePath2, filePath1);
				strcpy(filePath2 + strlen(filePath2) - 5, "yy.bmp");

				inputFile = fopen(filePath1, "rb");
				inputFile2 = fopen(filePath2, "rb");

				if (inputFile == NULL || inputFile2 == NULL) {
					printf("Unable to open file %s or %s\n", filePath1, filePath2);
					if (inputFile) fclose(inputFile);
					if (inputFile2) fclose(inputFile2);
					continue;
				}

				fread(&bmpFile, sizeof(BITMAPFILEHEADER), 1, inputFile);
				fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, inputFile);
				fread(&bmpFile2, sizeof(BITMAPFILEHEADER), 1, inputFile2);
				fread(&bmpInfo2, sizeof(BITMAPINFOHEADER), 1, inputFile2);

				int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage, bitCnt = bmpInfo.biBitCount, stride = (((bitCnt / 8) * width) + 3) / 4 * 4;
				int width2 = bmpInfo2.biWidth, height2 = bmpInfo2.biHeight, size2 = bmpInfo2.biSizeImage, bitCnt2 = bmpInfo2.biBitCount, stride2 = (((bitCnt2 / 8) * width2) + 3) / 4 * 4;

				double* y = (double*)calloc(width * height, sizeof(double));
				double* y2 = (double*)calloc(width * height, sizeof(double));
				double mse = 0, psnr = 0, * edgey;
				edgey = (double*)calloc(width2 * height2, sizeof(double));

				unsigned char* inputImg = (unsigned char*)calloc(size, sizeof(unsigned char));
				unsigned char* inputImg2 = (unsigned char*)calloc(size, sizeof(unsigned char));

				fread(inputImg, sizeof(unsigned char), size, inputFile);
				fread(inputImg2, sizeof(unsigned char), size, inputFile2);
				printf("Processing files: %s and %s\n", filePath1, filePath2);
				for (int j = 0; j < height; j++) {
					for (int i = 0; i < width; i++) {
						y[j * width + i] = inputImg[j * stride + 3 * i];
					}
				}
				for (int j = 0; j < height2; j++) {
					for (int i = 0; i < width2; i++) {
						y2[j * width2 + i] = inputImg2[j * stride2 + 3 * i];
					}
				}
				// Algorithm

				// sampling
				int ratio = 4;
				double* upy;


				upy = (double*)calloc(width * height * ratio * ratio, sizeof(double));


				//padding
				int padding = 2, pwidth = width2 + padding * 2, pheight = height2 + padding * 2, psize = pwidth * pheight;
				double* py;
				py = (double*)calloc(pwidth * pheight, sizeof(double));


				applyPaddingWithAverage(py, height2, width2, padding, y2);


				// filter

				int fsize = padding * 2 + 1;

				

				// Gussian Filter
				double G3filter[] = { 1.0 / 16,2.0 / 16,1.0 / 16,2.0 / 16,4.0 / 16,2.0 / 16,1.0 / 16,2.0 / 16,1.0 / 16 };
				double G5filter[] = { 1 / 273.0, 4 / 273.0, 7 / 273.0, 4 / 273.0, 1 / 273.0, 4 / 273.0, 16 / 273.0, 26 / 273.0, 16 / 273.0, 4 / 273.0, 7 / 273.0, 26 / 273.0, 41 / 273.0, 26 / 273.0, 7 / 273.0, 4 / 273.0, 16 / 273.0, 26 / 273.0, 16 / 273.0, 4 / 273.0,1 / 273.0, 4 / 273.0, 7 / 273.0, 4 / 273.0, 1 / 273.0 };
				double* y3;
				y3 = (double*)calloc(width2 * height2, sizeof(double));
				//calFilter(y3,py, fsize, G3filter,height2,width2,pwidth);
				//calMedianFilter( y3,py,  fsize,  height2,  width2,  pwidth);
				bilateralFilter(py, y3, width2, height2, pwidth, pheight, fsize, 50.0, 10); //25.29
				//sobelEdgeMap(y3, width2, height2, bmpFile2, bmpInfo2, edgey);
				//applyPaddingWithAverage(py, height2, width2, padding, y3);
				//bilateralFilter(py, y3, width2, height2, pwidth, pheight, fsize, 50.0, 10);
				//calMedianFilter(y3, py, fsize, height2, width2, pwidth);
				//hybridFilter(y3, py, edgey, fsize, height2, width2, pwidth, G5filter);


				//get Quality
				upSp(ratio, y3, bmpFile2, bmpInfo2, upy);

				double* edgey2;
				edgey2 = (double*)calloc(width * height, sizeof(double));
				int padding2 = 2, pwidth2 = width + padding2 * 2, pheight2 = height + padding2 * 2, psize2 = pwidth2 * pheight2;
				double* py2;
				py2 = (double*)calloc(pwidth2 * pheight2, sizeof(double));
				int fsize2 = padding2 * 2 + 1;

				applyPaddingWithAverage(py2, height, width, padding2, upy);
				bilateralFilter(py2, upy, width, height, pwidth2, pheight2, fsize2, 60.0, 10.0);//192.72
				applyPaddingWithAverage(py2, height, width, padding2, upy);
				sobelEdgeMap(upy, width, height, bmpFile, bmpInfo, edgey2);
				hybridFilter(upy, py2, edgey2, fsize2, height, width, pwidth2, G5filter);
				
				

				//applyPaddingWithAverage(py2, height, width, padding2, upy);
				//sobelEdgeMap(upy, width, height, bmpFile, bmpInfo, edgey2);
				//hybridFilter(upy, py2, edgey2, fsize2, height, width, pwidth2, G5filter);
				
				int padding3 = 1, pwidth3 = width + padding3 * 2, pheight3 = height + padding3 * 2, psize3 = pwidth3 * pheight3;
				double* py3;
				py3 = (double*)calloc(pwidth3 * pheight3, sizeof(double));
				int fsize3 = padding3 * 2 + 1;

				double* filter;
				filter = (double*)calloc(fsize3 * fsize3, sizeof(double));
				for (int i = 0; i < fsize3 * fsize3; i++) filter[i] = 1.0 / (fsize3 * fsize3);
				double *gfilter;
				gfilter = (double*)calloc(fsize3 * fsize3, sizeof(double));
				generateGaussianFilter(fsize3, fsize3 / 6.0, gfilter);
				applyPaddingWithAverage(py3, height, width, padding3, upy);

				sobelEdgeMap(upy, width, height, bmpFile, bmpInfo, edgey2);
				hybridFilter(upy, py3, edgey2, fsize3, height, width, pwidth3, gfilter);
				applyPaddingWithAverage(py2, height, width, padding2, upy);

				calMedianFilter(upy, py2, fsize2, height, width, pwidth2);


				
				getQulity(y, upy, width, height, bitCnt, &psnr);
				totalPsnr += psnr;
				count++;

				free(inputImg);
				free(inputImg2);
				free(y);
				free(y2);
				free(py);
				free(y3);
				free(edgey);
				free(upy);
				free(edgey2);
				free(py2);

				fclose(inputFile);
				fclose(inputFile2);
			}
		}
		closedir(dir);
	}
	else {
		perror("Could not open directory");
	}

	if (count > 0) {
		printf("Average PSNR: %.2lf\n", totalPsnr / count);
	}
	else {
		printf("No valid image pairs found.\n");
	}
}

int main() {
	processImagePairs("data");
	return 0;
}

void getQulity(double* y, double* y3, int width, int height, int bitCnt, double* psnr) {
	double mse = 0, max;
	unsigned char org, out;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			org = (unsigned char)(y[j * width + i] > 255 ? 255 : (y[j * width + i] < 0 ? 0 : y[j * width + i]));
			out = (unsigned char)(y3[j * width + i] > 255 ? 255 : (y3[j * width + i] < 0 ? 0 : y3[j * width + i]));
			mse += (double)((org - out) * (org - out));
		}
	}
	mse /= (height * width);
	max = pow(2, bitCnt / 3) - 1;
	*psnr = mse != 0.0 ? 10.0 * log10(max * max / mse) : 99.99;
	printf("mse = %.2lf\npsnr = %.2lf\n", mse, *psnr);
}

// 나머지 함수는 그대로 유지됩니다.



void calFilter(double* y3, double* py, int fsize, double* filter, int height, int width, int pwidth) {
	double sumf = 0;
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			sumf = 0;
			for (int k = 0; k < fsize; k++) {
				for (int l = 0; l < fsize; l++) {
					sumf += filter[k * fsize + l] * py[(j + k) * pwidth + (i + l)];
				}
			}
			y3[j * width + i] = sumf;
		}
	}
}


void CumulativeHisto(int height, int width, double* y, int size, int stride, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo) {
	double* histogram;
	histogram = (double*)calloc(256, sizeof(double));
	int width2 = 512, height2 = 512, stride2 = (((bmpInfo.biBitCount / 8) * width2) + 3) / 4 * 4, size2 = stride2 * height2;

	// get Histogram
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			histogram[(unsigned char)(y[j * width + i] > 255 ? 255 : (y[j * width + i] < 0 ? 0 : y[j * width + i]))]++;
		}
	}
	for (int i = 0; i < 255; i++) {
		histogram[i + 1] += histogram[i];
	}
	for (int i = 0; i < 255; i++) {
		if (histogram[i] > height * width * 0.985) {
			threshold = i;
			break;
		}
		if (i == 254) threshold = 254;
	}

	// out Histogram
	double histoMax = 0;
	for (int i = 0; i < 256; i++) {
		if (histogram[i] > histoMax) histoMax = histogram[i];
	}
	unsigned char* outHisto, * HE;
	outHisto = (unsigned char*)calloc(size2, sizeof(unsigned char));
	HE = (unsigned char*)calloc(size, sizeof(unsigned char));


	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			HE[j * stride + 3 * i + 0] = (unsigned char)(255 * histogram[(unsigned char)(y[j * width + i] > 255 ? 255 : (y[j * width + i] < 0 ? 0 : y[j * width + i]))] / (width * height));
			HE[j * stride + 3 * i + 1] = (unsigned char)(255 * histogram[(unsigned char)(y[j * width + i] > 255 ? 255 : (y[j * width + i] < 0 ? 0 : y[j * width + i]))] / (width * height));
			HE[j * stride + 3 * i + 2] = (unsigned char)(255 * histogram[(unsigned char)(y[j * width + i] > 255 ? 255 : (y[j * width + i] < 0 ? 0 : y[j * width + i]))] / (width * height));
		}
	}
	for (int i = 0; i < 256; i++)histogram[i] = histogram[i] / histoMax * 450;

	for (int j = 0; j < height2; j++) {
		for (int i = 0; i < width2; i++) {
			if (histogram[i / 2] > j) continue;
			outHisto[j * stride2 + 3 * i + 0] = 255;
			outHisto[j * stride2 + 3 * i + 1] = 255;
			outHisto[j * stride2 + 3 * i + 2] = 255;
		}
	}


	FILE* outputHisto = fopen("OutCHisto.bmp", "wb");
	bmpInfo.biWidth = 512;
	bmpInfo.biHeight = 512;
	bmpInfo.biSizeImage = 512 * 3 * 512;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 512 * 3 * 512;


	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputHisto);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputHisto);
	fwrite(outHisto, sizeof(unsigned char), size2, outputHisto);

	FILE* outputHE = fopen("OutHE.bmp", "wb");

	bmpInfo.biWidth = width;
	bmpInfo.biHeight = height;
	bmpInfo.biSizeImage = size;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size;

	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputHE);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputHE);
	fwrite(HE, sizeof(unsigned char), size, outputHE);
	fclose(outputHE);
	free(HE);



	free(histogram);
	fclose(outputHisto);
	free(outHisto);
}



void applyPaddingWithAverage(double* paddedImg, int height, int width, int padding, double* origImg) {
	int pheight = height + 2 * padding;
	int pwidth = width + 2 * padding;

	// 원본 이미지 데이터를 중앙에 배치
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			paddedImg[(j + padding) * pwidth + (i + padding)] = origImg[j * width + i];
		}
	}

	// 상하좌우 패딩에 평균 값 적용
	for (int j = 0; j < pheight; j++) {
		for (int i = 0; i < pwidth; i++) {
			// 좌측 패딩 처리
			if (i < padding) {
				double sum = 0;
				int count = 0;
				for (int k = -2; k <= 2; k++) {
					int idx = j + k; // 현재 행에서 상하로 2개씩
					if (idx >= padding && idx < height + padding) { // 범위 체크
						sum += paddedImg[idx * pwidth + padding];
						count++;
					}
				}
				paddedImg[j * pwidth + i] = count > 0 ? sum / count : 0; // 평균 값 적용
			}

			// 우측 패딩 처리
			if (i >= width + padding) {
				double sum = 0;
				int count = 0;
				for (int k = -2; k <= 2; k++) {
					int idx = j + k; // 현재 행에서 상하로 2개씩
					if (idx >= padding && idx < height + padding) { // 범위 체크
						sum += paddedImg[idx * pwidth + (width + padding - 1)];
						count++;
					}
				}
				paddedImg[j * pwidth + i] = count > 0 ? sum / count : 0; // 평균 값 적용
			}
			// 상단 패딩 처리
			for (int p = 0; p < padding; p++) {
				double sum = 0;
				int count = 0;
				for (int k = -2; k <= 2; k++) {
					int idx = i + k; // 현재 컬럼에서 좌우로 2개씩
					if (idx >= padding && idx < width + padding) { // 범위 체크
						sum += paddedImg[padding * pwidth + idx];
						count++;
					}
				}
				paddedImg[p * pwidth + i] = count > 0 ? sum / count : 0; // 평균 값 적용
			}

			// 하단 패딩 처리
			for (int p = 0; p < padding; p++) {
				double sum = 0;
				int count = 0;
				for (int k = -2; k <= 2; k++) {
					int idx = i + k; // 현재 컬럼에서 좌우로 2개씩
					if (idx >= padding && idx < width + padding) { // 범위 체크
						sum += paddedImg[(height + padding - 1) * pwidth + idx];
						count++;
					}
				}
				paddedImg[(height + padding + p) * pwidth + i] = count > 0 ? sum / count : 0; // 평균 값 적용
			}
		}
	}

}



void upSp(int ratio, double* org, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* upy) {
	double* ups;
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight;
	//ups = (double*)calloc(width * height * ratio/2 * ratio/2, sizeof(double));
	ups = (double*)calloc(width * height * ratio * ratio, sizeof(double));

	//upsampling(ratio/2, org, ups, bmpFile, bmpInfo,upy); // 25.23
	//bilinearUpsample(ratio, org, ups, bmpFile, bmpInfo, upy); // 25.22
	//bicubicUpsample(ratio,  org,  ups,  bmpFile,  bmpInfo, upy);
	//bilinearUpsampling(ratio/2, org, ups, bmpFile, bmpInfo, upy);//25.22
	nTapInterpolation(ratio, org, ups, bmpFile, bmpInfo, 4, upy); // 25.19
	double* ups2;
	bmpInfo.biHeight = bmpInfo.biHeight * ratio / 2;
	bmpInfo.biWidth = bmpInfo.biWidth * ratio / 2;

	ups2 = (double*)calloc(width * height * ratio * ratio, sizeof(double));
	//upsampling(ratio / 2, ups, ups2, bmpFile, bmpInfo, upy);
	//bilinearUpsampling(ratio / 2, ups, ups2, bmpFile, bmpInfo, upy); //24.90
	free(ups);
}



void bilinearUpsampling(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* upy) {
	int originalWidth = bmpInfo.biWidth, originalHeight = bmpInfo.biHeight;
	int upscaledWidth = bmpInfo.biWidth * ratio, upscaledHeight = bmpInfo.biHeight * ratio;
	int stride2 = (((bmpInfo.biBitCount / 8) * upscaledWidth) + 3) / 4 * 4, size2 = stride2 * upscaledHeight;

	for (int y = 0; y < upscaledHeight; y++) {
		for (int x = 0; x < upscaledWidth; x++) {
			float gx = ((float)x / (float)upscaledWidth) * (float)(originalWidth - 1);
			float gy = ((float)y / (float)upscaledHeight) * (float)(originalHeight - 1);
			int gxi = (int)gx;
			int gyi = (int)gy;

			double top = (gx - gxi) * org[gyi * originalWidth + (gxi + 1)] + (gxi + 1 - gx) * org[gyi * originalWidth + gxi];
			double bottom = (gx - gxi) * org[(gyi + 1) * originalWidth + (gxi + 1)] + (gxi + 1 - gx) * org[(gyi + 1) * originalWidth + gxi];

			ups[y * upscaledWidth + x] = (gy - gyi) * bottom + (gyi + 1 - gy) * top;
			upy[y * upscaledWidth + x] = ups[y * upscaledWidth + x];
		}
	}

	bmpInfo.biWidth = upscaledWidth;
	bmpInfo.biHeight = upscaledHeight;
	bmpInfo.biSizeImage = size2;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size2;
	makeOutFile(bmpFile, bmpInfo, "OutUPS.bmp", ups);

}

void bilinearUpsample(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* upy) {
	// 원본 이미지의 너비와 높이
	int originalWidth = bmpInfo.biWidth, originalHeight = bmpInfo.biHeight;
	// 업스케일된 이미지의 너비와 높이
	int upscaledWidth = originalWidth * ratio, upscaledHeight = originalHeight * ratio;
	// 업스케일된 이미지의 바이트 배열 크기와 이미지 크기 계산
	int stride2 = (((bmpInfo.biBitCount / 8) * upscaledWidth) + 3) / 4 * 4, size2 = stride2 * upscaledHeight;

	// 업스케일된 이미지의 각 픽셀에 대해
	for (int y = 0; y < upscaledHeight; y++) {
		for (int x = 0; x < upscaledWidth; x++) {
			// 원본 이미지에서 대응되는 좌표 계산
			float gx = ((float)x / (float)upscaledWidth) * (float)(originalWidth - 1);
			float gy = ((float)y / (float)upscaledHeight) * (float)(originalHeight - 1);
			int gxi = (int)gx;
			int gyi = (int)gy;

			// 4개의 인접한 픽셀값 가져오기 (원본 이미지 경계 검사 포함)
			double c00 = org[gyi * originalWidth + gxi];
			double c10 = org[gyi * originalWidth + (gxi + 1 < originalWidth ? gxi + 1 : gxi)];
			double c01 = org[(gyi + 1 < originalHeight ? gyi + 1 : gyi) * originalWidth + gxi];
			double c11 = org[(gyi + 1 < originalHeight ? gyi + 1 : gyi) * originalWidth + (gxi + 1 < originalWidth ? gxi + 1 : gxi)];

			// 두 좌표 사이의 거리 계산
			double dx = gx - gxi;
			double dy = gy - gyi;

			// 두 방향으로 보간
			double c0 = c00 * (1 - dx) + c10 * dx;
			double c1 = c01 * (1 - dx) + c11 * dx;
			double c = c0 * (1 - dy) + c1 * dy;

			// 업스케일된 이미지 배열에 값 할당
			ups[y * upscaledWidth + x] = c;
			upy[y * upscaledWidth + x] = ups[y * upscaledWidth + x];
		}
	}

	// 비트맵 헤더 정보 업데이트
	bmpInfo.biWidth = upscaledWidth;
	bmpInfo.biHeight = upscaledHeight;
	bmpInfo.biSizeImage = size2;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size2;

	// 결과 파일 저장
	makeOutFile(bmpFile, bmpInfo, "OutBiUPS.bmp", ups);
}

void nTapInterpolation(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, int n, double* upy) {
	// 원본 이미지의 너비와 높이
	int originalWidth = bmpInfo.biWidth, originalHeight = bmpInfo.biHeight;
	// 업스케일된 이미지의 너비와 높이
	int upscaledWidth = originalWidth * ratio, upscaledHeight = originalHeight * ratio;
	// 업스케일된 이미지의 바이트 배열 크기와 이미지 크기 계산
	int stride2 = (((bmpInfo.biBitCount / 8) * upscaledWidth) + 3) / 4 * 4, size2 = stride2 * upscaledHeight;

	// n-TAP 필터 계수 설정 (예: 3-tap 또는 4-tap)
	double* coefficients;
	if (n == 3) {
		double coeffs[3] = { 0.25, 0.5, 0.25 };  // 3-tap 간단 평균 계수
		coefficients = coeffs;
	}
	else if (n == 4) {
		double coeffs[4] = { -1.0 / 16, 9.0 / 16, 9.0 / 16, -1.0 / 16 }; // 4-tap 간단 평균 계수
		coefficients = coeffs;
	}
	else {
		printf("지원되지 않는 n-tap 값: %d\n", n);
		return;
	}

	// 업스케일된 이미지의 각 픽셀에 대해
	for (int j = 0; j < upscaledHeight; j++) {
		for (int i = 0; i < upscaledWidth; i++) {
			// 원본 이미지에서 대응되는 좌표 계산
			float x = (float)i / ratio;
			float y = (float)j / ratio;

			double sum = 0;
			// n-TAP 필터링
			for (int k = 0; k < n; k++) {
				int x1 = fmax(0, (int)x - k + 1);
				int y1 = fmax(0, (int)y - k + 1);
				int x2 = fmin(originalWidth - 1, (int)x + k);
				int y2 = fmin(originalHeight - 1, (int)y + k);

				sum += org[y1 * originalWidth + x1] * coefficients[k];
				sum += org[y2 * originalWidth + x2] * coefficients[k];
			}

			// 업스케일된 이미지 배열에 값 할당
			ups[j * upscaledWidth + i] = sum / 2;
			upy[j * upscaledWidth + i] = ups[j * upscaledWidth + i];
		}
	}

	// 비트맵 헤더 정보 업데이트
	bmpInfo.biWidth = upscaledWidth;
	bmpInfo.biHeight = upscaledHeight;
	bmpInfo.biSizeImage = size2;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size2;

	// 결과 파일 저장
	makeOutFile(bmpFile, bmpInfo, "OutUPS.bmp", ups);
}


double cubicInterpolate(double p0, double p1, double p2, double p3, double x) {
	return p1 + 0.5 * x * (p2 - p0 + x * (2.0 * p0 - 5.0 * p1 + 4.0 * p2 - p3 + x * (3.0 * (p1 - p2) + p3 - p0)));
}

double bicubicInterpolate(double p[4][4], double x, double y) {
	double arr[4];
	arr[0] = cubicInterpolate(p[0][0], p[0][1], p[0][2], p[0][3], x);
	arr[1] = cubicInterpolate(p[1][0], p[1][1], p[1][2], p[1][3], x);
	arr[2] = cubicInterpolate(p[2][0], p[2][1], p[2][2], p[2][3], x);
	arr[3] = cubicInterpolate(p[3][0], p[3][1], p[3][2], p[3][3], x);
	return cubicInterpolate(arr[0], arr[1], arr[2], arr[3], y);
}

void bicubicUpsample(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* upy) {
	// 원본 이미지의 너비와 높이
	int originalWidth = bmpInfo.biWidth, originalHeight = bmpInfo.biHeight;
	// 업스케일된 이미지의 너비와 높이
	int upscaledWidth = originalWidth * ratio, upscaledHeight = originalHeight * ratio;
	// 업스케일된 이미지의 바이트 배열 크기와 이미지 크기 계산
	int stride2 = (((bmpInfo.biBitCount / 8) * upscaledWidth) + 3) / 4 * 4, size2 = stride2 * upscaledHeight;

	for (int j = 0; j < upscaledHeight; j++) {
		for (int i = 0; i < upscaledWidth; i++) {
			// 원본 이미지에서 대응되는 좌표 계산
			float gx = ((float)i / (float)upscaledWidth) * (float)(originalWidth - 1);
			float gy = ((float)j / (float)upscaledHeight) * (float)(originalHeight - 1);
			int gxi = (int)gx;
			int gyi = (int)gy;

			// 4x4 블록에서 픽셀 값을 가져옴
			double p[4][4];
			for (int m = -1; m <= 2; m++) {
				for (int n = -1; n <= 2; n++) {
					int x = min(max(gxi + n, 0), originalWidth - 1);
					int y = min(max(gyi + m, 0), originalHeight - 1);
					p[m + 1][n + 1] = org[y * originalWidth + x];
				}
			}

			// 보간 계산
			double dx = gx - gxi;
			double dy = gy - gyi;
			double value = bicubicInterpolate(p, dx, dy);

			// 업스케일된 이미지 배열에 값 할당
			ups[j * upscaledWidth + i] = value;
			upy[j * upscaledWidth + i] = ups[j * upscaledWidth + i];
		}
	}

	// 비트맵 헤더 정보 업데이트
	bmpInfo.biWidth = upscaledWidth;
	bmpInfo.biHeight = upscaledHeight;
	bmpInfo.biSizeImage = size2;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size2;

	// 결과 파일 저장
	makeOutFile(bmpFile, bmpInfo, "OutBicubicUPS.bmp", ups);
}



// Median filter 함수
double median(double* arr, int size) {
	// 배열을 정렬
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (arr[i] > arr[j]) {
				double tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
	// 중간값 반환
	if (size % 2 == 0) {
		return (arr[size / 2 - 1] + arr[size / 2]) / 2.0;
	}
	else {
		return arr[size / 2];
	}
}

// 미디언 필터 적용 함수
void calMedianFilter(double* y3, double* py, int fsize, int height, int width, int pwidth) {
	int filterSize = fsize * fsize;
	double* window = (double*)malloc(filterSize * sizeof(double));

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			int count = 0;
			// 각 픽셀 주변의 값을 window 배열에 저장
			for (int k = 0; k < fsize; k++) {
				for (int l = 0; l < fsize; l++) {
					int xIdx = i + l;
					int yIdx = j + k;
					// 이미지 경계 처리
					if (xIdx >= 0 && xIdx < width && yIdx >= 0 && yIdx < height) {
						window[count++] = py[yIdx * pwidth + xIdx];
					}
				}
			}
			// 미디언 값을 결과 배열에 저장
			y3[j * width + i] = median(window, count);
		}
	}

	free(window);
}

void makeOutFile(BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, char* fileName, double* y) {
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage, bitCnt = bmpInfo.biBitCount, stride = (((bitCnt / 8) * width) + 3) / 4 * 4;
	unsigned char* outputImg = NULL;
	outputImg = (unsigned char*)calloc(size, sizeof(unsigned char));
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			for (int k = 0; k < 3; k++) outputImg[j * stride + 3 * i + k] = (unsigned char)(y[j * width + i] > 255 ? 255 : (y[j * width + i] < 0 ? 0 : y[j * width + i]));
		}
	}
	FILE* outputFile = fopen(fileName, "wb");
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile);
	fwrite(outputImg, sizeof(unsigned char), size, outputFile);
	fclose(outputFile);
	free(outputImg);
}


void sobelEdgeMap(double* y, int width, int height, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* edgey) {
	//padding
	int padding = 2, pwidth = width + padding * 2, pheight = height + padding * 2, psize = pwidth * pheight;
	double* py, * xy, * yy, * outy, sumf = 0;

	py = (double*)calloc(pwidth * pheight, sizeof(double));
	xy = (double*)calloc(width * height, sizeof(double));
	yy = (double*)calloc(width * height, sizeof(double));
	outy = (double*)calloc(width * height, sizeof(double));
	int fsize = padding * 2 + 1;

	double* xfilter, * yfilter;
	xfilter = (double*)calloc(fsize * fsize, sizeof(double));
	yfilter = (double*)calloc(fsize * fsize, sizeof(double));
	double xco, yco;
	for (int i = 0; i < fsize; i++) {
		for (int j = 0; j < fsize; j++) {
			xco = (i - padding);
			yco = (j - padding);
			if (xco == 0 && yco == 0) {
				xfilter[i * fsize + j] = 0;
				yfilter[i * fsize + j] = 0;
			}
			else {
				xfilter[i * fsize + j] = xco / (xco * xco + yco * yco);
				yfilter[i * fsize + j] = yco / (xco * xco + yco * yco);
			}
		}
	}


	applyPaddingWithAverage(py, height, width, padding, y);
	calFilter(xy, py, fsize, xfilter, height, width, pwidth);
	calFilter(yy, py, fsize, yfilter, height, width, pwidth);
	makeOutFile(bmpFile, bmpInfo, "xEdgeOut.bmp", xy);
	makeOutFile(bmpFile, bmpInfo, "yEdgeOut.bmp", yy);
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			outy[j * width + i] = sqrt(xy[j * width + i] * xy[j * width + i] + yy[j * width + i] * yy[j * width + i]);
		}
	}

	CumulativeHisto(height, width, outy, bmpInfo.biSizeImage, (((bmpInfo.biBitCount / 8) * width) + 3) / 4 * 4, bmpFile, bmpInfo);
	//printf("threshold= %f\n", threshold);
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (outy[j * width + i] > threshold) edgey[j * width + i] = 254;
		}
	}
	makeOutFile(bmpFile, bmpInfo, "data/EdgeOut.bmp", outy);
	makeOutFile(bmpFile, bmpInfo, "data/thresholdEdge.bmp", edgey);
	free(py);
	free(xy);
	free(yy);
	free(outy);

}

void bilateralFilter(double* paddedImg, double* outputImg, int width, int height, int pwidth, int pheight, int d, double sigmaColor, double sigmaSpace) {
	// 시그마 컬러 : 픽셀값 차이에 대한 민감도 조절
	// 시그마 스페이스 : 공간적으로 멀리 떨어진 픽셀들의 영향을 줄인다.
	// 필터 반경 설정
	int radius = d / 2;
	// 시그마 값의 제곱 계산 (색상 및 공간)
	double sigmaColor2 = sigmaColor * sigmaColor;
	double sigmaSpace2 = sigmaSpace * sigmaSpace;

	// 출력 이미지의 각 픽셀에 대해
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			double iFiltered = 0;
			double wP = 0;
			// 현재 픽셀 값 가져오기
			double iValue = paddedImg[(y + radius) * pwidth + (x + radius)];

			// 필터링 영역 내의 각 픽셀에 대해
			for (int dy = -radius; dy <= radius; dy++) {
				for (int dx = -radius; dx <= radius; dx++) {
					int ny = y + radius + dy;
					int nx = x + radius + dx;
					// 이웃 픽셀 값 가져오기
					double nValue = paddedImg[ny * pwidth + nx];
					// 공간 거리 계산
					double spatialDist = dx * dx + dy * dy;
					// 색상 거리 계산
					double colorDist = (iValue - nValue) * (iValue - nValue);
					// 가중치 계산
					double weight = exp(-(spatialDist / (2 * sigmaSpace2) + colorDist / (2 * sigmaColor2)));
					// 필터링된 값 계산
					iFiltered += nValue * weight;
					wP += weight;
				}
			}
			// 필터링된 결과를 출력 이미지에 저장
			outputImg[y * width + x] = iFiltered / wP;
		}
	}
}


// 하이브리드 필터 함수
void hybridFilter(double* y3, double* py, double* edgey, int fsize, int height, int width, int pwidth, double* gFilter) {
	double* window = (double*)malloc(fsize * fsize * sizeof(double));
	double sumf;

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (edgey[j * width + i] > 0) {
				// Median filter
				int count = 0;
				for (int k = 0; k < fsize; k++) {
					for (int l = 0; l < fsize; l++) {
						int xIdx = i + l;
						int yIdx = j + k;
						if (xIdx >= 0 && xIdx < width && yIdx >= 0 && yIdx < height) {
							window[count++] = py[yIdx * pwidth + xIdx];
						}
					}
				}
				y3[j * width + i] = median(window, count);
			}
			else {
				// Gaussian filter
				sumf = 0;
				for (int k = 0; k < fsize; k++) {
					for (int l = 0; l < fsize; l++) {
						sumf += gFilter[k * fsize + l] * py[(j + k) * pwidth + (i + l)];
					}
				}
				y3[j * width + i] = sumf;
			}
		}
	}

	free(window);
}


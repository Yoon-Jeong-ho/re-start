#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<windows.h>

#define PI 3.141592
double threshold=0;

void histo(int height,int width,double* y,int size, int stride, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);
void CumulativeHisto(int height, int width, double* y, int size, int stride, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);

void GammaOut(double*, double, BITMAPFILEHEADER, BITMAPINFOHEADER);
void DPCMEncoder(double*, int *,int , BITMAPFILEHEADER, BITMAPINFOHEADER);
void write_matrix_to_file(const char* filename, int* matrix, int height, int width);

void DPCMDecoder(double* out, int* prsy, int q, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);
void read_matrix_from_file(const char* filename, int* matrix, int rows, int cols);

void applyPadding(double* paddedImg, int height, int width, int padding, double* origImg);
void applyPaddingWithAverage(double* paddedImg, int height, int width, int padding, double* origImg);
void getPadding(double* py, int height, int width, int padding, int pheight, int pwidth, double* y2);

void calFilter(double* y3, double* py, int fsize, double* filter, int height, int width, int pwidth);
double median(double* arr, int size);
void calMedianFilter(double* y3, double* py, int fsize, int height, int width, int pwidth);
void bilateralFilter(double* paddedImg, double* outputImg, int width, int height, int pwidth, int pheight, int d, double sigmaColor, double sigmaSpace);

void getQulity(double* y, double* y3, int width, int height, int bitCnt);

void downsampling(int raito, double* org, double* dws, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);
void averageDownsampling(int ratio, double* org, double* dws, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);

void upSp(int ratio, double* org, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* upy);
void upsampling(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* upy);
void bilinearUpsampling(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* upy);
void bilinearUpsample(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* upy);
void nTapInterpolation(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, int n, double* upy);

void makeOutFile(BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, char* fileName, double* y);
void GammaOut(double* y, double g, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);

void Rotation(double* y, int width, int height,double theta, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);
void edgeMap(double* y, int width, int height, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo,double *edgey);
void sobelEdgeMap(double* y, int width, int height, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* edgey);

int main() {
	BITMAPFILEHEADER bmpFile, bmpFile2;
	BITMAPINFOHEADER bmpInfo, bmpInfo2;
	FILE* inputFile = NULL, * inputFile2 = NULL;
	//inputFile = fopen("data/AICenterY.bmp", "rb"); // 원본 영상
	inputFile = fopen("reconEncY.bmp", "rb"); // 원본 영상
	inputFile2 = fopen("reconDecY.bmp", "rb"); // 노이즈 영상

	//inputFile2 = fopen("data/AICenterY.bmp", "rb"); // 노이즈 영상
		
	fread(&bmpFile, sizeof(BITMAPFILEHEADER), 1, inputFile);
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, inputFile);
	fread(&bmpFile2, sizeof(BITMAPFILEHEADER), 1, inputFile2);
	fread(&bmpInfo2, sizeof(BITMAPINFOHEADER), 1, inputFile2);
	
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage, bitCnt = bmpInfo.biBitCount, stride = (((bitCnt / 8) * width) + 3) / 4 * 4,max;
	int width2 = bmpInfo2.biWidth, height2 = bmpInfo2.biHeight, size2 = bmpInfo2.biSizeImage, bitCnt2 = bmpInfo2.biBitCount, stride2 = (((bitCnt2 / 8) * width2) + 3) / 4 * 4;
	
	double *y,*y2,mse=0,psnr=0,*edgey;
	y = (double*)calloc(width * height, sizeof(double));
	y2 = (double*)calloc(width * height, sizeof(double));
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
	fread(inputImg2, sizeof(unsigned char), size, inputFile2);

	// input 
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			y[j * width + i] = inputImg[j * stride + 3 * i ];
			//y[j * width + i] = 0.299 * inputImg[j * stride + 3 * i + 2] + 0.587 * inputImg[j * stride + 3 * i + 1] + 0.114 * inputImg[j * stride + 3 * i + 0];
			//y2[j * width + i] = inputImg2[j * stride + 3 * i ];
		}
	}
	for (int j = 0; j < height2; j++) {
		for (int i = 0; i < width2; i++) {
			y2[j * width2 + i] = inputImg2[j * stride2 + 3 * i];
		}
	}
	getQulity(y, y2, width, height, bitCnt);
	return 0;
	int* prsy, q = 20;
	prsy = (int*)calloc(width * height, sizeof(int));

	DPCMEncoder(y,prsy , q, bmpFile, bmpInfo);
	DPCMDecoder(y2, prsy, q, bmpFile, bmpInfo);
	return 0;

	// Algorithm
	
	// sampling
	int ratio = 4;
	double* dws,* upy;
	dws = (double*)calloc(width * height/ ratio / ratio, sizeof(double));
	//downsampling(ratio, y, dws, bmpFile, bmpInfo);
	//averageDownsampling(raito, y, dws, bmpFile, bmpInfo);
	
	upy = (double*)calloc(width * height * ratio * ratio, sizeof(double));

	
	free(dws);
	

	//padding
	int padding = 2, pwidth = width2 + padding * 2, pheight = height2 + padding * 2, psize = pwidth * pheight;
	double* py;
	py = (double*)calloc(pwidth * pheight, sizeof(double));
	
	//getPadding(py,height,width, padding, pheight, pwidth, y2);
	//applyPadding(py, height, width, padding, y2);
	applyPaddingWithAverage(py, height2, width2, padding, y2);
	

	// filter

	int fsize = padding*2+1;

	// mean filter
	double* filter;
	filter = (double*)calloc(fsize * fsize, sizeof(double));
	for (int i = 0; i < fsize * fsize; i++) filter[i] = 1.0 / (fsize * fsize);

	// Gussian Filter
	double G3filter[] = {1.0/16,2.0/16,1.0/16,2.0/16,4.0/16,2.0/16,1.0/16,2.0/16,1.0/16};
	double G5filter[] = {1/273.0, 4/ 273.0, 7/ 273.0, 4/ 273.0, 1/ 273.0, 4/ 273.0, 16/ 273.0, 26/ 273.0, 16/ 273.0, 4/ 273.0, 7/ 273.0, 26/ 273.0, 41/ 273.0, 26/ 273.0, 7/ 273.0, 4 / 273.0, 16 / 273.0, 26 / 273.0, 16 / 273.0, 4 / 273.0,1 / 273.0, 4 / 273.0, 7 / 273.0, 4 / 273.0, 1 / 273.0 };
	double* y3;
	y3 = (double*)calloc(width2 * height2, sizeof(double));
	//calFilter(y3,py, fsize, G5filter,height2,width2,pwidth);
	//calMedianFilter( y3,py,  fsize,  height2,  width2,  pwidth);
	bilateralFilter(py, y3, width2, height2, pwidth, pheight, 5, 75.0, 75.0);


	//edgeMap(y3, width, height, bmpFile, bmpInfo,edgey);
	//get Quality
	upSp(ratio, y3, bmpFile2, bmpInfo2, upy);
	sobelEdgeMap(upy, width, height, bmpFile, bmpInfo, edgey);
	

	getQulity(y, upy,width,height, bitCnt);
	
	//histo
	
	//histo(height, width, y, size2, stride2, bmpFile2, bmpInfo2);
	//CumulativeHisto(height, width, y, size, stride, bmpFile, bmpInfo);

	// output

	makeOutFile(bmpFile,  bmpInfo, "data/Output.bmp", upy);
	//GammaOut( y, 2.5, bmpFile,bmpInfo);
	//Rotation(y3, width,height, 30, bmpFile, bmpInfo);

	free(inputImg);
	free(inputImg2);

	free(y);
	free(y2);
	free(py);
	free(y3);
	free(edgey);
	fclose(inputFile);
	fclose(inputFile2);
	return 0; 
}



void getPadding(double* py, int height, int width, int padding, int pheight, int pwidth, double* y2){
// 일단 원본 값 집어넣기
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			py[(j + padding) * pwidth + (i + padding)] = y2[j * width + i];
		}
	}
	// 패딩 값 집어넣기
	//하
	for (int p = 0; p < padding; p++) {
		for (int i = 0; i < width; i++) {
			py[(p)*pwidth + (i + padding)] = y2[0 * width + i];
		}
	}
	//좌
	for (int p = 0; p < padding; p++) {
		for (int j = 0; j < height; j++) {
			py[(j + padding) * pwidth + p] = y2[j * width];
		}
	}
	//우
	for (int p = 0; p < padding; p++) {
		for (int j = 0; j < height; j++) {
			py[(j + padding) * pwidth + (width + padding) + p] = y2[(j + 1) * width - 1];
		}
	}

	//상
	for (int p = 0; p < padding; p++) {
		for (int i = 0; i < width; i++) {
			py[(p + width + padding) * pwidth + (i + padding)] = y2[(height - 1) * width + i];
		}
	}

	// 좌하 ( 0,0) ~ (padding-1,padding-1)
	for (int j = 0; j < padding; j++) {
		for (int i = 0; i < padding; i++) {
			py[(j)*pwidth + (i)] = y2[0 * width + 0];
		}
	}
	// 우하 (0,pwidth-1 -padding) ~ (padding-1,pwidth-1)
	for (int j = 0; j < padding; j++) {
		for (int i = 0; i < padding; i++) {
			py[(j)*pwidth + (width + padding + i)] = y2[1 * width - 1];
		}
	}
	// 좌상
	for (int j = 0; j < padding; j++) {
		for (int i = 0; i < padding; i++) {
			py[(height + padding + j) * pwidth + (i)] = y2[(height - 1) * width];
		}
	}
	//우상
	for (int j = 0; j < padding; j++) {
		for (int i = 0; i < padding; i++) {
			py[(height + padding + j) * pwidth + (width + padding + i)] = y2[(height)*width - 1];
		}
	}
}

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

void histo(int height, int width, double* y, int size,int stride, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo) {
	double* histogram;
	histogram = (double*)calloc(256, sizeof(double));

	// get Histogram
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			histogram[(unsigned char)(y[j * width + i] > 255 ? 255 : (y[j * width + i] < 0 ? 0 : y[j * width + i]))]++;
		}
	}
	// out Histogram
	double histoMax = 0;
	for (int i = 0; i < 256; i++) {
		if (histogram[i] > histoMax) histoMax = histogram[i];
	}
	for (int i = 0; i < 256; i++)histogram[i] = histogram[i] / histoMax * 450;
	unsigned char* outHisto;
	outHisto = (unsigned char*)calloc(512*512*3, sizeof(unsigned char));

	for (int j = 0; j < 512; j++) {
		for (int i = 0; i < 512; i++) {
			if (histogram[i / 2] > j) continue;
			outHisto[j * 512 * 3 + 3 * i + 0] = 255;
			outHisto[j * 512 * 3 + 3 * i + 1] = 255;
			outHisto[j * 512 * 3 + 3 * i + 2] = 255;
		}
	}
	FILE* outputHisto = fopen("OutHisto.bmp", "wb");

	bmpInfo.biWidth = 512;
	bmpInfo.biHeight = 512;
	bmpInfo.biSizeImage = 512*3*512;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 512 * 3 * 512;

	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputHisto);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputHisto);
	fwrite(outHisto, sizeof(unsigned char), 512 * 3 * 512, outputHisto);
	free(histogram);
	fclose(outputHisto);
	free(outHisto);
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
		if (histogram[i] > height * width * 0.98 ) {
			threshold = i;
			break;
		}
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

void getQulity(double* y, double* y3,int width,int height,int bitCnt) {
	double mse=0,max,psnr;
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
	psnr = mse != 0.0 ? 10.0 * log10(max * max / mse) : 99.99;
	printf("mse = %.2lf\npsnr = %.2lf\n", mse, psnr);
}

void applyPadding(double* paddedImg, int height, int width, int padding, double* origImg) {
	int pheight = height + 2 * padding;
	int pwidth = width + 2 * padding;

	// 원본 이미지 데이터를 중앙에 배치
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			paddedImg[(j + padding) * pwidth + (i + padding)] = origImg[j * width + i];
		}
	}

	// 상하좌우 패딩 적용
	for (int j = 0; j < pheight; j++) {
		for (int i = 0; i < pwidth; i++) {
			// 상단 패딩
			if (j < padding) {
				paddedImg[j * pwidth + i] = paddedImg[padding * pwidth + i];
			}
			// 하단 패딩
			if (j >= height + padding) {
				paddedImg[j * pwidth + i] = paddedImg[(height + padding - 1) * pwidth + i];
			}
			// 좌측 패딩
			if (i < padding) {
				paddedImg[j * pwidth + i] = paddedImg[j * pwidth + padding];
			}
			// 우측 패딩
			if (i >= width + padding) {
				paddedImg[j * pwidth + i] = paddedImg[j * pwidth + (width + padding - 1)];
			}
		}
	}
	// 상단 패딩 적용
	for (int p = 0; p < padding; p++) {
		for (int i = 0; i < pwidth; i++) {
			paddedImg[p * pwidth + i] = paddedImg[padding * pwidth + i];
		}
	}

	// 하단 패딩 적용
	for (int p = 0; p < padding; p++) {
		for (int i = 0; i < pwidth; i++) {
			paddedImg[(height + padding + p) * pwidth + i] = paddedImg[(height + padding - 1) * pwidth + i];
		}
	}

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



void downsampling(int ratio, double* org, double* dws, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo) {
	int width2 = bmpInfo.biWidth/ ratio, height2 = bmpInfo.biHeight / ratio, stride2 = (((bmpInfo.biBitCount/8)*width2)+3)/4*4,size2 = stride2*height2;
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight;

	for (int j = 0; j < height2; j++) {
		for (int i = 0; i < width2; i++) {
			dws[j * width2 + i] = org[(j* ratio)*width + i* ratio];
		}
	}
	bmpInfo.biWidth = width2;
	bmpInfo.biHeight = height2;
	bmpInfo.biSizeImage = size2;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size2;
	makeOutFile(bmpFile, bmpInfo, "OutDWS.bmp", dws);

}

void averageDownsampling(int ratio, double* org, double* dws, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo) {
	int width2 = bmpInfo.biWidth / ratio, height2 = bmpInfo.biHeight / ratio;
	int stride2 = (((bmpInfo.biBitCount / 8) * width2) + 3) / 4 * 4;
	int size2 = stride2 * height2;
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight;

	for (int j = 0; j < height2; j++) {
		for (int i = 0; i < width2; i++) {
			double sum = 0;
			int count = 0;
			// Compute the average of pixels in the block
			for (int y = 0; y < ratio; y++) {
				for (int x = 0; x < ratio; x++) {
					int ny = j * ratio + y;
					int nx = i * ratio + x;
					if (ny < height && nx < width) {
						sum += org[ny * width + nx];
						count++;
					}
				}
			}
			dws[j * width2 + i] = sum / count;  // Store the average in the downsampled image
		}
	}
	bmpInfo.biWidth = width2;
	bmpInfo.biHeight = height2;
	bmpInfo.biSizeImage = size2;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size2;
	makeOutFile(bmpFile, bmpInfo, "OutDWS.bmp", dws);
}

void upSp(int ratio, double* org, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* upy) {
	double* ups;
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight;
	//ups = (double*)calloc(width * height * ratio/2 * ratio/2, sizeof(double));
	ups = (double*)calloc(width * height * ratio  * ratio, sizeof(double));

	//upsampling(ratio/2, org, ups, bmpFile, bmpInfo,upy); // 25.23
	bilinearUpsample(ratio, org, ups, bmpFile, bmpInfo, upy); // 25.22
	//bilinearUpsampling(ratio/2, org, ups, bmpFile, bmpInfo, upy);//25.22
	//nTapInterpolation(ratio, org, ups, bmpFile, bmpInfo, 4, upy); // 25.19
	double* ups2;
	bmpInfo.biHeight = bmpInfo.biHeight * ratio / 2;
	bmpInfo.biWidth = bmpInfo.biWidth * ratio / 2;

	ups2 = (double*)calloc(width * height * ratio * ratio , sizeof(double));
	//upsampling(ratio / 2, ups, ups2, bmpFile, bmpInfo, upy);
	//bilinearUpsampling(ratio / 2, ups, ups2, bmpFile, bmpInfo, upy); //24.90
	free(ups);
}

void upsampling(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* upy) {
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight;
	int width2 = bmpInfo.biWidth * ratio, height2 = bmpInfo.biHeight * ratio;
	int stride2 = (((bmpInfo.biBitCount / 8) * width2) + 3) / 4 * 4, size2 = stride2 * height2;
	int nearestJ = 0, nearestI=0;
	for (int j = 0; j < height2; j++) {
		for (int i = 0; i < width2; i++) {
			nearestJ = j / ratio;
			nearestI = i / ratio;
			ups[j * width2 + i] = org[nearestJ * width + nearestI];
			upy[j * width2 + i] = ups[j * width2 + i];
		}
	}


	bmpInfo.biWidth = width2;
	bmpInfo.biHeight = height2;
	bmpInfo.biSizeImage = size2;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size2;
	makeOutFile(bmpFile, bmpInfo, "OutUPS.bmp", ups);


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
	int originalWidth = bmpInfo.biWidth, originalHeight = bmpInfo.biHeight;
	int upscaledWidth = originalWidth * ratio, upscaledHeight = originalHeight * ratio;
	int stride2 = (((bmpInfo.biBitCount / 8) * upscaledWidth) + 3) / 4 * 4, size2 = stride2 * upscaledHeight;

	for (int y = 0; y < upscaledHeight; y++) {
		for (int x = 0; x < upscaledWidth; x++) {
			float gx = ((float)x / (float)upscaledWidth) * (float)(originalWidth - 1);
			float gy = ((float)y / (float)upscaledHeight) * (float)(originalHeight - 1);
			int gxi = (int)gx;
			int gyi = (int)gy;

			double c00 = org[gyi * originalWidth + gxi];
			double c10 = org[gyi * originalWidth + (gxi + 1 < originalWidth ? gxi + 1 : gxi)];
			double c01 = org[(gyi + 1 < originalHeight ? gyi + 1 : gyi) * originalWidth + gxi];
			double c11 = org[(gyi + 1 < originalHeight ? gyi + 1 : gyi) * originalWidth + (gxi + 1 < originalWidth ? gxi + 1 : gxi)];

			double dx = gx - gxi;
			double dy = gy - gyi;

			double c0 = c00 * (1 - dx) + c10 * dx;
			double c1 = c01 * (1 - dx) + c11 * dx;
			double c = c0 * (1 - dy) + c1 * dy;

			ups[y * upscaledWidth + x] = c;
			upy[y * upscaledWidth + x] = ups[y * upscaledWidth + x];
		}
	}

	bmpInfo.biWidth = upscaledWidth;
	bmpInfo.biHeight = upscaledHeight;
	bmpInfo.biSizeImage = size2;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size2;
	makeOutFile(bmpFile, bmpInfo, "OutBiUPS.bmp", ups);
}


void nTapInterpolation(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, int n, double* upy) {
	int originalWidth = bmpInfo.biWidth, originalHeight = bmpInfo.biHeight;
	int upscaledWidth = originalWidth * ratio, upscaledHeight = originalHeight * ratio;
	int stride2 = (((bmpInfo.biBitCount / 8) * upscaledWidth) + 3) / 4 * 4, size2 = stride2 * upscaledHeight;

	// Example of n-TAP filter coefficients for 3-tap or 4-tap
	double* coefficients;
	if (n == 3) {
		double coeffs[3] = { 0.25, 0.5, 0.25 };  // Simple averaging coefficients for 3-tap
		coefficients = coeffs;
	}
	else if (n == 4) {
		double coeffs[4] = { -2.0/16, 10.0/16, 10.0/16, -2.0/16 }; // Simple averaging coefficients for 4-tap
		coefficients = coeffs;
	}
	else {
		printf("Unsupported n-tap value: %d\n", n);
		return;
	}

	for (int j = 0; j < upscaledHeight; j++) {
		for (int i = 0; i < upscaledWidth; i++) {
			float x = (float)i / ratio;
			float y = (float)j / ratio;

			double sum = 0;
			for (int k = 0; k < n; k++) {
				int x1 = fmax(0, (int)x - k + 1);
				int y1 = fmax(0, (int)y - k + 1);
				int x2 = fmin(originalWidth - 1, (int)x + k);
				int y2 = fmin(originalHeight - 1, (int)y + k);

				sum += org[y1 * originalWidth + x1] * coefficients[k];
				sum += org[y2 * originalWidth + x2] * coefficients[k];
			}

			ups[j * upscaledWidth + i] = sum/2;
			upy[j * upscaledWidth + i] = ups[j * upscaledWidth + i];
		}
	}

	bmpInfo.biWidth = upscaledWidth;
	bmpInfo.biHeight = upscaledHeight;
	bmpInfo.biSizeImage = size2;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size2;
	makeOutFile(bmpFile, bmpInfo, "OutUPS.bmp", ups);
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
					int xIdx = i + l ;
					int yIdx = j + k ;
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

void GammaOut(double* y, double g, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo) {
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage;
	double* gy;
	gy = (double*)calloc(width * height, sizeof(double));

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			gy[j * width + i] = 255 * pow(y[j * width + i] / 255.0, 1/g);
		}
	}
	makeOutFile(bmpFile, bmpInfo, "gammaOut.bmp", gy);
	free(gy);

}

void DPCMEncoder(double* org, int* prsy, int q, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo) {
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage;
	double* pe, *rs;
	pe = (double*)calloc(width * height, sizeof(double));
	rs = (double*)calloc(width * height, sizeof(double));
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (i == 0) {
				pe[j * width + i] = org[j * width + i] - 128;
				prsy[j * width + i] = (int)(pe[j * width + i] / q);
				rs[j * width + i] = 128 + prsy[j * width + i] * q;
			}
			else {
				pe[j * width + i] = org[j * width + i] - rs[j * width + i - 1];
				prsy[j * width + i] = (int)(pe[j * width + i] / q);
				rs[j * width + i] = rs[j * width + i - 1] + prsy[j * width + i] * q;
			}
			
		}
	}
	makeOutFile(bmpFile, bmpInfo, "DPCMEncoder.bmp", rs);
	write_matrix_to_file("encoder.txt", prsy, height, width);
	free(rs);
	free(pe);
}

void write_matrix_to_file(const char* filename, int *matrix, int height, int width) {
	FILE* file = fopen(filename, "w");
	printf("start encoding\n");
	if (file == NULL) {
		perror("파일 열기 실패");
		return;
	}

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			fprintf(file, "%d ", matrix[j * width + i]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}

void DPCMDecoder(double* out, int* prsy, int q, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo) {
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage;
	double * rs;
	printf("start decoding\n");
	rs = (double*)calloc(width * height, sizeof(double));
	read_matrix_from_file("encoder.txt", prsy, height, width);
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (i == 0) {
				rs[j * width + i] = 128 + prsy[j * width + i] * q;
			}
			else {
				rs[j * width + i] = rs[j * width + i -1] + prsy[j * width + i] * q;

			}

		}
	}
	makeOutFile(bmpFile, bmpInfo, "DPCMDecoder.bmp", rs);
	free(rs);

}

void read_matrix_from_file(const char* filename, int *matrix, int height, int width) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		perror("파일 열기 실패");
		return;
	}
	printf("%d  %d \n", width,height);
	for (int j = 0; j < height; j++) {
		printf("%d ", j);
		for (int i = 0; i < width; i++) {
			fscanf(file, "%d", &matrix[j * width + i]);
			
		}
		
	}

	fclose(file);
}

void Rotation(double* y, int width, int height, double theta, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo) {
	theta = theta / 180 * PI;
	double* gy;
	gy = (double*)calloc(width * height, sizeof(double));

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			int x2, y2;
			x2 = (int)(cos(theta) * (i-width/2) - sin(theta) * (j-height/2) + width/2 );
			y2 = (int)(sin(theta) * (i - width / 2) + cos(theta) * (j - height / 2)+ height/2 );
			if (x2>=0 && x2 < width && y2 >= 0 && y2 < height) gy[y2 * width + x2] = y[j * width + i];

		}
	}
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (gy[j * width + i] == 0) {
				if (i + 1 == width && gy[j * width + i - 1] != 0)gy[j * width + i] = gy[j * width + i - 1];
				else if (i + 1 != width && gy[j * width + i + 1] != 0) gy[j * width + i] = gy[j * width + i +1];
				
			}
		}
	}
	makeOutFile(bmpFile, bmpInfo, "rotateOut.bmp", gy);
	free(gy);
}

void edgeMap(double* y, int width, int height, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* edgey) {
	//padding
	int padding = 2, pwidth = width + padding * 2, pheight = height + padding * 2, psize = pwidth * pheight;
	double* py, * xy, * yy, * outy, filter[] = {-1,0,1},sumf = 0;
	py = (double*)calloc(pwidth * pheight, sizeof(double));
	xy = (double*)calloc(width * height, sizeof(double));
	yy = (double*)calloc(width * height, sizeof(double));
	outy = (double*)calloc(width * height, sizeof(double));

	//getPadding(py,height,width, padding, pheight, pwidth, y2);
	//applyPadding(py, height, width, padding, y2);
	applyPaddingWithAverage(py, height, width, padding, y);

	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			sumf = 0;
			for (int k = 0; k < 3; k++) {
				sumf += filter[k] * py[(j) * pwidth + (i + k)];
			}
			xy[j * width + i] = sumf;

		}
	}
	makeOutFile(bmpFile, bmpInfo, "xEdgeOut.bmp", xy);
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			sumf = 0;
			for (int k = 0; k < 3; k++) {
				sumf += filter[k] * py[(j+k)*pwidth + (i)];
			}
			yy[j * width + i] = sumf;

		}
	}
	makeOutFile(bmpFile, bmpInfo, "yEdgeOut.bmp", yy);
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			outy[j * width + i] = sqrt(xy[j * width + i]* xy[j * width + i]+yy[j * width + i]*yy[j * width + i]);
		}
	}

	CumulativeHisto(height, width, outy, bmpInfo.biSizeImage, (((bmpInfo.biBitCount / 8) * width) + 3) / 4 * 4, bmpFile, bmpInfo);
	printf("threshold= %f\n", threshold);
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (outy[j * width + i] > threshold) edgey[j * width + i] = 254;
		}
	}
	makeOutFile(bmpFile, bmpInfo, "EdgeOut.bmp", outy);
	makeOutFile(bmpFile, bmpInfo, "thresholdEdge.bmp", edgey);
	free(py);
	free(xy);
	free(yy);
	free(outy);

}

void sobelEdgeMap(double* y, int width, int height, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* edgey) {
	//padding
	int padding = 2, pwidth = width + padding * 2, pheight = height + padding * 2, psize = pwidth * pheight;
	double* py, * xy, * yy, * outy, sumf = 0;

	py = (double*)calloc(pwidth * pheight, sizeof(double));
	xy = (double*)calloc(width * height, sizeof(double));
	yy = (double*)calloc(width * height, sizeof(double));
	outy = (double*)calloc(width * height, sizeof(double));
	int fsize = padding*2+1;

	double* xfilter,* yfilter;
	xfilter = (double*)calloc(fsize * fsize, sizeof(double));
	yfilter = (double*)calloc(fsize * fsize, sizeof(double));
	double xco, yco;
	for (int i = 0; i < fsize; i++) {
		for (int j = 0; j < fsize; j++) {
			xco = (i - padding);
			yco = (j - padding);
			if (xco ==0 && yco == 0) {
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
	printf("threshold= %f\n", threshold);
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
	int radius = d / 2;
	double sigmaColor2 = sigmaColor * sigmaColor;
	double sigmaSpace2 = sigmaSpace * sigmaSpace;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			double iFiltered = 0;
			double wP = 0;
			double iValue = paddedImg[(y + radius) * pwidth + (x + radius)];

			for (int dy = -radius; dy <= radius; dy++) {
				for (int dx = -radius; dx <= radius; dx++) {
					int ny = y + radius + dy;
					int nx = x + radius + dx;
					double nValue = paddedImg[ny * pwidth + nx];
					double spatialDist = dx * dx + dy * dy;
					double colorDist = (iValue - nValue) * (iValue - nValue);
					double weight = exp(-(spatialDist / (2 * sigmaSpace2) + colorDist / (2 * sigmaColor2)));
					iFiltered += nValue * weight;
					wP += weight;
				}
			}
			outputImg[y * width + x] = iFiltered / wP;
		}
	}
}
#define _CRT_SECURE_NO_WARNINGS
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<windows.h>

double threshold = 0;


void applyPaddingWithAverage(double* paddedImg, int height, int width, int padding, double* origImg);

void calFilter(double* y3, double* py, int fsize, double* filter, int height, int width, int pwidth);
double median(double* arr, int size);
void calMedianFilter(double* y3, double* py, int fsize, int height, int width, int pwidth);
void bilateralFilter(double* paddedImg, double* outputImg, int width, int height, int pwidth, int pheight, int d, double sigmaColor, double sigmaSpace);
void hybridFilter(double* y3, double* py, double* edgey, int fsize, int height, int width, int pwidth, double* gFilter);
void generateGaussianFilter(int n, double sigma, double filter[]);

void upSp(int ratio, double* org, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* upy);
void nTapInterpolation(int ratio, double* org, double* ups, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, int n, double* upy);

void makeOutFile(BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, char* fileName, double* y);

void sobelEdgeMap(double* y, int width, int height, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* edgey);

void CumulativeHisto(int height, int width, double* y, int size, int stride, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo);

int main(int argc, char* argv[]) {
	BITMAPFILEHEADER bmpFile;
	BITMAPINFOHEADER bmpInfo;
	FILE* inputFile = NULL;
	inputFile = fopen(argv[1], "rb");


	fread(&bmpFile, sizeof(BITMAPFILEHEADER), 1, inputFile);
	fread(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, inputFile);

	// 넓이, 높이 값 받기
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage, bitCnt = bmpInfo.biBitCount, stride = (((bitCnt / 8) * width) + 3) / 4 * 4;
	int ratio = 4;
	int width2 = width * ratio, height2 = height * ratio, stride2 = (((bitCnt / 8) * width2) + 3) / 4 * 4, size2 = height2 * stride2;

	// 이미지 저장 공간 
	double* y;
	y = (double*)calloc(width * height, sizeof(double));

	// 이미지 데이터 받아서 저장하기
	unsigned char* inputImg = NULL;
	inputImg = (unsigned char*)calloc(size, sizeof(unsigned char));
	fread(inputImg, sizeof(unsigned char), size, inputFile);

	// input 
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			y[j * width + i] = inputImg[j * stride + 3 * i];
		}
	}




	//padding
	int padding = 2, pwidth = width + padding * 2, pheight = height + padding * 2, psize = pwidth * pheight;
	double* py;
	py = (double*)calloc(pwidth * pheight, sizeof(double));
	applyPaddingWithAverage(py, height, width, padding, y);

	// 필터 결과값 저장 공간
	double* y3;
	y3 = (double*)calloc(width * height, sizeof(double));

	// filter
	int fsize = padding * 2 + 1;

	// Gussian Filter
	double G5filter[] = { 1 / 273.0, 4 / 273.0, 7 / 273.0, 4 / 273.0, 1 / 273.0, 4 / 273.0, 16 / 273.0, 26 / 273.0, 16 / 273.0, 4 / 273.0, 7 / 273.0, 26 / 273.0, 41 / 273.0, 26 / 273.0, 7 / 273.0, 4 / 273.0, 16 / 273.0, 26 / 273.0, 16 / 273.0, 4 / 273.0,1 / 273.0, 4 / 273.0, 7 / 273.0, 4 / 273.0, 1 / 273.0 };

	// 양방향 필터 
	bilateralFilter(py, y3, width, height, pwidth, pheight, fsize, 50.0, 10); // 양방향 필터 


	// 최종 데이터 저장 공간
	double* upy;
	upy = (double*)calloc(width2 * height2, sizeof(double));

	// 업스케일링
	upSp(ratio, y3, bmpFile, bmpInfo, upy); // 업스케일링 

	// 업스케일링에 맞춰 헤드 바꿔주기
	bmpInfo.biWidth = height2;
	bmpInfo.biHeight = width2;
	bmpInfo.biSizeImage = height2 * stride2;
	bmpFile.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size2;

	double* edgey2;
	edgey2 = (double*)calloc(width2 * height2, sizeof(double));
	int padding2 = 2, pwidth2 = width2 + padding2 * 2, pheight2 = height2 + padding2 * 2, psize2 = pwidth2 * pheight2;
	double* py2;
	py2 = (double*)calloc(pwidth2 * pheight2, sizeof(double));
	int fsize2 = padding2 * 2 + 1;

	// 양방향 필터
	applyPaddingWithAverage(py2, height2, width2, padding2, upy);
	bilateralFilter(py2, upy, width2, height2, pwidth2, pheight2, fsize2, 60.0, 10.0);

	// edge에 따른 필터 적용
	applyPaddingWithAverage(py2, height2, width2, padding2, upy);
	sobelEdgeMap(upy, width2, height2, bmpFile, bmpInfo, edgey2);
	hybridFilter(upy, py2, edgey2, fsize2, height2, width2, pwidth2, G5filter);


	int padding3 = 1, pwidth3 = width2 + padding3 * 2, pheight3 = height2 + padding3 * 2, psize3 = pwidth3 * pheight3;
	double* py3;
	py3 = (double*)calloc(pwidth3 * pheight3, sizeof(double));
	int fsize3 = padding3 * 2 + 1;


	double* gfilter;
	gfilter = (double*)calloc(fsize3 * fsize3, sizeof(double));

	// edge에 따른 필터 1회 더 적용 
	generateGaussianFilter(fsize3, fsize3 / 6.0, gfilter);
	applyPaddingWithAverage(py3, height2, width2, padding3, upy);
	sobelEdgeMap(upy, width2, height2, bmpFile, bmpInfo, edgey2);
	hybridFilter(upy, py3, edgey2, fsize3, height2, width2, pwidth3, gfilter);

	// median 필터 적용 
	applyPaddingWithAverage(py2, height2, width2, padding2, upy);
	calMedianFilter(upy, py2, fsize2, height2, width2, pwidth2);

	//사진 출력 
	makeOutFile(bmpFile, bmpInfo, "19011268.bmp", upy);

	//메모리 해제
	free(inputImg);
	free(y);
	free(py);
	free(y3);
	free(upy);
	free(edgey2);
	free(py2);
	free(py3);
	free(gfilter);
	fclose(inputFile);
	return 0;
}


void calFilter(double* y3, double* py, int fsize, double* filter, int height, int width, int pwidth) {
	double sumf = 0;

	//각 픽셀에 대해 필터 적용 
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			sumf = 0;
			// 필터 크기만큼 주변 픽셀 더하기 
			for (int k = 0; k < fsize; k++) {
				for (int l = 0; l < fsize; l++) {
					sumf += filter[k * fsize + l] * py[(j + k) * pwidth + (i + l)];
				}
			}
			// 필터 계산 내용 저장 
			y3[j * width + i] = sumf;
		}
	}
}

//원래는 히스토그램까지 출력하지만 여기선 필요 없으니 임계값만 정한다.
void CumulativeHisto(int height, int width, double* y, int size, int stride, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo) {
	double* histogram;
	histogram = (double*)calloc(256, sizeof(double));

	// get Histogram
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			histogram[(unsigned char)(y[j * width + i] > 255 ? 255 : (y[j * width + i] < 0 ? 0 : y[j * width + i]))]++;
		}
	}

	// 누적 히스토그램 계산 
	for (int i = 0; i < 255; i++) {
		histogram[i + 1] += histogram[i];
	}

	// 임계값 결정 
	for (int i = 0; i < 255; i++) {
		if (histogram[i] > height * width * 0.985) {
			threshold = i;
			break;
		}
		if (i == 254) threshold = 254;
	}


	free(histogram);
}

// 평균 패딩
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


// 업셈플링 정하는 곳
void upSp(int ratio, double* org, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* upy) {
	double* ups;
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight;

	ups = (double*)calloc(width * height * ratio * ratio, sizeof(double));

	// n - tap 보간법 적용 
	nTapInterpolation(ratio, org, ups, bmpFile, bmpInfo, 4, upy);

	free(ups);
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
			ups[j * upscaledWidth + i] = sum / 2.0;
			upy[j * upscaledWidth + i] = ups[j * upscaledWidth + i];
		}
	}

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

//출력 파일
void makeOutFile(BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, char* fileName, double* y) {
	int width = bmpInfo.biWidth, height = bmpInfo.biHeight, size = bmpInfo.biSizeImage, bitCnt = bmpInfo.biBitCount, stride = (((bitCnt / 8) * width) + 3) / 4 * 4;
	unsigned char* outputImg = NULL;
	outputImg = (unsigned char*)calloc(size, sizeof(unsigned char));
	// 값 집어넣어 주기
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			//255 넘지 않게, RGB칸 모두 넣어주기
			for (int k = 0; k < 3; k++) outputImg[j * stride + 3 * i + k] = (unsigned char)(y[j * width + i] > 255 ? 255 : (y[j * width + i] < 0 ? 0 : y[j * width + i]));
		}
	}
	// 파일 만드는 곳
	FILE* outputFile = fopen(fileName, "wb");
	fwrite(&bmpFile, sizeof(BITMAPFILEHEADER), 1, outputFile);
	fwrite(&bmpInfo, sizeof(BITMAPINFOHEADER), 1, outputFile);
	fwrite(outputImg, sizeof(unsigned char), size, outputFile);
	fclose(outputFile);
	free(outputImg);
}

// 소벨 엣지 멥을 통해 엣지 멥 가져오기
void sobelEdgeMap(double* y, int width, int height, BITMAPFILEHEADER bmpFile, BITMAPINFOHEADER bmpInfo, double* edgey) {
	//padding
	int padding = 2, pwidth = width + padding * 2, pheight = height + padding * 2, psize = pwidth * pheight;
	double* py, * xy, * yy, * outy, sumf = 0;
	
	// 값 저장 공간
	py = (double*)calloc(pwidth * pheight, sizeof(double));
	xy = (double*)calloc(width * height, sizeof(double));
	yy = (double*)calloc(width * height, sizeof(double));
	outy = (double*)calloc(width * height, sizeof(double));
	int fsize = padding * 2 + 1;

	// 필터 저장 공간
	double* xfilter, * yfilter;
	xfilter = (double*)calloc(fsize * fsize, sizeof(double));
	yfilter = (double*)calloc(fsize * fsize, sizeof(double));
	double xco, yco;

	//소벨 필터 만들기
	for (int i = 0; i < fsize; i++) {
		for (int j = 0; j < fsize; j++) {
			xco = (i - padding);
			yco = (j - padding);
			// 중앙을 기준으로 값 계산
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

	// 패딩 만들기
	applyPaddingWithAverage(py, height, width, padding, y);

	// 소벨 필터 계산 
	calFilter(xy, py, fsize, xfilter, height, width, pwidth);
	calFilter(yy, py, fsize, yfilter, height, width, pwidth);
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			outy[j * width + i] = sqrt(xy[j * width + i] * xy[j * width + i] + yy[j * width + i] * yy[j * width + i]);
		}
	}

	// 히스토그램 누적 계산을 통한 임계치 구하기 
	CumulativeHisto(height, width, outy, bmpInfo.biSizeImage, (((bmpInfo.biBitCount / 8) * width) + 3) / 4 * 4, bmpFile, bmpInfo);
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (outy[j * width + i] > threshold) edgey[j * width + i] = 254;
		}
	}

	//메모리 해제
	free(py);
	free(xy);
	free(yy);
	free(outy);
	free(xfilter);
	free(yfilter);

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

	// edge에는 미디안, edge가 아닌부분엔 가우시안 필터 적용 
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (edgey[j * width + i] > 0) {
				// Median filter 적용
				int count = 0;
				for (int k = 0; k < fsize; k++) {
					for (int l = 0; l < fsize; l++) {
						// 미디안 필터 부분과 똑같다.
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
				// Gaussian filter 적용 
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

void generateGaussianFilter(int n, double sigma, double filter[]) {
	double sum = 0.0;
	int half = n / 2;
	double pi = 3.14159265359;
	// Calculate the Gaussian filter
	for (int x = -half; x <= half; x++) {
		for (int y = -half; y <= half; y++) {
			filter[(x + half) * n + (y + half)] = (1 / (2 * pi * sigma * sigma)) * exp(-(x * x + y * y) / (2 * sigma * sigma));
			sum += filter[(x + half) * n + (y + half)];
		}
	}

	// Normalize the filter
	for (int i = 0; i < n * n; i++) {
		filter[i] /= sum;
	}
}

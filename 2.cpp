#include <opencv2/opencv.hpp> 
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	//입력 이미지 Road-and-house, Lena
	Mat image = imread("Road-and-house.jpg",cv::IMREAD_GRAYSCALE);
	int w = image.cols;
	int h = image.rows;
	imshow("image", image); //원본이미지

	/*1번*/
	//sobel filter 수평방향
	Mat sobelx;
	Sobel(image, sobelx, -1, 1, 0);
	imshow("sobelX", sobelx);
	//sobel filter 수평방향
	Mat sobely;
	Sobel(image, sobely, -1, 0, 1);
	imshow("sobelY", sobely);
	//sobel filter 수평방향
	Mat sobel;
	sobel = abs(sobelx) + abs(sobely); 
	imshow("sobelXY", sobel);
	waitKey(0);

	/*2번*/
	Mat median33, median55;
	//3x3 미디언필터
	medianBlur(image, median33, 3);
	imshow("median33", median33);
	//5x5 미디언필터
	medianBlur(image, median55, 5);
	imshow("median55", median55);
	waitKey(0);

	/*3번*/
	Mat ave33(h, w, CV_8UC1), ave55(h, w, CV_8UC1);
	Mat border1, border2;
	//경계선 처리 문제 해결 방법 : BORDER_DEFAULT 대각선 매칭
	copyMakeBorder(image, border1, 1, 1, 1, 1, BORDER_DEFAULT);
	copyMakeBorder(image, border2, 2, 2, 2, 2, BORDER_DEFAULT);

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {

			//3x3 평균필터 연산
			int sum = 0;
			for (int j = -1; j <= 1; j++) {
				for (int i = -1; i <= 1; i++) {
					int p = border1.at<uchar>(y + 1 + j, x + 1 + i);
					sum = sum + p * 1 / 9;
				}
			}
			ave33.at<uchar>(y, x) = sum;

			//5x5 평균필터 연산
			sum = 0;
			for (int j = -2; j <= 2; j++) {
				for (int i = -2; i <= 2; i++) {
					int p = border2.at<uchar>(y + 2 + j, x + 2 + i);
					sum = sum + p * 1 / 25;
				}
			}
			ave55.at<uchar>(y, x) = sum;
		}
	}

	imshow("ave33", ave33); //3x3 평균필터
	imshow("ave55", ave55); //5x5 평균필터
	waitKey(0);
}
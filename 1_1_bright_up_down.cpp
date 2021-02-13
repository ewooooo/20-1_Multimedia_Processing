#include <opencv2/opencv.hpp> 
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	
	Mat image = imread("D:\\OneDrive - kyonggi.ac.kr\\2020-1\\멀티미디어처리기술\\2주 과제\\Cameraman.jpg",cv::IMREAD_GRAYSCALE);
	int w = image.cols;
	int h = image.rows;
	imshow("image", image);

	Mat brightUp20(h,w, CV_8UC1), brightDown50(h, w, CV_8UC1);
	//CV_8UC1 :　0~255 GrayScale포맷 

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int up = image.at<uchar>(y, x) + 20;
			int down = image.at<uchar>(y, x) - 50;
			if (up > 255)
				up = 255;
			brightUp20.at<uchar>(y, x) = up;
			if (down < 0)
				down = 0;
			brightDown50.at<uchar>(y, x) = down;
		}
	}
	imshow("brightUP20", brightUp20);
	imshow("brightDown50", brightDown50);
	waitKey(0);
}
#include <opencv2/opencv.hpp> 
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	Mat image = imread("Cameraman.jpg",cv::IMREAD_GRAYSCALE);
	int w = image.cols;
	int h = image.rows;

	Mat invertImage(h, w, CV_8UC1);
	int max=0;
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int value = image.at<uchar>(y, x);
			if (max < value)
				max = value;
		}
	}
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int value = image.at<uchar>(y, x);
			invertImage.at<uchar>(y, x) = max - value;
		}
	}
	imshow("invertImage", invertImage);
	waitKey(0);
}
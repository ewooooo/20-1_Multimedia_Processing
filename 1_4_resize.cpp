#include <opencv2/opencv.hpp> 
#include <iostream>

using namespace cv;
using namespace std;

int main() {
	Mat myImage = imread("myImage.jpg");
	int w = myImage.cols;
	int h = myImage.rows;
	imshow("myImage", myImage);

	Rect rectROI(200,230,130,150);	//x,y,w,h
	Mat imageROI = myImage(rectROI);
	imshow("imageROI", imageROI);

	Mat zoomImage;
	resize(imageROI, zoomImage, Size(), 2, 2, CV_INTER_LINEAR);
	//INTER_LINEAR : bilinear interpolation

	imshow("zoomImage", zoomImage);
	waitKey(0);
}
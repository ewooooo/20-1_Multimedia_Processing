#include <opencv2/opencv.hpp> 
#include <iostream>
using namespace cv;
using namespace std;

#define thresholdValue 60

int main() {
	
	Mat src = imread("D:\\OneDrive - kyonggi.ac.kr\\2020-1\\멀티미디어처리기술\\6주 과제\\blocks_color.jpg");
	imshow("src", src);
	cvtColor(src, src, COLOR_RGBA2GRAY, 0);

	Mat dst;
	Canny(src, dst, 50, 150, 3);
	imshow("dst", dst);
	// Copy edges to the images that will display the results in BGR
	Mat cdst;
	cvtColor(src, cdst, COLOR_GRAY2BGR);
	Mat cdstP = cdst.clone();
	// Standard Hough Line Transform
	vector<Vec2f> lines; // will hold the results of the detection
	HoughLines(dst, lines, 1, CV_PI / 180, thresholdValue, 0, 0); // runs the actual detection
	// Draw the lines
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, LINE_AA);
	}
	// Probabilistic Line Transform
	vector<Vec4i> linesP; // will hold the results of the detection
	HoughLinesP(dst, linesP, 1, CV_PI / 180, thresholdValue, 50, 10); // runs the actual detection
	// Draw the lines
	for (size_t i = 0; i < linesP.size(); i++)
	{
		Vec4i l = linesP[i];
		line(cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, LINE_AA);
	}
	// Show results
	imshow("Source", src);
	imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
	imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);
	// Wait and Exit
	waitKey();
	return 0;
}
#include <opencv2/opencv.hpp> 
#include <iostream>

using namespace cv;
using namespace std;

vector<vector<Point>> C;

Point DELTA(Point x, int d) {
	if (d == 0)
		return Point(x.x + 1, x.y);
	else if (d == 1)
		return Point(x.x, x.y + 1);
	else if (d == 2)
		return Point(x.x-1, x.y);
	else if (d == 3)
		return Point(x.x, x.y - 1);
}

Point FindNextPoint(Point x, int* d, Mat I, int** LM) {

	for (int i = 0; i < 3; i++) {
		Point x1 = DELTA(x, *d);
		if ((int)I.at<uchar>(x1.y, x1.x) == 0) {
			LM[x1.y][x1.x] = -1;
			*d = (*d + 1) % 4;
		}
		else {
			return x1;
		}
	}
	return x;
}


vector<int> TraceContour(Point Xs, int ds, int Lc, Mat I, int** LM) {
	int dnext = ds;
	Point XT = FindNextPoint(Xs, &dnext, I, LM);
	vector<Point> c;
	c.push_back(XT);
	vector<int> chainCode;
	chainCode.push_back(dnext);

	Point Xp = Xs;
	Point Xc = XT;
	bool done = (Xs == XT);
	while (!done) {
		LM[Xc.y][Xc.x] = Lc;

		int dsearch = (dnext + 3) % 4;
		Point Xn = FindNextPoint(Xc, &dsearch, I, LM);
		dnext = dsearch;
		Xp = Xc;
		Xc = Xn;
		done = (Xp == Xs);
		if (!done) {
			c.push_back(Xn);
			chainCode.push_back(dnext);
		}
	}
	C.push_back(c);
	return chainCode;
}

int main() {

	Mat image0 = imread("0.jpg", IMREAD_GRAYSCALE);
	Mat image8 = imread("8.jpg", IMREAD_GRAYSCALE);

	Mat image;

	threshold(image0, image, 50, 255, THRESH_BINARY_INV);

	imshow("image", image);

	int w = image.cols;
	int h = image.rows;

	vector<vector<int>> ChainCode;
	int** LM;
	LM = new int* [h];
	for (int i = 0; i < h; i++)
		LM[i] = new int[w];

	for (int v = 0; v < h; v++) 
		for (int u = 0; u < w; u++) 
			LM[v][u] = 0;

	int R = 0;

	for (int v = 0; v < h; v++) {
		int Lk = 0;
		for (int u = 0; u < w; u++) {
			if ((int)image.at<uchar>(v, u) != 0) {
				if (Lk != 0) {
					LM[v][u] = Lk;
				}
				else {
					Lk = LM[v][u];
					if (Lk == 0) {
						R = R + 1;
						Lk = R;
						Point Xs(u, v);
						ChainCode.push_back(TraceContour(Xs, 0, Lk, image, LM));
						LM[v][u] = Lk;
					}
				}
			}
			else {
				if (Lk != 0) {
					if (LM[v][u] == 0) {
						Point Xs(u - 1, v);
						ChainCode.push_back(TraceContour(Xs, 1, Lk, image, LM));
					}
					Lk = 0;
				}
			}
		}
	}
	Mat test = Mat::zeros(h, w, CV_8UC1);

	for (int idx = 0; idx < C.size(); idx++) {
		cout << "Contour Start Point : " << C[idx][0]<< endl;
		cout << "Contour second Point : " << C[idx][1] << endl;
		for (int jdx = 0; jdx < C[idx].size(); jdx++) {
			test.at<uchar>(C[idx][jdx].y, C[idx][jdx].x) = 255;
		}
		cout <<endl<< "ChainCode" << endl;
		for (int jdx = 0; jdx < ChainCode[idx].size(); jdx++) {
			cout << ChainCode[idx][jdx];
		}
		cout << endl << endl << endl;
	}

	imshow("Test", test);

	waitKey(0);
}
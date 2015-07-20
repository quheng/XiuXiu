#ifndef TRANPENCIL
#define TRANPENCIL

#include <stdio.h>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
using namespace std;
using namespace cv;

void TranPencil(Mat &img){
	img=img.clone();
	int width = img.cols;
	int heigh = img.rows;
	if (img.empty()) cout << "TranReAncient Error!";
	Mat gray0, gray1;
	cvtColor(img, gray0, CV_BGR2GRAY);
	addWeighted(gray0, -1, NULL, 0, 255, gray1);
	GaussianBlur(gray1, gray1, Size(15, 15), 0);
	for (int y = 0; y<heigh; y++){
		uchar* P0 = gray0.ptr<uchar>(y);
		uchar* P1 = gray1.ptr<uchar>(y);
		uchar* P = img.ptr<uchar>(y);
		for (int x = 0; x<width; x++){
			int tmp0 = P0[x];
			int tmp1 = P1[x];
			P[3 * x] = (uchar)min((int)fabs((float)((tmp0 + (tmp0*tmp1) / (256 - tmp1)) - 10)), 255);
			P[3 * x + 1] = P[3 * x];
			P[3 * x + 2] = P[3 * x];
		}
	}
	cvtColor(img, gray0, CV_BGR2GRAY);
	equalizeHist(gray0, gray0);
	for (int y = 0; y<heigh; y++){
		uchar* P0 = gray0.ptr<uchar>(y);
		uchar* P = img.ptr<uchar>(y);
		for (int x = 0; x<width; x++){
			int tmp0 = P0[x];
			P[3 * x] = (uchar)tmp0;
			P[3 * x + 1] = P[3 * x];
			P[3 * x + 2] = P[3 * x];
		}
	}
	return;
}
#endif

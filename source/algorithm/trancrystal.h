#ifndef TRANCRYSTAL
#define TRANCRYSTAL

#include <stdio.h>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
using namespace std;
using namespace cv;

inline void TranCrystal(Mat &img){
	img=img.clone();
	int width = img.cols;
	int heigh = img.rows;
	if (img.empty()) cout << "TranCrystal Error!";
	for (int y = 0; y<heigh; y++){
		uchar* P = img.ptr<uchar>(y);
		for (int x = 0; x<width; x++){
			float B = P[3 * x];
			float G = P[3 * x + 1];
			float R = P[3 * x + 2];
			float newB = fabs(B-R-G)*3/2;
			float newG = fabs(G-R-B)*3/2;
			float newR = fabs(R-B-G)*3/2;
			if (newB<0) newB = 0;
			if (newB>255) newB = 255;
			if (newG<0) newG = 0;
			if (newG>255) newG = 255;
			if (newR<0) newR = 0;
			if (newR>255) newR = 255;
			P[3 * x] = (uchar)newB;
			P[3 * x + 1] = (uchar)newG;
			P[3 * x + 2] = (uchar)newR;
		}
	}
	return;
}
#endif
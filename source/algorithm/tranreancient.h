#ifndef TRANREANCIENT
#define TRANREANCIENT

#include <stdio.h>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
using namespace std;
using namespace cv;

inline void TranReAncient(Mat& img){
	img=img.clone();
	int width = img.cols;
	int heigh = img.rows;
	if (img.empty()) cout << "TranReAncient Error!";
	for (int y = 0; y<heigh; y++){
		uchar* P0 = img.ptr<uchar>(y);
		for (int x = 0; x<width; x++){
			float B = P0[3 * x];
			float G = P0[3 * x + 1];
			float R = P0[3 * x + 2];
			float newB = 0.272*R + 0.534*G + 0.131*B;
			float newG = 0.349*R + 0.686*G + 0.168*B;
			float newR = 0.393*R + 0.769*G + 0.189*B;
			if (newB<0) newB = 0;
			if (newB>255) newB = 255;
			if (newG<0) newG = 0;
			if (newG>255) newG = 255;
			if (newR<0) newR = 0;
			if (newR>255) newR = 255;
			P0[3 * x] = (uchar)newB;
			P0[3 * x + 1] = (uchar)newG;
			P0[3 * x + 2] = (uchar)newR;
		}
	}
	return;
}
#endif

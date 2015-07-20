#ifndef TRANGAUSSIANBLUR
#define TRANGAUSSIANBLUR

#include <stdio.h>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
using namespace std;
using namespace cv;

inline void TranGaussianBlur(Mat &img){
	img=img.clone();
	if (img.empty()) cout << "TranReAncient Error!";
	GaussianBlur(img, img, Size(15, 15), 0);
	GaussianBlur(img, img, Size(45, 45), 0);
	GaussianBlur(img, img, Size(45, 45), 0);
	GaussianBlur(img, img, Size(45, 45), 0);
}
#endif

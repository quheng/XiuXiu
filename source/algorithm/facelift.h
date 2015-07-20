//磨皮头文件

#include <opencv2/opencv.hpp>
#include <iostream>
#include "CMatrix.h"
using namespace std;
using namespace cv;

#ifndef FACELIFT
#define FACELIFT
void HorizontalIteration(const CMatrix<double>& mxImg,const int numChl,const double lamda,const double sigma,CMatrix<double>& mxResult);
void VerticalIteration(const CMatrix<double>& mxImg,const int numChl,const double lamda,const double sigma,CMatrix<double>& mxResult);
void BeepsHorVer(const CMatrix<double>& mxImg,const int numChl,const double lamda,const double sigma,CMatrix<double>& mxResult);
void BeepsVerHor(const CMatrix<double>& mxImg,const int numChl,const double lamda,const double sigma,CMatrix<double>& mxResult);
void FaceLift(Mat& oriImg, const int sigma);
#endif // FACELIFT


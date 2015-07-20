//Gamma矫正
#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include "mathfunction.h"
#include "../common/common.h"
using namespace std;
using namespace cv;

inline void _GammaCorrection(Mat& img,const double gamma){ //gamma>0
    if (gamma==1) return;
    img=img.clone();
    const int numColor=256;//颜色数
    int pixRows=img.rows; //像素行数
    int numChl=img.channels(); //通道数
    int pixCol=img.cols; //像素列数
    uchar mapColor[numColor];
    double fPrecompensation=1.0/gamma;
    for (int color=0;color<numColor;color++)
    {
        double f=(color+0.5F)/256.0;
        f=pow(f,fPrecompensation);
        mapColor[color]=(uchar)(f*256.0-0.5F);
    }
    for(int px=0;px<pixRows;px++)
        for (int py=0;py<pixCol;py++)
        {
            uchar* data=img.ptr<uchar>(px);
            for (int chl=0; chl<numChl; chl++){
                data[py*numChl+chl]=mapColor[data[py*numChl+chl]];
            }
        }
}

inline void GammaCorrection(Mat& img,const CImagePara para)
{
    const double delta=0.000001;
    if (abs(para.gamma-0.5)<delta)
        return;
    else if(para.gamma>0.5)
        _GammaCorrection(img,1+(para.gamma-0.5)*3);
    else
        _GammaCorrection(img,1+(para.gamma-0.5)*2+delta);
}
// GAMMACORRECTION


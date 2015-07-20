//美白
#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;
inline void FaceWhite(Mat& img,const int oriBeta) //beta>0
{
    int beta=oriBeta+1;
    if (beta<=1) return;
    img=img.clone();
    const int numColor=256;//颜色数
    int numRows=img.rows; //行数
    int numChl=img.channels(); //通道数
    int numCol=img.cols*numChl; //列数
    uchar mapColor[numColor];
    for (int color=0;color<numColor;color++)
    {
        double result=(double)color/255.0*(beta-1.0)+1.0;
        result=log(result)/log(beta)*255.0;
        mapColor[color]=(uchar)result;
    }
    for (int i=0;i<numRows;i++){//美白
        uchar* data=img.ptr<uchar>(i);
        for (int j=0;j<numCol;j++){
            data[j]=mapColor[data[j]];
        }
    }
}



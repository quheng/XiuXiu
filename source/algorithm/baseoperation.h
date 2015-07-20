#ifndef BASEOPERATION
#define BASEOPERATION
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <string>


using namespace std;
using namespace cv;


inline void rgb2gray(Mat& mat){
    cvtColor( mat, mat, CV_BGR2GRAY );
}


inline Mat BuildMat(const Mat& img)
{
    int pixRows=img.rows; //像素行数
    int numChl=img.channels(); //通道数
    int pixCol=img.cols; //像素列数
    switch (numChl){
    case 1:
        return Mat (pixCol,pixRows,CV_8UC1);
        break;
    case 2:
        return Mat (pixCol,pixRows,CV_8UC2);
        break;
    case 3:
        return Mat (pixCol,pixRows,CV_8UC3);
        break;
    case 4:
        return Mat (pixCol,pixRows,CV_8UC4);
        break;
    }
}

inline void clockwiseRotation(Mat& img )//顺时针
{
    Mat temImg=BuildMat(img);
    int pixRows=img.rows; //像素行数
    int numChl=img.channels(); //通道数
    int pixCol=img.cols; //像素列数
    for(int px=0;px<pixRows;px++)
        for (int py=0;py<pixCol;py++)
        {
            int rpx=py;
            int rpy=pixRows-px-1;
            uchar* oriData=img.ptr<uchar>(px);
            uchar* rotData=temImg.ptr<uchar>(rpx);
            for (int chl=0; chl<numChl; chl++){
                rotData[rpy*numChl+chl]=oriData[py*numChl+chl];
            }
        }
    img=temImg.clone();
}

inline void anticlockwiseRotation(Mat& img )//逆时针
{
    Mat temImg=BuildMat(img);
    int pixRows=img.rows; //像素行数
    int numChl=img.channels(); //通道数
    int pixCol=img.cols; //像素列数
    for(int px=0;px<pixRows;px++)
        for (int py=0;py<pixCol;py++)
        {
            int rpx=pixCol-py-1;
            int rpy=px;
            uchar* oriData=img.ptr<uchar>(px);
            uchar* rotData=temImg.ptr<uchar>(rpx);
            for (int chl=0; chl<numChl; chl++){
                rotData[rpy*numChl+chl]=oriData[py*numChl+chl];
            }
        }
    img=temImg.clone();
}

#endif // RGB2GRAY


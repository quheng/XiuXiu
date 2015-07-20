//局部缩放
#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include "mathfunction.h"
using namespace std;
using namespace cv;

inline int adjScale(int l,int r, int k)
{
    k=max(l,k);
    k=min(r,k);
    return k;
}

inline double distance(int x,int y, int a, int b)
{
    double powD=pow(x-a,2.0)+pow(y-b,2.0);
    return powD;
}

inline void PartialZoom(Mat& img,const int centerX,const int centerY,const int radius,const int  stringency) //abs(strength)<100
{
    if (stringency==0||stringency>=100||stringency<=-100) return;
    img=img.clone();
    Mat oriImg=img.clone();
    int pixRows=img.rows; //像素行数
    int numChl=img.channels(); //通道数
    int pixCol=img.cols; //像素列数
    int top,bottom,left,right;//调整的大致范围
    top=max(0,centerX-radius);
    bottom=min(pixRows-1,centerX+radius);
    left=max(0,centerY-radius);
    right=min(pixCol-1,centerY+radius);
    double strength=(double)stringency/100.0;
    double powRadius=radius*radius;
    for(int px=top;px<=bottom;px++)
        for (int py=left;py<=right;py++)
        {
            double powD=distance(centerX,centerY,px,py);
            if (powD>powRadius) continue;
            int offsetX=px-centerX;
            int offsetY=py-centerY;
            double scaleFactor=1.0-powD/powRadius;
            scaleFactor=1-strength*scaleFactor;
            int posX=adjScale(0,pixRows-1,int(offsetX*scaleFactor+centerX));
            int posY=adjScale(0,pixCol-1,int(offsetY*scaleFactor+centerY));
            uchar* imgData=img.ptr<uchar>(px);
            uchar* posData=oriImg.ptr<uchar>(posX);
            for (int chl=0; chl<numChl; chl++){
                imgData[py*numChl+chl]=posData[posY*numChl+chl];
            }
        }
}

// PARTIALZOOM


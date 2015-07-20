//亮度和对比度调整
#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include "../common/common.h"
using namespace std;
using namespace cv;

inline uchar adjRGB(int rgb)
{
  return (rgb & ~0xff) == 0? rgb : rgb > 255? 255 : 0;
}

inline uchar LuminanceAdj(const uchar rgb,const int bright)
{
    if (bright==0) return rgb;
    double result;
    double value=(bright<=-255)?-1:(bright/255.1) ;
    if (bright>0){
        value=1.0/(1.0-value)-1.0;
        result=rgb*value+rgb;
        return adjRGB((int)result);
    }
    else {
        result=rgb*value+rgb;
        return adjRGB((int) result);
    }
}

inline uchar ContrastAdj(const uchar rgb,const int contrast,uchar threshold=128)
{
    if (contrast==0) return rgb;
    double result;
    double value=(contrast<=-255)?-1:(contrast/255.0) ;
    if (contrast>0){
        if (contrast>=255)
            return (rgb>=threshold?255:0);
        else{
            value=1.0/(1.0-value)-1.0;
            result=(rgb-threshold)*value+rgb;
            return adjRGB((int)result);
        }
    }
    else{
        if (contrast==-255)
            return threshold;
        else{
            result=(rgb-threshold)*value+rgb;
            return adjRGB((int) result);
        }
    }
}

inline void _LuminAndContrast(Mat& img,const int bright,const int contrast,uchar threshold=128) //bright:[-255,255],contrast:[-255,255]
{
    if (bright==0&&contrast==0) return;
    img=img.clone();
    const int numColor=256;//颜色数
    int pixRows=img.rows; //像素行数
    int numChl=img.channels(); //通道数
    int pixCol=img.cols; //像素列数
    uchar mapColor[numColor];
    for (int color=0;color<numColor;color++)
    {
        if (contrast>0)
            mapColor[color]=ContrastAdj( LuminanceAdj(color,bright), contrast, threshold);
        else
            mapColor[color]=LuminanceAdj(ContrastAdj(color,contrast,threshold), bright);
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

inline void LuminAndContrast(Mat& img,const CImagePara para)
{
    _LuminAndContrast(img, (para.bright-0.5)*510,(para.contrast-0.5)*510);
}

// LUMINANDCONTRAST


//色相和饱和度调整(不能用于灰度图)
#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include "mathfunction.h"
#include "../common/common.h"
using namespace std;
using namespace cv;

inline int RGB2HSL(const uchar& R, const uchar& G, const uchar& B, int& H, int& S, int& L)
{
    int maxRGB,minRGB;
    maxRGB=max(max(R,G),B);
    minRGB=min(min(R,G),B);
    int delta=maxRGB-minRGB;
    int sum=maxRGB+minRGB;
    if (delta==0) return -1;
    L=sum>>1;
    if (L<128)
        S=delta*255/sum;
    else
        S=delta*255/(510-sum);
    if (maxRGB==R)
        H=(G-B)*60/delta;
    else if (maxRGB==G)
        H=(B-R)*60/delta+120;
    else
        H=(R-G)*60/delta+240;
    return 0;
}

inline void HueAdj(uchar& R, uchar& G, uchar& B,const int hueValue)
{
    if (hueValue==0) return;
    int H,S,L;
    if (RGB2HSL(R,G,B,H,S,L)==-1) return;
    H+=hueValue;
    if (H<0)
        H+=360;
    else if (H>360)
        H-=360;
    int index=H/60;
    int extra=H%60;
    if (index&1) extra=60-extra;
    extra=(extra*255+30)/60;
    G=extra-(extra-128)*(255-S)/255;
    int Lum=L-128;
    if(Lum > 0)
        G+=((255-G)*Lum+64)/128;
    else if (Lum < 0)
        G+=G*Lum/128;
    CheckRGB(G);
    switch (index)
      {
          case 1:
              swap(R, G);
              break;
          case 2:
              swap(R, B);
              swap(G, B);
              break;
          case 3:
              swap(R, B);
              break;
          case 4:
              swap(R, G);
              swap(G, B);
              break;
          case 5:
              swap(G, B);
              break;
      }
}

inline void SaturationAdj(uchar& R, uchar& G, uchar& B,const int satValue)
{
    if (satValue==0) return;
    int H,S,L;
    if (RGB2HSL(R,G,B,H,S,L)==-1) return;
    int sValue=satValue;
    if (satValue>0){
        if (satValue+S>=255)
            sValue=S;
        else sValue=255-sValue;
        sValue=65025/sValue-255;
    }
    R+=(R-L)*sValue/255;
    G+=(G-L)*sValue/255;
    B+=(B-L)*sValue/255;
    CheckRGB(R);
    CheckRGB(G);
    CheckRGB(B);
}

inline void _HueAndSaturation(Mat& img,const int hueValue,const int satValue) //hueValue:[0,360],satValue:[-255,+255]
{
    img=img.clone();
    int pixRows=img.rows; //像素行数
    int numChl=img.channels(); //通道数
    int pixCol=img.cols; //像素列数
    for(int px=0;px<pixRows;px++)
        for (int py=0;py<pixCol;py++)
        {
            uchar* data=img.ptr<uchar>(px);
            int index=py*numChl;
            HueAdj(data[index],data[index+1],data[index+2],hueValue);
            SaturationAdj(data[index],data[index+1],data[index+2],satValue);
        }
}

inline void HueAndSaturation(Mat& img,const CImagePara para)
{
    _HueAndSaturation(img,(para.hue-0.5)*360,(para.saturation-0.5)*510);
}

// HUEANDSATURATION


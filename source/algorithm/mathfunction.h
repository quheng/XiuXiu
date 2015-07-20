//高斯函数
#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;

inline double Guass(const double sigma,const double dis)
{
    double c=-0.5;
    double result=dis/sigma;
    result=result*result*c;
    return exp(result);
}


inline void swap(uchar& x,uchar& y)
{
    uchar temp;
    temp=x;
    x=y;
    y=temp;
}

inline void CheckRGB(uchar& value)
{
    if (value<0)
        value=0;
    if (value>255)
        value=255;
}

// MATHFUNCTION


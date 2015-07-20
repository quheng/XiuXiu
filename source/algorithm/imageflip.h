//图像水平、垂直翻转

#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include "mathfunction.h"
using namespace std;
using namespace cv;

inline void HorizontalFilp(Mat& img)
{
    img=img.clone();
    int pixRows=img.rows; //像素行数
    int numChl=img.channels(); //通道数
    int pixCol=img.cols; //像素列数
    for(int px=0;px<pixRows;px++)
    {
        uchar* data=img.ptr<uchar>(px);
        int left=0;
        int right=pixCol-1;
        while (left<right)
        {
            for (int chl=0;chl<numChl;chl++)
                swap(data[left*numChl+chl],data[right*numChl+chl]);
            left++;
            right--;
        }
    }
}

inline void VerticalFilp(Mat& img)
{
    img=img.clone();
    int pixRows=img.rows; //像素行数
    int numChl=img.channels(); //通道数
    int pixCol=img.cols; //像素列数
    for(int py=0;py<pixCol;py++)
    {
        int up=0;
        int down=pixRows-1;
        while (up<down)
        {
            uchar* data1=img.ptr<uchar>(up);
            uchar* data2=img.ptr<uchar>(down);
            for (int chl=0;chl<numChl;chl++)
                swap(data1[py*numChl+chl],data2[py*numChl+chl]);
            up++;
            down--;
        }
    }
}


// IMAGEFLIP


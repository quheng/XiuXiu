#ifndef TRANACG
#define TRANACG

#include <stdio.h>
#include <iostream>
#include <string>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

inline void SetMaxRGBValue(Mat& buckets, Mat& dst, int x, int y){
	int MaxCount = 0, Index = 0;
	for (int i = 0; i<buckets.rows; i++){
		if (buckets.at<ushort>(i, 0)>MaxCount){
			MaxCount = buckets.at<ushort>(i, 0);
			Index = i;
		}
	}
	int avR, avG, avB;
	if (MaxCount>0){
		avR = buckets.at<ushort>(Index, 1) / MaxCount;
		avG = buckets.at<ushort>(Index, 2) / MaxCount;
		avB = buckets.at<ushort>(Index, 3) / MaxCount;
		Vec3b tmp(avB, avG, avR);
		dst.at<Vec3b>(y, x) = tmp;
	}
}

inline void RemoveAndAddToBuckets(Mat& buckets, Mat& src, Mat& gray, int radius, int col_index, int row_index, bool IsAdd, bool IsLie = true){
	int StartIndex, EndIndex;
	int width = 2 * radius + 1;
	int BiaoZhi;
	if (IsAdd) BiaoZhi = 1;
	else BiaoZhi = -1;
	if (IsLie){
		if (col_index<0 || col_index >= src.cols)  return;
		if (row_index<0){
			StartIndex = 0;
			EndIndex = width + row_index;
		}
		else{
			StartIndex = row_index;
			EndIndex = (row_index + width)<src.rows ? row_index + width : src.rows;
		}
		for (int y = StartIndex; y<EndIndex; y++){
			int tmp = gray.at<uchar>(y, col_index);
			buckets.at<ushort>(tmp, 0) += BiaoZhi;
			buckets.at<ushort>(tmp, 1) += src.at<Vec3b>(y, col_index)[2] * BiaoZhi;
			buckets.at<ushort>(tmp, 2) += src.at<Vec3b>(y, col_index)[1] * BiaoZhi;
			buckets.at<ushort>(tmp, 3) += src.at<Vec3b>(y, col_index)[0] * BiaoZhi;
		}
	}
	else{
		if (row_index >= src.rows || row_index<0) return;
		if (col_index<0){
			StartIndex = 0;
			EndIndex = col_index + width;
		}
		else if (col_index >= src.cols) {
			StartIndex = src.cols - radius - 1;
			EndIndex = src.cols;
		}
		for (int x = StartIndex; x<EndIndex; x++){
			int tmp = gray.at<uchar>(row_index, x);
			buckets.at<ushort>(tmp, 0) += BiaoZhi;
			buckets.at<ushort>(tmp, 1) += src.at<Vec3b>(row_index, x)[2] * BiaoZhi;
			buckets.at<ushort>(tmp, 2) += src.at<Vec3b>(row_index, x)[1] * BiaoZhi;
			buckets.at<ushort>(tmp, 3) += src.at<Vec3b>(row_index, x)[0] * BiaoZhi;
		}
	}
}

inline void TranACG(Mat& src){
	src=src.clone();
    const int radius = 2;
	const int smoothness = 3;
    _LuminAndContrast(src, 5, -20, 128);
    Mat dst = Mat::zeros(src.size(), src.type());
	Mat Gray, Buckets;
	cvtColor(src, Gray, CV_BGR2GRAY);
	Buckets = Mat::zeros(Size(smoothness + 1, 4), CV_16UC1);
	int y, x;
	for (y = 0; y<Gray.rows; y++)
	for (x = 0; x<Gray.cols; x++) Gray.at<uchar>(y, x) = Gray.at<uchar>(y, x) / 255.0*smoothness;
	for (y = 0; y <= radius; y++)
	for (x = 0; x <= radius; x++){
		int tmp = Gray.at<uchar>(y, x);
		Buckets.at<ushort>(tmp, 0)++;
		Buckets.at<ushort>(tmp, 1) += src.at<Vec3b>(y, x)[2];
		Buckets.at<ushort>(tmp, 2) += src.at<Vec3b>(y, x)[1];;
		Buckets.at<ushort>(tmp, 3) += src.at<Vec3b>(y, x)[0];;
	}
	bool MoveFlags = false;
	for (y = 0; y<dst.rows; y++){
		if (!MoveFlags){
			for (x = 0; x<dst.cols; x++){
				SetMaxRGBValue(Buckets, dst, x, y);
				if (x != src.cols - 1){
					RemoveAndAddToBuckets(Buckets, src, Gray, radius, x - radius, y - radius, false);
					RemoveAndAddToBuckets(Buckets, src, Gray, radius, x + radius + 1, y - radius, true);
				}
				else{
					RemoveAndAddToBuckets(Buckets, src, Gray, radius, src.cols, y - radius, false, false);
					RemoveAndAddToBuckets(Buckets, src, Gray, radius, src.cols, y + radius + 1, true, false);
					MoveFlags = true;
				}
			}
		}
		else{
			for (x = src.cols - 1; x >= 0; x--){
				SetMaxRGBValue(Buckets, dst, x, y);
				if (x != 0){
					RemoveAndAddToBuckets(Buckets, src, Gray, radius, x + radius, y - radius, false);
					RemoveAndAddToBuckets(Buckets, src, Gray, radius, x - radius - 1, y - radius, true);
				}
				else{
					RemoveAndAddToBuckets(Buckets, src, Gray, radius, -radius, y - radius, false, false);
					RemoveAndAddToBuckets(Buckets, src, Gray, radius, -radius, y + radius + 1, true, false);
					MoveFlags = false;
				}
			}
		}
	}
    _GammaCorrection(src, 5.0);
    _HueAndSaturation(src, 0, 30);
	src = dst;
}

#endif

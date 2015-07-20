#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

void EdgeTest(Mat& src,int lowThreshold )
{
    int ratio = 3;
    int kernel_size = 3;

    Mat dst,src_gray, detected_edges;

    /// 创建与src同类型和大小的矩阵(dst)
      dst.create( src.size(), src.type() );

      /// 原图像转换为灰度图像
      cvtColor( src, src_gray, CV_BGR2GRAY );
    /// 使用 3x3内核降噪
      blur( src_gray, detected_edges, Size(3,3) );

   // 运行Canny算子
   Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

   // 使用 Canny算子输出边缘作为掩码显示原图像
   dst = Scalar::all(0);

   src.copyTo( dst, detected_edges);
   src = dst.clone();
 }

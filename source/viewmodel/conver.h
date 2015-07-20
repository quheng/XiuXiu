#ifndef CONVER
#define CONVER

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QImage>

using namespace cv;

inline QImage Mat2QImage(const Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
        if(mat.type() == CV_8UC1)
        {
            QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
            // Set the color table (used to translate colour indexes to qRgb values)
            image.setColorCount(256);
            for(int i = 0; i < 256; i++)
            {
                image.setColor(i, qRgb(i, i, i));
            }
            // Copy input Mat
            uchar *pSrc = mat.data;
            for(int row = 0; row < mat.rows; row ++)
            {
                uchar *pDest = image.scanLine(row);
                memcpy(pDest, pSrc, mat.cols);
                pSrc += mat.step;
            }
            return image;
        }
        // 8-bits unsigned, NO. OF CHANNELS = 3
           else if(mat.type() == CV_8UC3)
           {
               // Copy input Mat
               const uchar *pSrc = (const uchar*)mat.data;
               // Create QImage with same dimensions as input Mat
               QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
               return image.rgbSwapped();
           }
           else if(mat.type() == CV_8UC4)
           {
               // Copy input Mat
               const uchar *pSrc = (const uchar*)mat.data;
               // Create QImage with same dimensions as input Mat
               QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
               return image.copy();
           }

}

inline cv::Mat QImage2Mat(const QImage& qimage)
{
    cv::Mat mat = cv::Mat(qimage.height(), qimage.width(), CV_8UC4, (uchar*)qimage.bits(), qimage.bytesPerLine());
    cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = { 0,0, 1,1, 2,2 };
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );
    return mat2;
}

#endif // CONVER


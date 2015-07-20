//离散mat类型图像数据
#pragma once
inline void DisImgData(const Mat& img, CMatrix<double>& mx)
{
    int numRows=img.rows; //行数
    int numChl=img.channels(); //通道数
    int numCol=img.cols*numChl; //列数
    for (int i=0;i<numRows;i++){
        const uchar* data=img.ptr<uchar>(i);
        for (int j=0;j<numCol;j++){
            mx.set(i,j,data[j]);
        }
    }
}

inline void MatrixToImg(const CMatrix<double>& mx,Mat& img)
{
    int numRows=img.rows; //行数
    int numChl=img.channels(); //通道数
    int numCol=img.cols*numChl; //列数
    for (int i=0;i<numRows;i++){
        uchar* data=img.ptr<uchar>(i);
        for (int j=0;j<numCol;j++){
            data[j]=mx.get(i,j);
        }
    }
}
// IMG2MATIRX


//磨皮

#include <opencv2/opencv.hpp>
#include <iostream>
#include "cmatrix.h"
#include "facelift.h"
#include "img2matrix.h"
#include "mathfunction.h"
using namespace std;
using namespace cv;

void HorizontalIteration(const CMatrix<double>& mxImg,const int numChl,const double lamda,const double sigma,CMatrix<double>& mxResult)
{
    int numRows=mxImg.getRows(); //行数
    int numCol=mxImg.getCol(); //列数
    CMatrix<double> mxa(numRows,numCol);
    CMatrix<double> mxb(numRows,numCol);
    //progressive
    for (int i=0;i<numRows;i++){//枚举行
         for (int j=0;j<numCol;j++) //枚举列
           {
                mxa.set(i,j,mxImg.get(i,j));
                int k=j-numChl;
                if (k>=0)
                {
                    double rho=Guass(sigma,mxa.get(i,j)-mxa.get(i,k));
                    double result=(1.0-rho*lamda)*mxa.get(i,j)+rho*lamda*mxa.get(i,k);
                    mxa.set(i,j,result);
                }
            }
    }
    //regressive
    for (int i=0;i<numRows;i++){//枚举行
        for (int j=numCol-1;j>=0;j--) //枚举列
            {
                mxb.set(i,j,mxImg.get(i,j));
                int k=j+numChl;
                if (k<numCol)
                {
                    double rho=Guass(sigma,mxb.get(i,j)-mxb.get(i,k));
                    double result=(1.0-rho*lamda)*mxb.get(i,j)+rho*lamda*mxb.get(i,k);
                    mxb.set(i,j,result);
                }
            }
    }
    //合并
    for (int i=0;i<numRows;i++)    
        for (int j=0;j<numCol;j++)
        {
            double result=(mxa.get(i,j)+mxb.get(i,j))/2;
            mxResult.set(i,j,result);
        }

}


void VerticalIteration(const CMatrix<double>& mxImg,const int numChl,const double lamda,const double sigma,CMatrix<double>& mxResult)
{
    int numRows=mxImg.getRows(); //行数
    int numCol=mxImg.getCol(); //列数
    CMatrix<double> mxa(numRows,numCol);
    CMatrix<double> mxb(numRows,numCol);
    //progressive
    for (int j=0;j<numCol;j++){//枚举列
        for (int i=0;i<numRows;i++) //枚举行
            {
                mxa.set(i,j,mxImg.get(i,j));
                int k=i-1;
                if (k>=0)
                {
                    double rho=Guass(sigma,mxa.get(i,j)-mxa.get(k,j));
                    double result=(1.0-rho*lamda)*mxa.get(i,j)+rho*lamda*mxa.get(k,j);
                    mxa.set(i,j,result);
                }
            }
    }
    //regressive
    for (int j=0;j<numCol;j++){//枚举列
        for (int i=numRows-1;i>=0;i--) //枚举行
            {
                mxb.set(i,j,mxImg.get(i,j));
                int k=i+1;
                if (k<numRows)
                {
                    double rho=Guass(sigma,mxb.get(i,j)-mxb.get(k,j));
                    double result=(1.0-rho*lamda)*mxb.get(i,j)+rho*lamda*mxb.get(k,j);
                    mxb.set(i,j,result);
                }
            }
    }
    //合并
    for (int i=0;i<numRows;i++)   
        for (int j=0;j<numCol;j++)
        {
            double result=(mxa.get(i,j)+mxb.get(i,j))/2;
            mxResult.set(i,j,result);
        }    
}


void BeepsHorVer(const CMatrix<double>& mxImg,const int numChl,const double lamda,const double sigma,CMatrix<double>& mxResult)
{
    CMatrix<double> mx(mxImg.getRows(),mxImg.getCol());
    HorizontalIteration(mxImg,numChl,lamda,sigma,mx);
    VerticalIteration(mx,numChl,lamda,sigma,mxResult);
}


void BeepsVerHor(const CMatrix<double>& mxImg,const int numChl,const double lamda,const double sigma,CMatrix<double>& mxResult)
{
    CMatrix<double> mx(mxImg.getRows(),mxImg.getCol());
    VerticalIteration(mxImg,numChl,lamda,sigma,mx);
    HorizontalIteration(mx,numChl,lamda,sigma,mxResult);
}

void FaceLift(Mat& oriImg,const int sigma) //sigma>0
{
    if (sigma<=0) return;
    oriImg=oriImg.clone();
    int numRows=oriImg.rows; //行数
    int numChl=oriImg.channels(); //通道数
    int numCol=oriImg.cols*numChl; //列数
    CMatrix<double> mxHorVer(numRows,numCol);
    CMatrix<double> mxVerHor(numRows,numCol);
    CMatrix<double> mxImg(numRows,numCol);
    DisImgData(oriImg,mxImg);
    BeepsHorVer(mxImg,numChl,0.995,sigma,mxHorVer); //图像先水平后垂直迭代
    BeepsVerHor(mxImg,numChl,0.995,sigma,mxVerHor);//图像先垂直后水平迭代
    for (int i=0;i<numRows;i++){//合并
        uchar* data=oriImg.ptr<uchar>(i);
        for (int j=0;j<numCol;j++){
            data[j]=(uchar)((mxHorVer.get(i,j)+mxVerHor.get(i,j))/2.0);
        }
    }
}

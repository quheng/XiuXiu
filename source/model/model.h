#pragma once

#include <QImage>
#include <stack>
#include <QMessageBox>
#include <QMainWindow>
#include <QString>
#include <algorithm/histogram.h>
#include <algorithm/facelift.h>
#include <algorithm/baseoperation.h>
#include <algorithm/trancrystal.h>
#include <algorithm/tranpencil.h>
#include <algorithm/tranreancient.h>
#include <algorithm/facewhite.h>
#include <algorithm/trangaussianblur.h>
#include <algorithm/imageflip.h>
#include <algorithm/gammacorrection.h>
#include <algorithm/hueandsaturation.h>
#include <algorithm/luminandcontrast.h>
#include <algorithm/edge.h>
#include <algorithm/tranacg.h>
#include "../common/common.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

//notic 更新时注意将老图片压入堆栈
class ImageModel{
private:
    Mat image;
    Mat testImage;
    stack<Mat> oldImage;
    stack<Mat> reDoImage;
    CHistogram hist;
    CImagePara imagePara;

public:

    inline Mat& GetImage(){return image;}

    inline void SetImage(const Mat& value){
        while(!oldImage.empty())
            oldImage.pop();// 出栈
        image = value;                  //question 读入新图片对操作历史的影响
    }

    inline Mat& GetTestImage(){return testImage;}
    inline void SetImagePara(const CImagePara& value){imagePara = value;}

    //redo
    inline void Undo(){
        if (!oldImage.empty()){
            reDoImage.push(image);
            image = oldImage.top();
            oldImage.pop();
        }
    }

    //撤销
    inline void Redo(){
        if (!reDoImage.empty()){
            oldImage.push(image);
            image = reDoImage.top();
            reDoImage.pop();
        }
    }


    //获取直方图信息
    inline CHistogram& GetHistogram(){
        if (image.channels() > 2){
            hist = getHistogram(image);
            return hist;
        }
    }

    //获取临时直方图信息
    inline CHistogram& GetTestHistogram(){
        if (image.channels() > 2){
            hist = getHistogram(testImage);
            return hist;
        }
    }

    //磨皮
    inline void DoFaceLift(){
        oldImage.push(image);
        while(!reDoImage.empty())
            reDoImage.pop();// 出栈
        FaceLift (image,10);
    }
    //美白
    inline void DoFaceWhite(int para){
        testImage = image.clone();
        FaceWhite(testImage,para);
    }

    //转灰度图
    inline void DoGray(){
        while(!reDoImage.empty())
            reDoImage.pop();// 出栈
        if (image.channels() > 2) {             //灰度图 channels = 2， 多次转换会崩溃
            oldImage.push(image);
            rgb2gray(image);
       }
    }

    //水晶
    void DoCrystal(){
        while(!reDoImage.empty())
            reDoImage.pop();// 出栈
        if (image.channels() > 2) {
            oldImage.push(image);
            TranCrystal(image);
        }
    }

    //复古
    void DoReancient(){
        while(!reDoImage.empty())
            reDoImage.pop();// 出栈
        if (image.channels() > 2) {
            oldImage.push(image);
            TranReAncient(image);
        }
    }

    //铅笔画
    void DoPencil(){
        while(!reDoImage.empty())
            reDoImage.pop();// 出栈
        if (image.channels() > 2) {
            oldImage.push(image);
            TranPencil(image);
        }
    }

    //毛玻璃
    void DoGauss(){
        while(!reDoImage.empty())
            reDoImage.pop();// 出栈
        oldImage.push(image);
        TranGaussianBlur(image);
    }

    //竖直翻转
    void DoVerticalFilp(){
        while(!reDoImage.empty())
            reDoImage.pop();// 出栈
         oldImage.push(image);
         VerticalFilp(image);
    }

    //水平翻转
    void DoHorizontalFilp(){
        while(!reDoImage.empty())
            reDoImage.pop();// 出栈
        oldImage.push(image);
        HorizontalFilp(image);
    }

    //顺时针翻转
    void DoClockwiseRotation(){
        while(!reDoImage.empty())
            reDoImage.pop();// 出栈
        oldImage.push(image);
        clockwiseRotation(image);
    }

    //逆时针翻转
    void DoAnticlockwiseRotation(){
        while(!reDoImage.empty())
            reDoImage.pop();// 出栈
        oldImage.push(image);
        anticlockwiseRotation(image);
    }

    //调整Gamma
    void AdGamma(){
        testImage = image.clone();
        GammaCorrection(testImage,imagePara);
    }

    //调整亮度和对比度
    void AdLuminAndContrast(){
        testImage = image.clone();
        LuminAndContrast(testImage,imagePara);
    }

    //调整色相和饱和度
    void AdHueAndSaturation(){
        testImage = image.clone();
        HueAndSaturation(testImage,imagePara);
    }

    //边缘检测
    void DoEdgeTest(int para){
        testImage = image.clone();
        EdgeTest(testImage,para);
    }
    //动漫风
    void DoACG(){
        while(!reDoImage.empty())
            reDoImage.pop();// 出栈
        oldImage.push(image);
        TranACG(image);
    }

    //确认修改
    void DoAdjust(){
        while(!reDoImage.empty())
            reDoImage.pop();// 出栈
        oldImage.push(image);
        image = testImage.clone();
    }
    //取消修改
    void DoCancel(){
        testImage = image.clone();
    }
};

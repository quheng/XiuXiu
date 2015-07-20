#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <common/CommandParameter.h>
#include <string>
#include <Qstring>
#include "../conver.h"
using namespace std;


template <class T>
class OpenCommand :public ICommandEx
{
public:
    OpenCommand(T* p) throw():m_pviemod(p)
    {
    }

    RefPtr<ICommandEx> getOpenCommandRef() throw()
    {
         return RefPtrHelper::TypeCast<OpenCommand<T>, ICommandEx>(RefPtr<OpenCommand<T> >(this));
    }
    virtual void SetParameter(const RefPtr<ICommandParameter>& param)
    {
       m_param = param;
    }
    virtual void Exec()
    {
        RefPtr<OneParameter<QString> > p = RefPtrHelper::TypeCast<ICommandParameter, OneParameter<QString> >(m_param);

        cv::Mat mat = cv::imread(p.Deref().getPara().toStdString());

        m_pviemod->setQImage(Mat2QImage(mat));

        //将数据储存到ImageModel
        m_pviemod->getImageModelRef().Deref().SetImage(mat);

        //更新直方图
        CHistogram tem = m_pviemod->getImageModelRef().Deref().GetHistogram();
        m_pviemod->getHist().setRedHistogram(Mat2QImage(tem.getRedHistogram()));
        m_pviemod->getHist().setBlueHistogram(Mat2QImage(tem.getBlueHistogram()));
        m_pviemod->getHist().setGreenHistogram(Mat2QImage(tem.getGreenHistogram()));
    }

private:
    T* m_pviemod;
    RefPtr<ICommandParameter> m_param;
};

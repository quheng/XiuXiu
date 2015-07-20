#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <common/CommandParameter.h>
#include <string>
#include <Qstring>
#include "../conver.h"
using namespace std;


template <class T>
class HistCommand :public ICommandEx
{
public:
    HistCommand(T* p) throw():m_pviemod(p)
    {
    }

    RefPtr<ICommandEx> getHistCommandRef() throw()
    {
         return RefPtrHelper::TypeCast<HistCommand<T>, ICommandEx>(RefPtr<HistCommand<T> >(this));
    }
    virtual void SetParameter(const RefPtr<ICommandParameter>& param)
    {
       m_param = param;
    }
    virtual void Exec()
    {
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

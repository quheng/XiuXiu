#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <common/CommandParameter.h>
#include <string>
#include <Qstring>
#include "../conver.h"
using namespace std;


template <class T>
class RedoCommand :public ICommandEx
{
public:
    RedoCommand(T* p) throw():m_pviemod(p)
    {
    }

    RefPtr<ICommandEx> getRedoCommandRef() throw()
    {
         return RefPtrHelper::TypeCast<RedoCommand<T>, ICommandEx>(RefPtr<RedoCommand<T> >(this));
    }
    virtual void SetParameter(const RefPtr<ICommandParameter>& param)
    {
       m_param = param;
    }
    virtual void Exec()
    {
        //将model层图像回退到上个图像，并更新view层
        m_pviemod->getImageModelRef().Deref().Redo();

        m_pviemod->setQImage(Mat2QImage(m_pviemod->getImageModelRef().Deref().GetImage()));

        CHistogram tem = m_pviemod->getImageModelRef().Deref().GetHistogram();
        m_pviemod->getHist().setRedHistogram(Mat2QImage(tem.getRedHistogram()));
        m_pviemod->getHist().setBlueHistogram(Mat2QImage(tem.getBlueHistogram()));
        m_pviemod->getHist().setGreenHistogram(Mat2QImage(tem.getGreenHistogram()));
    }

private:
    T* m_pviemod;
    RefPtr<ICommandParameter> m_param;
};

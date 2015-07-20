#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <common/CommandParameter.h>
#include <string>
#include <Qstring>
#include "../conver.h"
using namespace std;


template <class T>
class GrayCommand :public ICommandEx
{
public:
    GrayCommand(T* p) throw():m_pviemod(p)
    {
    }

    RefPtr<ICommandEx> getGrayCommandRef() throw()
    {
         return RefPtrHelper::TypeCast<GrayCommand<T>, ICommandEx>(RefPtr<GrayCommand<T> >(this));
    }
    virtual void SetParameter(const RefPtr<ICommandParameter>& param)
    {
       m_param = param;
    }
    virtual void Exec()
    {
        //改变model层数据
        m_pviemod->getImageModelRef().Deref().DoGray();

        //将model传递到viewModel；
        QImage img = Mat2QImage(m_pviemod->getImageModelRef().Deref().GetImage());
        m_pviemod->setQImage(img);
    }

private:
    T* m_pviemod;
    RefPtr<ICommandParameter> m_param;
};

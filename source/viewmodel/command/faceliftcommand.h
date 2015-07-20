#pragma once
#include <common/CommandParameter.h>
#include <string>
#include <Qstring>
#include "../conver.h"
using namespace std;

template <class T>
class FaceLiftCommand :public ICommandEx
{
public:
    FaceLiftCommand(T* p) throw():m_pviemod(p)
    {
    }

    RefPtr<ICommandEx> getFaceLiftCommandRef() throw()
    {
         return RefPtrHelper::TypeCast<FaceLiftCommand<T>, ICommandEx>(RefPtr<FaceLiftCommand<T> >(this));
    }
    virtual void SetParameter(const RefPtr<ICommandParameter>& param)
    {
       m_param = param;
    }
    virtual void Exec()
    {
        //得到参数
        //RefPtr<OneParameter<int> > p = RefPtrHelper::TypeCast<ICommandParameter, OneParameter<int> >(m_param);

        //改变model层数据
        m_pviemod->getImageModelRef().Deref().DoFaceLift();

        //将model传递到viewModel；
        QImage img = Mat2QImage(m_pviemod->getImageModelRef().Deref().GetImage());
        m_pviemod->setQImage(img);

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


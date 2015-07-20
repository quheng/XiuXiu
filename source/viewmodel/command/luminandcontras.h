#pragma once
#include <common/CommandParameter.h>
#include <string>
#include <Qstring>
#include "../conver.h"
using namespace std;

template <class T>
class LuminContrasCommand :public ICommandEx
{
public:
    LuminContrasCommand(T* p) throw():m_pviemod(p)
    {
    }

    RefPtr<ICommandEx> getLuminContrasCommandRef() throw()
    {
         return RefPtrHelper::TypeCast<LuminContrasCommand<T>, ICommandEx>(RefPtr<LuminContrasCommand<T> >(this));
    }
    virtual void SetParameter(const RefPtr<ICommandParameter>& param)
    {
       m_param = param;
    }
    virtual void Exec()
    {

        RefPtr<OneParameter<CImagePara> > p = RefPtrHelper::TypeCast<ICommandParameter, OneParameter<CImagePara> >(m_param);

        //改变model层的图像参数
        m_pviemod->getImageModelRef().Deref().SetImagePara(p.Deref().getPara());

        //改变model层的数据
        m_pviemod->getImageModelRef().Deref().AdLuminAndContrast();

        //将model传递到viewModel；
        QImage img = Mat2QImage(m_pviemod->getImageModelRef().Deref().GetTestImage());
        m_pviemod->setQImage(img);

        //更新直方图
        CHistogram tem = m_pviemod->getImageModelRef().Deref().GetTestHistogram();
        m_pviemod->getHist().setRedHistogram(Mat2QImage(tem.getRedHistogram()));
        m_pviemod->getHist().setBlueHistogram(Mat2QImage(tem.getBlueHistogram()));
        m_pviemod->getHist().setGreenHistogram(Mat2QImage(tem.getGreenHistogram()));
    }

private:
    T* m_pviemod;
    RefPtr<ICommandParameter> m_param;
};


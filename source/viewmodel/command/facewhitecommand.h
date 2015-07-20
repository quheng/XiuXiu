#pragma once
#include <common/CommandParameter.h>
#include <string>
#include <Qstring>
#include "../conver.h"
using namespace std;

template <class T>
class FaceWhiteCommand :public ICommandEx
{
public:
    FaceWhiteCommand(T* p) throw():m_pviemod(p)
    {
    }

    RefPtr<ICommandEx> getFaceWhiteCommandRef() throw()
    {
         return RefPtrHelper::TypeCast<FaceWhiteCommand<T>, ICommandEx>(RefPtr<FaceWhiteCommand<T> >(this));
    }
    virtual void SetParameter(const RefPtr<ICommandParameter>& param)
    {
       m_param = param;
    }
    virtual void Exec()
    {

        //改变model层数据
        RefPtr<OneParameter<int> > p = RefPtrHelper::TypeCast<ICommandParameter, OneParameter<int> >(m_param);
        m_pviemod->getImageModelRef().Deref().DoFaceWhite(p.Deref().getPara());

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


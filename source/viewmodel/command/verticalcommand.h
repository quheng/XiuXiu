#pragma once
#include <common/CommandParameter.h>
#include <string>
#include <Qstring>
#include "../conver.h"
using namespace std;

template <class T>
class VerticalCommand :public ICommandEx
{
public:
    VerticalCommand(T* p) throw():m_pviemod(p)
    {
    }

    RefPtr<ICommandEx> getVerticalCommandRef() throw()
    {
         return RefPtrHelper::TypeCast<VerticalCommand<T>, ICommandEx>(RefPtr<VerticalCommand<T> >(this));
    }
    virtual void SetParameter(const RefPtr<ICommandParameter>& param)
    {
       m_param = param;
    }
    virtual void Exec()
    {
        //改变model层数据
        m_pviemod->getImageModelRef().Deref().DoVerticalFilp();

        //将model传递到viewModel；
        QImage img = Mat2QImage(m_pviemod->getImageModelRef().Deref().GetImage());
        m_pviemod->setQImage(img);
    }

private:
    T* m_pviemod;
    RefPtr<ICommandParameter> m_param;
};


#pragma once
#include <common/CommandParameter.h>
#include <string>
#include <Qstring>
#include "../conver.h"
using namespace std;

template <class T>
class DoAdjustCommand :public ICommandEx
{
public:
    DoAdjustCommand(T* p) throw():m_pviemod(p)
    {
    }

    RefPtr<ICommandEx> getDoAdjustCommandRef() throw()
    {
         return RefPtrHelper::TypeCast<DoAdjustCommand<T>, ICommandEx>(RefPtr<DoAdjustCommand<T> >(this));
    }
    virtual void SetParameter(const RefPtr<ICommandParameter>& param)
    {
       m_param = param;
    }
    virtual void Exec()
    {
        //改变model层数据
        m_pviemod->getImageModelRef().Deref().DoAdjust();

        //将model传递到viewModel；
        QImage img = Mat2QImage(m_pviemod->getImageModelRef().Deref().GetImage());
        m_pviemod->setQImage(img);
    }

private:
    T* m_pviemod;
    RefPtr<ICommandParameter> m_param;
};


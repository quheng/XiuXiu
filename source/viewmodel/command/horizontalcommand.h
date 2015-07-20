#pragma once
#include <common/CommandParameter.h>
#include <string>
#include <Qstring>
#include "../conver.h"
using namespace std;

template <class T>
class HorizontalCommand :public ICommandEx
{
public:
    HorizontalCommand(T* p) throw():m_pviemod(p)
    {
    }

    RefPtr<ICommandEx> getHorizontalCommandRef() throw()
    {
         return RefPtrHelper::TypeCast<HorizontalCommand<T>, ICommandEx>(RefPtr<HorizontalCommand<T> >(this));
    }
    virtual void SetParameter(const RefPtr<ICommandParameter>& param)
    {
       m_param = param;
    }
    virtual void Exec()
    {
        //改变model层数据
        m_pviemod->getImageModelRef().Deref().DoHorizontalFilp();

        //将model传递到viewModel；
        QImage img = Mat2QImage(m_pviemod->getImageModelRef().Deref().GetImage());
        m_pviemod->setQImage(img);
    }

private:
    T* m_pviemod;
    RefPtr<ICommandParameter> m_param;
};


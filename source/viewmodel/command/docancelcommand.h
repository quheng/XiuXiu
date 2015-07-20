#pragma once
#include <common/CommandParameter.h>
#include <string>
#include <Qstring>
#include "../conver.h"
using namespace std;

template <class T>
class DoCancelCommand :public ICommandEx
{
public:
    DoCancelCommand(T* p) throw():m_pviemod(p)
    {
    }

    RefPtr<ICommandEx> getDoCancelCommandRef() throw()
    {
         return RefPtrHelper::TypeCast<DoCancelCommand<T>, ICommandEx>(RefPtr<DoCancelCommand<T> >(this));
    }
    virtual void SetParameter(const RefPtr<ICommandParameter>& param)
    {
       m_param = param;
    }
    virtual void Exec()
    {
        //将model原始数据传递到viewModel；
        QImage img = Mat2QImage(m_pviemod->getImageModelRef().Deref().GetImage());
        m_pviemod->setQImage(img);
    }

private:
    T* m_pviemod;
    RefPtr<ICommandParameter> m_param;
};


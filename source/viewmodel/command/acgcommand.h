#pragma once
#include <common/CommandParameter.h>
#include <string>
#include <Qstring>
#include "../conver.h"
using namespace std;

template <class T>
class AcgCommand :public ICommandEx
{
public:
    AcgCommand(T* p) throw():m_pviemod(p)
    {
    }

    RefPtr<ICommandEx> getAcgCommandRef() throw()
    {
         return RefPtrHelper::TypeCast<AcgCommand<T>, ICommandEx>(RefPtr<AcgCommand<T> >(this));
    }
    virtual void SetParameter(const RefPtr<ICommandParameter>& param)
    {
       m_param = param;
    }
    virtual void Exec()
    {
        //改变model层数据
        m_pviemod->getImageModelRef().Deref().DoACG();

        //将model传递到viewModel；
        QImage img = Mat2QImage(m_pviemod->getImageModelRef().Deref().GetImage());
        m_pviemod->setQImage(img);

    }

private:
    T* m_pviemod;
    RefPtr<ICommandParameter> m_param;
};


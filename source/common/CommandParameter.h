#pragma once

template <class T>
class OneParameter : public ICommandParameter
{
public:
    void setPara(const T& str)
    {
         m_para = str;
    }
    const T& getPara() const
    {
         return m_para;
    }


private:
    T m_para;
};

template <class T>
class TwoParameter : public ICommandParameter
{
public:
    void setS1(const T& str)
    {
         m_s1 = str;
    }
    const T& getS1() const throw()
    {
         return m_s1;
    }
    void setS2(const T& str)
    {
         m_s2 = str;
    }
    const T& getS2() const throw()
    {
         return m_s2;
    }

private:
    T m_s1;
    T m_s2;
};

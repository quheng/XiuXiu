#pragma once

#include <assert.h>
#include <vector>
#include <string>
#include <QImage>
#include <opencv2/opencv.hpp>


template <typename T>
class RefPtr
{
public:
    explicit RefPtr(T* p = NULL) throw() : m_p(p)
    {
    }
    RefPtr(const RefPtr<T>& src) throw() : m_p(src.m_p)
    {
    }
    RefPtr(RefPtr&& src) throw()
    {
        m_p = src.m_p;
        src.m_p = NULL;
    }
    ~RefPtr() throw()
    {
    }

    void Release() throw()
    {
        m_p = NULL;
    }

    RefPtr<T>& operator=(const RefPtr<T>& src) throw()
    {
         if( this != &src ) {
              m_p = src.m_p;
         }
         return *this;
    }
    RefPtr<T>& operator=(RefPtr<T>&& src) throw()
    {
         if( this != &src ) {
              m_p = src.m_p;
              src.m_p = NULL;
         }
         return *this;
    }

    const T& Deref() const throw()
    {
        assert( m_p != NULL ); 
        return *m_p;
    }
    T& Deref() throw()
    {
        assert( m_p != NULL ); 
        return *m_p;
    }

private:
    T* m_p;
};

class RefPtrHelper
{
public:
    template <class T, class TBase>
    static RefPtr<TBase> TypeCast(const RefPtr<T>& t) throw()
    {
        return RefPtr<TBase>((TBase*)static_cast<const TBase*>(&(t.Deref())));
    }
};

template <class T>
class NotificationImpl
{
public:
    std::vector<RefPtr<T> >& GetNotificationArray() throw(){
		return m_array;
	}
	void AddNotification(const RefPtr<T>& p)
	{
		m_array.push_back(p);
	}

private:
    std::vector<RefPtr<T> > m_array;
};

class INotification
{
public:
	virtual void OnPropertyChange(const std::string& str) = 0;
};


class ICommandParameter
{
};

class ICommandEx
{
public:
    virtual void SetParameter(const RefPtr<ICommandParameter>& param) = 0;
	virtual void Exec() = 0;
};

class CHistogram{
private:
    cv::Mat redHist;
    cv::Mat blueHist;
    cv::Mat greenHist;
public:
    cv::Mat& getRedHistogram() {return redHist;}
    void setRedHistogram(const cv::Mat &value){redHist = value;}
    cv::Mat& getBlueHistogram() {return blueHist;}
    void setBlueHistogram(const cv::Mat &value){blueHist = value;}
    cv::Mat& getGreenHistogram() {return greenHist;}
    void setGreenHistogram(const cv::Mat &value){greenHist = value;}
};

class CImagePara{
public:
    double bright;
    double contrast;
    double gamma;
    double saturation;
    double hue;
};

class CQHistogram{
private:
    QImage redHist;
    QImage blueHist;
    QImage greenHist;
public:
    QImage& getRedHistogram() {return redHist;}
    void setRedHistogram(const QImage &value){redHist = value;}
    QImage& getBlueHistogram() {return blueHist;}
    void setBlueHistogram(const QImage &value){blueHist = value;}
    QImage& getGreenHistogram() {return greenHist;}
    void setGreenHistogram(const QImage &value){greenHist = value;}
};

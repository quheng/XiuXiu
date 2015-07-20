//矩阵类

#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace std;
using namespace cv;


template <class T>
class CMatrix{
    public:
        CMatrix():data(NULL),numRows(0),numCol(0){}
        CMatrix(int x,int y):numRows(x),numCol(y){
            alloSpace(x,y);
        }
        CMatrix(const CMatrix<T>& C):numRows(C.numRows),numCol(C.numCol){
           alloSpace(C.numRows,C.numCol);
           for (int i=0;i<numRows;i++)
                for (int j=0;j<numCol;j++)
                    set(i,j,C.get(i,j));
        }
        ~CMatrix(){
            delSpace();
        }

        void delSpace(){//回收数据内存
            for (int i=0;i<numRows;i++)
                delete[] data[i];
            delete[] data;
        }
        void alloSpace(int x,int y){//申请数据内存
            data=new T*[x];
            for(int i=0;i<x;i++)
                data[i]=new T[y];
        }

        CMatrix<T>& operator=(const CMatrix<T>& rhs){// = 重载
            if (this!=&rhs){
                numRows=rhs.numRows;
                numCol=rhs.numCol;
                delSpace();
                alloSpace(numRows,numCol);
                for (int i=0;i<numRows;i++)
                     for (int j=0;j<numCol;j++)
                         set(i,j,rhs.get(i,j));
            }
            return *this;
        }

        void set(int i,int j, const T& k){
            if (i<0||i>=numRows||j<0||j>=numCol) {
                return;
            }
            *(data[i]+j)=k;
        }
        T get(int i,int j) const{
            if (i<0||i>=numRows||j<0||j>=numCol) {
                return T(1);
            }
            return *(data[i]+j);
        }

        int getRows() const {
            return numRows;
        }
        int getCol() const{
            return numCol;
        }

    private:
        int numRows,numCol;
        T** data;
};

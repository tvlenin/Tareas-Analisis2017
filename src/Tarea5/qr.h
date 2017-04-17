#ifndef _ANPI_QR_H
#define _ANPI_QR_H
#include <vector>
#include "Matrix.hpp"
#include <math.h>


namespace anpi{
  using namespace std;
  template<typename T >
  class qr {
  private:
    std::vector<Matrix<T>> qMatrix;

  public:
    qr(){};
    // get the first column of Matrix A
    vector<T> getColumn(const Matrix<T> A, int sizec , int sizer){}
    // get the norm of a vector
    T getNorm(const vector<T> vec){
      int sizeV = vec.size();
      T ans = 0;
      for (int i = 0; i < sizeV;i++){
        ans += pow(vec[i],2);
      }
      return sqrt(ans);
    }
    //get de diferent qmatrix and put this on qMatrix vector
    void getQMatrix(Matrix<T> IMatrix, vector<T> u){}


    qr(const Matrix<T>& A, Matrix<T>& Q, Matrix<T>& R){
      int sizec = A.cols();
      int sizer = A.rows();
      vector<T> column;

    }

  };
}// namespace ANPI

#endif

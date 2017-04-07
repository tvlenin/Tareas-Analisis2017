#ifndef _ANPI_QR_H
#define _ANPI_QR_H
#include <vector>
#include "Matrix.hpp"


namespace anpi{
  using namespace std;
  template<typename T >
  class qr {
  private:
    std::vector<Matrix<T>> qMatrix;

  public:
    qr();
    // get the first column of Matrix A
    vector<T> getColumn(const Matrix<T> A, int sizec , int sizer){}
    // get the norm of a vector
    T getNorm(const vector<T>, T norm){}
    //Return the identity matrix sizec x sizec
    Matrix<T> IMatrix(int sizec){}



    qr(const Matrix<T>& A, Matrix<T>& Q, Matrix<T>& R){
      int sizec = A.cols();
      int sizer = A.rows();
      vector<T> column;

    }

  };
}// namespace ANPI

#endif

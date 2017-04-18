
#include "Matrix.hpp"
#include <cmath>

using namespace std;
using namespace anpi;


template<typename T>
class algorithms{
public:
	algorithms();
	~algorithms();
	//Given L and U rebuilds A, computes the norm with the diff of A and the rebuild A
	T testLU(Matrix<T>& A, Matrix<T>& L, Matrix<T>& U);
	T testQR(Matrix<T>& A, Matrix<T>& Q, Matrix<T>& R);
private:
	int n;//
};

// --------------
// Implementation
// --------------
template<typename T>
algorithms<T>::algorithms(){
	n=2;
}

template<typename T>
T algorithms<T>::testLU(Matrix<T>& A, Matrix<T>& L, Matrix<T>& U){
	Matrix<double>*ans = new Matrix<double>((*A)-((*L)*(*U)));
	T err;
	T* end = (*ans)(0,0) + (ans->_rows*ans->_cols);
	for (T* ptr = (*ans)(0,0); ptr!=end ;++ptr) {
		err += (*ans)*(*ans);
	}
	return pow(err,1/n);
}

template<typename T>
T algorithms<T>::testQR(Matrix<T>& A, Matrix<T>& Q, Matrix<T>& R){
	Matrix<double>*ans = new Matrix<double>((*A)-((*Q)*(*R)));
	T err;
	T* end = (*ans)(0,0) + (ans->_rows*ans->_cols);
	for (T* ptr = (*ans)(0,0); ptr!=end ;++ptr) {
		err += (*ans)*(*ans);
	}
	return pow(err,1/n);
}

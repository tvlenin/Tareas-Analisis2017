
#include "Matrix.hpp"
#include <cmath>

using namespace std;
using namespace anpi;


template<typename T>
class test{
public:
	test();
	~test();
	//Given L and U rebuilds A, computes the norm with the diff of A and the rebuild A
	T testLU(Matrix<T>& A, Matrix<T>& L, Matrix<T>& U);
	T testQR(Matrix<T>& A, Matrix<T>& Q, Matrix<T>& R);
private:
	int n;
};

// --------------
// Implementation
// --------------
template<typename T>
test<T>::test(){
	n=2;
}

template<typename T>
T test<T>::testLU(Matrix<T>& A, Matrix<T>& L, Matrix<T>& U){
	Matrix<double>*ans = new Matrix<double>((*A)-((*L)*(*U)));
	T err;
	T* end = ans(0,0) + (ans->_rows*ans->_cols);
	for (T* ptr = ans(0,0); ptr!=end ;++ptr) {
		err += (*ans)*(*ans);
	}
	return pow(err,1/n);
}

template<typename T>
T test<T>::testQR(Matrix<T>& A, Matrix<T>& Q, Matrix<T>& R){

}

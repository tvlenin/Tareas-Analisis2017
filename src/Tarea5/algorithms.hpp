
#include "Matrix.hpp"
#include <cmath>
#include <vector>
#include "qr.h"

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
	bool solveQR(const Matrix<T>& A, vector<T>& x, const vector<T>& b);
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

template<typename T>
bool algorithms<T>::solveQR(const Matrix<T>& A, vector<T>& x, const vector<T>& b){
	const int Asize = A.cols();
	
	Matrix<T>*Q = new Matrix<T>(Asize,Asize,0.0);
	Matrix<T>*R = new Matrix<T>(Asize,Asize,0.0);
	Matrix<T>*C = new Matrix<T>(Asize,1.0,0.0);
	Matrix<T>*B = new Matrix<T>(Asize,1.0,0.0);
	//cout<<" Crea y comienza"<<endl;
	qr<T> *qrDecomposition  =  new qr<T>(A,*Q,*R);
	//cout<<" PAsa el push"<<endl;
	qrDecomposition->result();
	
	for(int i = 0; i < Asize; i++ ){
		(*B)(i,0) = b[i];
	}
	
	
	
	(*C) = ((*Q).transposed())*(*B);
	
	vector<T> c;
	for(int i = 0; i < Asize; i++ ){
		c.push_back((*C)(0,i));
	}
	
	
	
	for (int i = (Asize-1); i >= 0; i--){
		
		
		if(i == (Asize-1)){
			
			x.push_back((c[i])/((*R)(i,i)));
		}else{
			T sumTemp = 0;
			for(int j = 0; j <((Asize-1)-i); j++){
				sumTemp += ((*R)(i,(Asize-1)-j) * x[j]);
			}
			x.push_back((c[i]-sumTemp)/((*R)(i,i)));
		}
	}
	
	return 0;

	
}




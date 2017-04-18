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
    // get the norm of a vector
    T getNorm(const vector<T> vec){
      int sizeV = vec.size();
      T ans = 0;
      for (int i = 0; i < sizeV;i++){
        ans += pow(vec[i],2);
      }
      return sqrt(ans);
    }
	//get U vector
	
	vector<T> getU(vector<T> aVector){
		vector<T> Uvector;
		if (aVector[0] < 0){
			Uvector = aVector;
			Uvector[0] = Uvector[0] - getNorm(aVector);
		}else {
			Uvector = aVector;
			Uvector[0] = Uvector[0] + getNorm(aVector);
		}
		return Uvector;
	}
	
    //get de diferent qmatrix and put this on qMatrix vector
    void getQMatrix(vector<T> u,vector<T> a){
		T beta = 1/(getNorm(a)*(getNorm(a) + abs(a[0])));
		double vectSize = u.size();
		Matrix<T> *I = new Matrix<T>(vectSize);
		Matrix<T> *UU = new Matrix<T>(vectSize);
		(*UU) = mulTrans(u);
		(*UU).scale(beta);
		Matrix<T> *Q = new Matrix<T>((*I)-(*UU));
		
		qMatrix.push_back(*Q);
		
		
		//(*Q) = (I)- UU;
		
		
	}
	
	Matrix<T> mulTrans(vector<T> vectU ){
		int vectSize = vectU.size();
		
		Matrix<T> *U = new Matrix<T>(vectSize,vectSize,0.0);
		for(int i = 0; i<vectSize ; i++){
			for(int j = 0; j<vectSize ; j++){
				(*U)(i,j) = vectU[i] * vectU[j]; 				
			}	
		}
		return *U;
	}
	
	void result (){
		//getQMatrix(getU(A.getColumn(0)),A.getColumn(0));
		
			
	}

    qr(const Matrix<T>& A, Matrix<T>& Q, Matrix<T>& R){
		(R) = (A);
		int matrixSize = A.cols();
		//Matrix<double>*qTemp = new Matrix<double>(matrixSize,matrixSize,0.0);
		//Matrix<double>*rTemp = new Matrix<double>(matrixSize,matrixSize,0.0);

		
		for(int i = 0; i < (matrixSize-1); i++){
			if(i==0){
				getQMatrix(getU(R.getColumn(0)),R.getColumn(0));
				Q = qMatrix[0];
				R = Q * R;
			}
							
				
			}
					
		}
	

  };
}// namespace ANPI

#endif

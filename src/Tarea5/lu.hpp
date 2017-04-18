/*
 * TestFramework.hpp
 *
 *  Created on: Apr 17, 2017
 *      Author: fasm22
 */

#ifndef TESTFRAMEWORK_HPP_
#define TESTFRAMEWORK_HPP_

#include <iostream>
#include <vector>
#include "Matrix.hpp"

using namespace std;
using namespace anpi;

namespace anpi{

	template<typename T>
	class lu {
	public:
		lu(){};
		~lu(){};

		/**
		 * Performs the LU (Lower Upper) matrix decomposition
		 */
		void lu(const Matrix<T>* A, Matrix<T>* LU);

		bool solveLU(const Matrix<T>* A, std::vector<T> x, const std::vector<T> b);


		void showVector(std::vector<T> v){
		   cout<<'\n';
		   for(int j=0;j<v.size();++j)
			   cout<<setw(14)<<v[j];
		   cout<<'\n';
		}

	};


	template<typename T>
	void lu<T>::lu(const Matrix<T>* A, Matrix<T>* LU){
		int d = A->cols();
		for(int k=0; k<d; ++k){
			for(int i=k; i<d; ++i){
				T sum = 0.;
				for(int p=0; p<k; ++p){
					sum+=((*LU)(i,p))*((*LU)(p,k));
				}
				(*LU)(k,i) = (*A)(i,k)-sum;
			}
			for(int j=k+1; j<d; ++j){
				T sum = 0.;
				for(int p=0; p<k; ++p)
					sum+=((*LU)(k,p))*((*LU)(p,j));
				(*LU)(j,k)=((*A)(k,j)-sum)/(*LU)(k,k);
			}
		}
	}

	template<typename T>
	bool lu<T>::solveLU(const Matrix<T>* A, vector<T> x, std::vector<T> b){
		int d = A->cols();
		Matrix<double>* LU = new Matrix<double>(d,d,1);	//LU Matrix, initialize with 1.

		lu(A,LU); //Calculte the LU Matrix

		std::vector<T> y(d);
		for(int i=0; i<d; ++i){
			T sum=0.;
			for(int k=0; k<i; ++k){
				sum+=((*LU)(k,i))*y[k];
			}

			y[i]=(b[i]-sum)/((*LU)(i,i));
		}
		for(int i=d-1; i>=0; --i){
			T sum=0.;
			for(int k=i+1; k<d; ++k)
				sum+=((*LU)(k,i))*x[k];
			x[i]=(y[i]-sum);
		}

		showVector(x);
		return true;
	}
}



#endif /* TESTFRAMEWORK_HPP_ */

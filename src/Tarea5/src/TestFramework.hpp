/*
 * TestFramework.hpp
 *
 *  Created on: Apr 17, 2017
 *      Author: fasm22
 */

#ifndef TESTFRAMEWORK_HPP_
#define TESTFRAMEWORK_HPP_

#include <iostream>
#include <cmath>
#include <vector>
#include "Matrix.hpp"

using namespace std;
using namespace anpi;

namespace anpi{

	template<typename T>
	class TestFramework {
	public:
		TestFramework(){};
		~TestFramework(){};

		/**
		 * Performs the LU (Lower Upper) matrix decomposition
		 */
		void lu(const Matrix<T>* A, Matrix<T>* LU);

		bool solveLU(const Matrix<T>* A, std::vector<T> x, const std::vector<T> b);


		void showVector(std::vector<T> v){
		   cout<<'\n';
		   for(unsigned int j=0;j<v.size();++j)
			   cout<<setw(14)<<v[j];
		   cout<<'\n';
		}

		void invertLU(Matrix<T>* A, Matrix<T>* Ai);

	};

	struct ErrSingular:std::exception {
		const char* what() const noexcept {
			return "**ANPI: Matrix is singular. Operation Canceled. Det=0**\n";
		}
	};

	struct ErrNan:std::exception {
		const char* what() const noexcept {
			return "**ANPI: Matrix is not valid. And caused Not a Number exception **\n";
		}
	};

	struct ErrSize:std::exception {
			const char* what() const noexcept {
				return "**ANPI: Matrix is not valid. Col and Row number are not equal **\n";
			}
		};



	template<typename T>
	void TestFramework<T>::lu(const Matrix<T>* A, Matrix<T>* LU){
		int d = A->cols();

		try{
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

			//Verify if the Matrix is Singular
			T det = 1;
			for(int j = 1; j < d; j++){
				if((*LU)(j,j)==0)
					throw ErrSingular();
				det*=(*LU)(j,j);
			}
			if(std::isnan(det))
				throw ErrNan();
		}
		catch(exception& err){
			cout << err.what() << endl;
			exit(0);
		}
	}

	template<typename T>
	bool TestFramework<T>::solveLU(const Matrix<T>* A, vector<T> x, std::vector<T> b){
		int d = A->cols();
		int d2 = A->rows();
		try{
			if(d==d2){
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
			else{
				throw ErrSize();
			}
		}
		catch(exception& err){
			cout << err.what() << endl;
			exit(0);
		}
	}

	template<typename T>
	void TestFramework<T>::invertLU(Matrix<T>* A, Matrix<T>* Ai){
		int N = A->cols();
		int N2 = A->rows();
		try{
			if(N==N2){
				std::vector<T> tempCol(N);
				std::vector<T> tempRow(N);

				cout<<"INVERTED MATRIX: ";
				for(int j=0; j<N; j++){
					for(int i = 0; i<N; i++)
						tempCol[i]=0.;

					tempCol[j]=1.0;

					solveLU(A,tempRow,tempCol);
					//showVector(tempRow);
				}
			}
			else{
				throw ErrSize();
			}

		}
		catch(exception& err){
			cout << err.what() << endl;
			exit(0);
		}
	}
}



#endif /* TESTFRAMEWORK_HPP_ */

/*
 * TestList.hpp
 *
 *  Created on: Apr 18, 2017
 *      Author: fasm22
 */

#ifndef TESTLIST_HPP_
#define TESTLIST_HPP_

#include "Matrix.hpp"
#include "TestFramework.hpp"
#include <iostream>
using namespace anpi;

class TestList {
	public:
		TestList(){};
		~TestList(){};

		void showLU_InvertTests(){
			TestFramework<double>* test = new TestFramework<double>();
			Matrix<double>* A = new Matrix<double>(3,3,1);
			Matrix<double>* Ai = new Matrix<double>(3,3,1);


			double Avals[9]={1.,-1.,0.,
							 0.,1.,0.,
							 2.,0.,1.};

			A->initializeMatrix(Avals,3);

			test->invertLU(A,Ai);

		}

		void showLU_Tests(){
			TestFramework<double>* test = new TestFramework<double>();

			Matrix<double>* A = new Matrix<double>(3,3,1);
			Matrix<double>* LU = new Matrix<double>(3,3,1);
			Matrix<double>* B = new Matrix<double>(3,3,1);
			Matrix<double>* LU2 = new Matrix<double>(3,3,1);
			Matrix<double>* C = new Matrix<double>(3,3,1);
			Matrix<double>* LU3 = new Matrix<double>(3,3,1);


			double Avals[9]={1.,1.,0.,
							 -1.,1.,0.,
							 0.,0.,-0.5};

			double Bvals[9]={3.,3.,0.,
							 -3.,3.,0.,
							 0.,0.,-1.5};

			double Cvals[9]={5.,5.,5.,
							 5.,5.,5.,
							 5.,5.,5.};

			std::vector<double> b(3);
			std::vector<double> x(3);
			b[0] = 1.;
			b[1] = 1.;
			b[2] = 1.;

			std::vector<double> b2(3);
			std::vector<double> x2(3);
			b2[0] = 9.;
			b2[1] = 9.;
			b2[2] = 9.;

			std::vector<double> b3(3);
			std::vector<double> x3(3);
			b3[0] = 3.;
			b3[1] = 2.;
			b3[2] = 3.;


			cout<<"TEST 1"<<endl;
			cout<<"###################################"<<endl;
			A->initializeMatrix(Avals,3);
			cout<<"SOLVING Ax=b"<<endl;
			cout<<"MATRIX A:"<<endl;
			A->showMatrix();

			cout<<"Vector b:"<<endl;
			test->showVector(b);

			cout <<"LU: "<<endl;
			test->lu(A,LU);
			LU->showMatrix();

			cout<<"--Result--"<<endl;
			cout<<"Vector x:"<<endl;
			test->solveLU(A,x,b);
			cout<<"###################################"<<endl;
			cout<<"TEST 2"<<endl;
			cout<<"###################################"<<endl;
			B->initializeMatrix(Bvals,3);
			cout<<"SOLVING Bx=b"<<endl;
			cout<<"MATRIX B:"<<endl;
			B->showMatrix();

			cout<<"Vector b:"<<endl;
			test->showVector(b2);

			cout <<"LU: "<<endl;
			test->lu(B,LU2);
			LU2->showMatrix();

			cout<<"--Result--"<<endl;
			cout<<"Vector x:"<<endl;
			test->solveLU(B,x2,b2);
			cout<<"###################################"<<endl;
			cout<<"TEST 3"<<endl;
			cout<<"###################################"<<endl;
			C->initializeMatrix(Cvals,3);
			cout<<"SOLVING Cx=b"<<endl;
			cout<<"MATRIX C:"<<endl;
			C->showMatrix();

			cout<<"Vector b:"<<endl;
			test->showVector(b3);

			cout <<"LU: "<<endl;
			test->lu(C,LU3);
			LU2->showMatrix();

			cout<<"--Result--"<<endl;
			cout<<"Vector x:"<<endl;
			test->solveLU(C,x3,b3);
		}
};



#endif /* TESTLIST_HPP_ */

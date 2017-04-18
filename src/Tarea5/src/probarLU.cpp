
#include "Matrix.hpp"
#include <iostream>

#include "lu.hpp"
using namespace std;
using namespace anpi;


int main2(){

	lu<double>* test = new lu<double>();

    Matrix<double>* A = new Matrix<double>(5,5,1);

    double Avalues[25]={2.,1.,1.,3.,2.,
				 1.,2.,2.,1.,1.,
				 1.,2.,9.,1.,5.,
				 3.,1.,1.,7.,1.,
				 2.,1.,5.,1.,8.};

    std::vector<double> b(5);
    std::vector<double> x(5);
    b[0] = -2.;
    b[1] = 4.;
    b[2] = 3.;
    b[3] = -5.;
    b[4] = 1.;

    A->initializeMatrix(Avalues,5);
    cout<<"SOLVING Ax=b"<<endl;
    cout<<"MATRIX A:"<<endl;
    A->showMatrix();

    cout<<"VECTOR b:"<<endl;;
    test->showVector(b);

    cout<<"-----------------"<<endl;
    cout<<"Results:"<<endl;
    cout<<"Vector x:"<<endl;
    test->solveLU(A,x,b);


}



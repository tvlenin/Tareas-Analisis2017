//============================================================================
// Name        : Tareas-Analisis2017.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace std;

template < class T, class T1>
T1 biseccion( T Fx, T1 Xi, T1 Xu){

	double Xr = 0.0;

	while(Fx(Xi)*Fx(Xu) != 0){// Hasta que la diferencia de acercamientos sea 0

		Xr = (Xi + Xu)/2; //calcula un nuevo acercamiento en cada iteracion

		if(Fx(Xi)*Fx(Xr) > 0){ //verifica si el nuevo acercamiento es por la derecha
				Xi = Xr;
		}
		else if(Fx(Xi)*Fx(Xr) < 0){ //verifica si el nuevo acercamiento es por la izquierda
				Xu = Xr;
		}
		else
			break;
	}
	cout << Xr<<endl;// Imprime el resultado final de la raiz

	return Xr;
}


template <class P, class P1>
P1 interpolacion (P Fx, P1 Xi, P1 Xu){

	double Xr = 0.0;

	//while(Fx(Xi)*Fx(Xu) != 0){// Hasta que la diferencia de acercamientos sea 0
	for(int i = 0; i<20 ; i++ ){
		Xr = Xu-((Fx(Xu)*(Xi-Xu))/(Fx(Xi)-Fx(Xu))); //calcula un nuevo acercamiento en cada iteracion
		if(Fx(Xi)*Fx(Xr) > 0){ //verifica si el nuevo acercamiento es por la derecha
				Xi = Xr;
		}
		else if(Fx(Xi)*Fx(Xr) < 0){ //verifica si el nuevo acercamiento es por la izquierda
				Xu = Xr;
		}
		else
			break;
	}
	cout << Xr<<endl;// Imprime el resultado final de la raiz

	return Xr;


}







#define JMAX 20
/*
 * [X1, X2] intervalo
 * xacc precision
 * */
//template <class T>
float rtnewt (void (*funcd)(float, float *, float *), float x1, float x2,float xacc){
	void nrerror(char error_text[]);
	int j;
	float df,dx,f,rtn;
	rtn=0.5*(x1+x2); //Initial guess.
	for (j=1;j<=JMAX;j++) {
		(*funcd)(rtn,&f,&df);
		dx=f/df;
		rtn -= dx;
		if ((x1-rtn)*(rtn-x2) < 0.0)
			cout<<"Jumped out of brackets in rtnewt\n";
			return 0;
			//nrerror("Jumped out of brackets in rtnewt");
		if (fabs(dx) < xacc)
			return rtn; //Convergence.
	}
	cout<<"Maximum number of iterations exceeded in rtnewt\n";
	//nrerror("Maximum number of iterations exceeded in rtnewt");
	return 0.0; //Never get here.
}



//template <class P, class P1>
//P1 interpolacion (P Fx, P1 Xi, P1 Xu){
template <class F, class T>
T n_r(F func, T x1, T x2, T xacc){
	T err=1;
	T ans=0;
	while(err>xacc){

	}
	return ans;
}


int main() {

	struct Square {
		double operator()(const double x) {
			return 5*x-3;
		}
		double operator()(const int n,const double x) {
			return 5;
		}
	};

	Square s1;
	s1(2);
	double x1 = -1;
	double x2 = 2;
	double err = 0.01;

	double ans = n_r(2.0, x1, x2, err);
	cout<<"Respuesta: "<<ans<<" ."<<endl;
	return 0;
}



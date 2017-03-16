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





#include "nrutil.h"
#define ITMAX 100 //Maximum allowed number of iterations.
#define EPS 3.0e-8 //Machine floating-point precision.

template<class F, class T>
T brent(F func, T x1, T x2, T tol){
	int iter;
	T a=x1,b=x2,c=x2,d,e,min1,min2;
	T fa=func(a);
	T fb=func(b);
	T fc,p,q,r,s,tol1,xm;
	if ((fa > 0.0 && fb > 0.0) || (fa < 0.0 && fb < 0.0))
		cout<<"Root must be bracketed in zbrent\n";
		//nrerror("Root must be bracketed in zbrent");
	fc=fb;
	for(iter=1;iter<=ITMAX;iter++){
		if ((fb > 0.0 && fc > 0.0) || (fb < 0.0 && fc < 0.0)) {
			c=a; //Rename a, b, c and adjust bounding interval
			fc=fa; //d.
			e=d=b-a;
		}if (fabs(fc) < fabs(fb)) {
			a=b;
			b=c;
			c=a;
			fa=fb;
			fb=fc;
			fc=fa;
		}
		tol1=2.0*EPS*fabs(b)+0.5*tol; //Convergence check.
		xm=0.5*(c-b);
		if (fabs(xm) <= tol1 || fb == 0.0)
			return b;
		if (fabs(e) >= tol1 && fabs(fa) > fabs(fb)) {
			s=fb/fa; //Attempt inverse quadratic interpolation.
			if (a == c) {
				p=2.0*xm*s;
				q=1.0-s;
			} else {
				q=fa/fc;
				r=fb/fc;
				p=s*(2.0*xm*q*(q-r)-(b-a)*(r-1.0));
				q=(q-1.0)*(r-1.0)*(s-1.0);
			}
			if (p > 0.0) q = -q; //Check whether in bounds.
				p=fabs(p);
			min1=3.0*xm*q-fabs(tol1*q);
			min2=fabs(e*q);
			if (2.0*p < (min1 < min2 ? min1 : min2)) {
				e=d; //Accept interpolation.
				d=p/q;
			} else {
				d=xm; //Interpolation failed, use bisection.
				e=d;
			}
		}else {// Bounds decreasing too slowly, use bisection.
			d=xm;
			e=d;
		}
		a=b; //Move last best guess to a.
		fa=fb;
		if (fabs(d) > tol1) //Evaluate new trial root.
				b += d;
		else
			b += SIGN(tol1,xm);
		fb=fb=func(b);
	}
	cout<<"Maximum number of iterations exceeded in zbrent\n";
	//nrerror("Maximum number of iterations exceeded in zbrent");
	return 0.0; //Never get here.
}

template <class F, class T>
T n_r(F func, T x1, T xacc){
	T ans=0;
	while(ans>xacc){
		x1=x1-(func(x1)/func(1,x1));
		ans=func(x1);
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

	double x1 = -1.0;
	double x2 = 4.0;
	double err = 0.01;
	double ans = interpolacion(s1, x1, x2);
	cout<<"Respuesta: "<<ans<<" ."<<endl;
	return 0;
}



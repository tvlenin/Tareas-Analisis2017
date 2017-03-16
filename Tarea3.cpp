//============================================================================
// Name        : Tarea3.cpp
// Author      : Lenin Torres/ Abraham Arias/ Fabian Solano
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "math.h"
//#include "Tarea3.h"
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







template <class S>
int prueba(S xs){

	return xs(3);
}


int main() {

	struct Square {
		double operator()(const double x) {
			return 5*x-3;
		}
	};

	double a = 0.01;
	double b = 5.1;
		Square s;


	 float error=0.00001,x2,Ea;
	 float x0 = a;
	 float x1 = b;

	 Ea=error+1;
	 while (Ea>error)
	 {x2=(x1-((x0-x1)/(s(x0)-s(x1))*s(x1)));
	 printf ("%f \n",x2);
	 Ea=(fabs (x1-x2));
	 x0=x1;
	 x1=x2;
	 }
	 printf ("la raiz es:%f \n",x2);
































	double c = biseccion(s,a,b);
	double ce = interpolacion(s,a,b);




	return 0;
}

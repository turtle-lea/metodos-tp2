#include <vector>
#include <iostream>
#include <fstream>
#include "../include/bridge.h"
using namespace std;

void Bridge::mostrar(){
	banda->mostrar();
}


double Bridge::max_valor(vector<double>& fuerzas){
	double res = 0;
	for(int i=0; i<fuerzas.size(); i++){
		if(abs(fuerzas[i])>res){
			res = abs(fuerzas[i]);
		}
	}
	return res;
}

bool Bridge::seguro(){
	return max_modulo > max_fuerza_obtenida;
}

void Bridge::heuristica(){
	if(seguro()){

	} else{
		int i=0;
		double max = 0;
		for(int j=0; j<cargas.size(); j++){
			if(abs(cargas[j] > max)){
				i=j;
				max = abs(cargas[j]);
			}
		}
		vector<double> c_1;
		for(int j=0; j<i;j++){
			c_1.push_back(cargas[j]);
			cout << "cargas: " << cargas[j] << endl;
		}
		cout << endl;
		vector<double> c_2;
		for(int j=i+1;j<cargas.size();j++){
			c_2.push_back(cargas[j]);
			cout << "cargas: " << cargas[j] << endl;
		}
		cout << "Tams: " << (i+1) << " " << cargas.size()-i << endl;
		cout << endl;
		double l_1 = (l/n)*(i+1);
		cout << "l_1: " << l_1 << endl;
		double l_2 = (l/n)*(cargas.size()-i);
		cout << "l_2: " << l_2 << endl;

		Bridge b_izq(l_1,h,(i+1),c_1,max_modulo,costo_pilar);
		Bridge b_der(l_2,h,(cargas.size()-i),c_2,max_modulo,costo_pilar);

		vector<double> x_1 = b_izq.resolver_sistema();
		vector<double> x_2 = b_der.resolver_sistema();
		cout << b_izq.max_fuerza_obtenida;
		cout << endl;
		cout << b_der.max_fuerza_obtenida;
		cout << endl;
	}

}




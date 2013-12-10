#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include "../include/bridge.h"
#include "../include/BandMatrix.h"

using namespace std;

pair<double,int> max(vector<double>& fuerzas){
	pair<double,int> res;
	double max = 0;
	for(int i=0; i<fuerzas.size(); i++){
		if(abs(fuerzas[i])>max){
			max = abs(fuerzas[i]);
			res.first = max;
			res.second = i;
		}
	}
	return res;
}

int main(){
	double l, h, max_mod, c_pilar, aux;
	int n;
	vector<double> cargas;
	vector<double> fuerzas;
	char c;
	cin >> c;
	while(c != '#'){
		cin.putback(c);
		cin >> l;
		cin >> h;
		cin >> n;
		for(int i=0; i< n-1; i++){
			cin >> aux;
			cargas.push_back(aux);
		}
		cin >> max_mod;
		cin >> c_pilar;
		cin >> c;
	}
	Bridge tito_puente(l,h,n,cargas,max_mod,c_pilar);
	// fuerzas = tito_puente.resolver_sistema();
	// res = max(fuerzas);
	pair< pair<double,bool>, vector<int> > res = tito_puente.heuristica();

	pair<double,bool> x = res.first;
	cout << "El puente es: " << x.second << "seguro" << endl;
	
	vector<int> y = res.second;
	for(int i=0; i<y.size(); i++){
		cout << y[i] << endl;
	}

	cout << "El costo total del puente es: " << x.first << endl;
	cout << "Cant pilares: " << y.size() << endl;
	return 0;
}

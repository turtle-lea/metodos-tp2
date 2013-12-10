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
	pair<double,int> res;
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
	cout << "Res: " << tito_puente.max_f_obt() << endl;
	// fuerzas = tito_puente.resolver_sistema();
	// for(int i=0; i<fuerzas.size(); i++){
		// cout << fuerzas[i] << endl;
	// }
	// res = max(fuerzas);
	// cout << res.first << " " << res.second << endl;
	// tito_puente.heuristica();
	return 0;
}

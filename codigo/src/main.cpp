#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include "../include/bridge.h"
#include "../include/BandMatrix.h"

using namespace std;

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
	bool esSeguro = x.second;

	if(esSeguro){
		cout << "El puente resultante es seguro" << endl;
	}else{
		cout << "Cuidado ! La estructura resultante no es segura" << endl;
	}
	cout << endl;

	vector<int> y = res.second;

	cout << "El costo total del puente es: " << x.first << endl;
	cout << "La cantidad de pilares insertados es: " << y.size() << endl;
	cout << endl;

	if(y.size() == 0){
		cout << "Como se insertaron 0 pilares mostramos la solución del sistema:" << endl;
		cout << endl;

		vector<double> sol = tito_puente.sol_sist();	
		for(int i=0; i<sol.size(); i++){
			cout << sol[i] << endl;
		}
	}
	return 0;
}

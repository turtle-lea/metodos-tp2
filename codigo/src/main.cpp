#include<iostream>
#include<fstream>
#include<vector>
#include "../include/bridge.h"
#include "../include/BandMatrix.h"

using namespace std;

int main(){
	double l, h, aux;
	int n;
	vector<double> cargas;
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
		cin >> c;
	}
	Bridge tito_puente(l,h,n,cargas);
	tito_puente.mostrar();
	return 0;
}

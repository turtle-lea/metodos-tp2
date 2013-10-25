#include <iostream>
#include <fstream>
#include <vector>
#include "../include/bridge.h"
#include "../include/BandMatrix.h"

using namespace std;

int main(){

	vector<double> cargas;
	vector<double> res;
	
	double step = 0.5;
	double span_inicial = 10; 	///10m
	double span_max = 1000;	///1km
	int n = 2;
	int n_max = 100;
	//~ char c;
	//~ cin >> c;
	//~ while(c != '#'){
		//~ cin.putback(c);
		//~ cin >> l;
		//~ cin >> h;
		//~ cin >> n;
		//~ for(int i=0; i< n-1; i++){
			//~ cin >> aux;
			//~ cargas.push_back(aux);
		//~ }
		//~ cin >> c;
	//~ }
	
	for(double i = span_inicial; i < span_max; i = i + step){
		
	
	
	Bridge tito_puente(l,h,n,cargas);

	res = tito_puente.resolver_sistema();

	for(int i=0; i<res.size(); i++){
		cout << res[i] << endl;
	}
	
	return 0;
}

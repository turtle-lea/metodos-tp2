#include <vector>
#include <iostream>
#include <fstream>
#include "../include/bridge.h"
using namespace std;

void Bridge::mostrar(){
	cout << h << " " << l << " " << n << endl;	
	for(int i=0; i<cargas.size(); i++){
		cout << cargas[i] << endl;
	}
}





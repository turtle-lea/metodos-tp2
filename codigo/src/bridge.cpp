#include <vector>
#include <iostream>
#include <fstream>
#include "../include/bridge.h"
using namespace std;

void Bridge::mostrar(){
	
	/*cout << "altura " << h << ", longitud " << l << ", " << n << " secciones."<< endl;	
	cout << "cargas: ";
	for(int i=0; i<cargas.size(); i++){
		cout << cargas[i] << " ";
	}
	cout << endl;
	*/
	banda->mostrar();
	//~ banda->mostrar2(cout);
	
}





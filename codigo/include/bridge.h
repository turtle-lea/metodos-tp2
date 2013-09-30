#ifndef BRIDGE_H
#define BRIDGE_H

#include <vector>
using namespace std;

class Bridge{
	public:
		Bridge(double altura,double largo,int secciones,vector<double> cs) : h(altura), l(largo), n(secciones), cargas(cs) {}
		void mostrar();
	private:
		int h;
		int l;
		int n;
		vector<double> cargas;		
};

#endif

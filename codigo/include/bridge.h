#ifndef BRIDGE_H
#define BRIDGE_H

#include <vector>
#include <cmath>
using namespace std;

class Bridge{
	public:
		Bridge(double altura,double largo,int secciones,vector<double> cs) : h(altura), l(largo), n(secciones), cargas(cs) {
			double adyacente_theta_1 = largo/secciones;
			double opuesto_theta_2 = adyacente_theta_1;
			double adyacente_thetha_2 = altura;
			double opuesto_theta_1 = altura;
			
			double hipotenusa = sqrt((adyacente_theta_1 * adyacente_theta_1) + (opuesto_theta_1 * opuesto_theta_1));
			
			cos_theta_1 = adyacente_theta_1/hipotenusa;
			sen_theta_1 = opuesto_theta_1/hipotenusa;
			
			cos_theta_2 = adyacente_theta_2/hipotenusa;
			sen_theta_2 = opuesto_theta_2/hipotenusa;
			
			///ya tenemos eso (cos y sen de theta)
			
			
			
		}
		void mostrar();
	
	private:
		int h;
		int l;
		int n;
		double cos_theta_1;
		double sen_theta_1;
		double cos_theta_2;
		double cos_theta_2;
		vector<double> cargas;		
};

#endif

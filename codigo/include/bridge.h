#ifndef BRIDGE_H
#define BRIDGE_H

#include <vector>
#include <cmath>
#include "BandMatrix.h"
#include <utility>

using namespace std;

class Bridge{
	public:
		Bridge(double largo,double altura,int secciones,vector<double> cs, double max, double c_pilar) : 
			h(altura), l(largo), n(secciones), cargas(cs), max_modulo(max), costo_pilar(c_pilar) {
			double adyacente_theta_1 = largo/secciones;
			double opuesto_theta_2 = adyacente_theta_1;
			double adyacente_theta_2 = altura;
			double opuesto_theta_1 = altura;
			
			double hipotenusa = sqrt((adyacente_theta_1 * adyacente_theta_1) + (opuesto_theta_1 * opuesto_theta_1));
			
			cos_theta_1 = adyacente_theta_1/hipotenusa;
			sen_theta_1 = opuesto_theta_1/hipotenusa;
			
			cos_theta_2 = adyacente_theta_2/hipotenusa;
			sen_theta_2 = opuesto_theta_2/hipotenusa;
			
			///ya tenemos eso (cos y sen de theta)
			
			longitud_total = (2*n-2)*(l/n) + (n-1)*h + n*sqrt((l/n)*(l/n)+h*h);

			banda = new BandMatrix(cos_theta_1, sen_theta_1, cos_theta_2, sen_theta_2, 4*secciones, cargas);
			vector<double> x = resolver_sistema();
			max_fuerza_obtenida = max_valor(x);
		}
		
		~Bridge(){
			delete banda;
		}
		
		void mostrar();
		vector<double> resolver_sistema(){return banda->resolver_sistema();}
		double max_valor(vector<double>& fuerzas);
		bool seguro();
		void heuristica();
		double max_f_obt(){return max_fuerza_obtenida;}

	private:
		double h;
		double l;
		int n;
		double cos_theta_1;
		double sen_theta_1;
		double cos_theta_2;
		double sen_theta_2;
		double max_modulo;	
		double costo_pilar;
		double longitud_total;
		BandMatrix* banda;
		
		double max_fuerza_obtenida;

		vector<double> cargas;		
};

#endif

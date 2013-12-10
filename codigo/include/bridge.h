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
			sol_sistema = resolver_sistema();
			max_fuerza_obtenida = max_valor(sol_sistema);
			pilares_insertados = 0;
		}
		
		~Bridge(){
			delete banda;
		}
		
		vector<double> resolver_sistema(){return banda->resolver_sistema();}
		double max_valor(vector<double>& fuerzas);
		double costo_puente(){return longitud_total*max_fuerza_obtenida;}
		int cant_pilares(){return pilares_insertados;}
		bool seguro();

		pair< pair<double,bool>, vector<int> > heuristica();
		pair<double,bool> heuristica_aux(vector<int>&);

		double max_f_obt(){return max_fuerza_obtenida;}
		vector<double> sol_sist(){return sol_sistema;}

		int calcular_indice_insercion();
		bool todas_iguales();

	private:
		double h;
		double l;
		int n;
		int pilares_insertados;
		double cos_theta_1;
		double sen_theta_1;
		double cos_theta_2;
		double sen_theta_2;
		double max_modulo;	
		double costo_pilar;
		double longitud_total;
		BandMatrix* banda;
		
		double max_fuerza_obtenida;
		vector<double> sol_sistema;		

		vector<double> cargas;		
};

#endif

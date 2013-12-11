#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include "../include/BandMatrix.h"
using namespace std;

BandMatrix::BandMatrix(double cos_theta_1,double sen_theta_1, 
	double cos_theta_2,double sen_theta_2, int n, vector<double> cargas){
	vector<double> v;
	for(int i = 0; i < n; i++){
		elem.push_back(v);
		for(int j = 0; j < 11; j++){
			elem[i].push_back(0.0);
		}
	}
	
	if(n==8){
		cargar_n_igual_2(cos_theta_1,sen_theta_2,cos_theta_2,sen_theta_2,n,cargas);
	}else{	
		cargar_n_mayor_2(cos_theta_1,sen_theta_2,cos_theta_2,sen_theta_2,n,cargas);
	}

	b.push_back(0.0);
	b.push_back(0.0);
	for(int i = 0; i < (n-4)/2; i++){
		if((i%2) == 0){
			b.push_back(0.0);
			b.push_back(-cargas[i/2]);
		}else{
			b.push_back(0.0);
			b.push_back(0.0);
		}
	}
	b.push_back(0.0);
	b.push_back(0.0);
}

void BandMatrix::cargar_n_mayor_2(double cos_theta_1,double sen_theta_1, double cos_theta_2,double sen_theta_2, int n, vector<double>& cargas){
	/** C0_h */
	elem[0][3] = 1; //F0 = h0
	elem[0][5] = 1; //F2
	elem[0][6] = cos_theta_1; //cos(theta1)F3
	
	/** C0_v */
	elem[1][3] = 1; //F1
	elem[1][5] = sen_theta_1; //sen(theta2)F3
	
	/** C1_h -> F2 y F5*/
	elem[2][3] = -1; //F2
	elem[2][6] = 1; //-F5
	
	/** C1_v -> F4*/
	elem[3][4] = 1; //F4
	
	/** C2_h -> F3 F6 F7*/
	elem[4][2] = -sen_theta_2; // - sen(theta2)*F3
	elem[4][5] = sen_theta_2; //F2
	elem[4][6] = 1; //+F7
	
	/** C2_v -> F3 F4 F6*/
	elem[5][1] = -cos_theta_2; //-F4
	elem[5][2] = -1; //-cos(theta2)F3
	elem[5][4] = -cos_theta_2; //-cos(theta2)F6

	int estoy_abajo;
	for(int i = 6; i < (n/2)-2 ; i = i+2){
		estoy_abajo = i % 4;
		int j = i+1;
		if(estoy_abajo != 0){
			//horizontales
			elem[i][2] = -1; //-Fi-1 
			elem[i][3] = -cos_theta_1; //-cos(theta1)Fi
			elem[i][6] = 1; //+Fi+3
			//verticales
			elem[j][2] = sen_theta_1; //sen(theta1)Fj-1
			elem[j][4] = 1; //Fj+1
		}else{
			//horizontales
			elem[i][2] = -1; //-Fi-1 
			elem[i][5] = sen_theta_2; //sen(theta2)Fi+2
			elem[i][6] = 1; //+Fi+3
			//verticales
			elem[j][2] = -1; //-Fj-1
			elem[j][4] = -cos_theta_2; //-cos(theta2)Fj+1	
		}
	}
	
	/** C n/4 -1_h  **/
	int medio = n/2 - 2;
	elem[medio][2] = -1; //-Fmedio-1
	elem[medio][3] = -cos_theta_1; //-cos(theta1)Fmedio
	elem[medio][6] = 1; //Fmedio+3
	elem[medio][7] = cos_theta_1; //cos(theta1)Fmedio+4
		
	/** C n/4 -1_v */
	medio++;
	elem[medio][2] = sen_theta_1; //sen(theta1)Fmedio-1	
	elem[medio][4] = 1; //Fmedio+1
	elem[medio][6] = sen_theta_1; //sen(theta1)Fmedio+3
	
	/** C n/4_h */
	medio++; 
	elem[medio][2] = -1; // -Fmedio-1
	elem[medio][6] = 1; // Fmedio+3

	
	/** C n/4_v */
	medio++;
	elem[medio][2] = -1; //-Fmedio-1
	
	medio++;

	for(int i = medio ; i < n-6 ; i = i+2){
		estoy_abajo = i % 4;
		int j = i+1;
		if(estoy_abajo != 0){
			//horizontales
			elem[i][2] = -1; //-Fi-1 
			elem[i][6] = 1; // Fi+3
			elem[i][7] = cos_theta_1; // cos(theta1)Fi+4
			//verticales
			elem[j][4] = 1; //Fj+1
			elem[j][6] = sen_theta_1; //sen(theta1)Fj+3
		}else{
			//horizontales
			elem[i][1] = -sen_theta_2; //-sen(theta2)Fi-2
			elem[i][2] = -1; //-Fi-1 
			elem[i][6] = 1; //+Fi+3
			//verticales
			elem[j][0] = -cos_theta_2; //-cos(theta2)Fj-3	
			elem[j][2] = -1; //-Fj-1
		}
	}
	
	/** Cn/2-3_h */
	elem[n-6][2] = -1; //-Factual-1
	elem[n-6][6] = 1; //Factual+3
	
	/** Cn/2-3_v */
	elem[n-5][4] = 1; //Factual+1
	
	/** Cn/2-2_h */
	elem[n-4][1] = -sen_theta_2; //-sen(theta2)Factual-2
	elem[n-4][2] = -1; //-Factual-1
	elem[n-4][5] = sen_theta_2; //sen(theta2)Factual+2
	
	/** Cn/2-2_v */ 
	elem[n-3][0] = -cos_theta_2; //-cos(theta2)Factual-3
	elem[n-3][2] = -1; //-Factual-1
	elem[n-3][4] = -cos_theta_2; //-cos(theta2)Factual+1
	
	/** Cn/2-1_h */
	elem[n-2][2] = -1; // -Factual-1
	elem[n-2][3] = -cos_theta_1; // -cos(theta1)Factual

	/** Cn/2-1_v */
	elem[n-1][2] = sen_theta_1; //sen(theta1)Factual-1
	elem[n-1][3] = 1; //Factual
	
	/** Construida la matriz rectangular elem */
	/** Construimos el vector b acorde a la matriz */
}

void BandMatrix::cargar_n_igual_2(double cos_theta_1,double sen_theta_1, double cos_theta_2,double sen_theta_2, int n, vector<double>& cargas){

	/** C0_h */
	elem[0][3] = -1; //F0 = h0
	elem[0][5] = 1; //F2
	elem[0][6] = cos_theta_1; //cos(theta1)F3
	
	/** C0_v */
	elem[1][3] = 1; //F1
	elem[1][5] = sen_theta_1; //sen(theta2)F3
	
	/** C1_h -> F2 y F5*/
	elem[2][3] = -1; //F2
	elem[2][6] = 1; //-F5
	
	/** C1_v -> F4*/
	elem[3][4] = 1; //F4
	
	/** C2_h -> F3 F6 F7*/
	elem[4][2] = -sen_theta_2; // - sen(theta2)*F3
	elem[4][5] = sen_theta_2; //F2
	
	/** C2_v -> F3 F4 F6*/
	elem[5][1] = -cos_theta_2; //-F4
	elem[5][2] = -1; //-cos(theta2)F3
	elem[5][4] = -cos_theta_2; //-cos(theta2)F6

	/** Cn/2-1_h */
	elem[n-2][2] = -1; // -Factual-1
	elem[n-2][3] = -cos_theta_1; // -cos(theta1)Factual

	/** Cn/2-1_v */
	elem[n-1][2] = sen_theta_1; //sen(theta1)Factual-1
	elem[n-1][3] = 1; //Factual
}

void BandMatrix::mostrar(){
	for(int i = 0; i < elem.size(); i++){
		for(int j = 0; j < 11; j++){
			cout << elem[i][j] << "\t || ";
		}
		cout << endl;
	}
}

void BandMatrix::mostrar2(ostream& os)
{
	m_imprimir(elem,os);
}

void BandMatrix::mostrar2(ofstream& os)
{
	m_imprimir(elem, os);
}

vector<double> BandMatrix::resolver_sistema(){
	vector<double> res;
	vector<int> diagonales;
	double e = 0.0000000001;
	int n = b.size();

	inicializar_estructuras(res,diagonales,n);

	//Algoritmo de triangulacion de matriz:	
	for(int i=0; i<n; i++){
		if(hayQueIterar(i,diagonales,e)){
			double elem_diagonal = elem[i][diagonales[i]];			
			if(abs(elem_diagonal)<e){
				double max = abs(elem_diagonal);
				int k_max = 0;
	
				//Encuentro la fila para swapear
				for(int k=0; k<=3 && ((k+i)<n); k++){
					if((diagonales[i+k]-k)>=0){
						if(abs(elem[i+k][diagonales[i+k]-k]) > abs(max)){
							k_max = k;
							max = abs(elem[i+k][diagonales[i+k]-k]);
						} 
					}
				}
						
				//swapeo fila i con fila k_max +i 
				vector<double> aux;
				aux = elem[k_max+i];	
				elem[k_max+i] = elem[i];
				elem[i] = aux;
	
				int aux_2;
				aux_2 = diagonales[i];
				diagonales[i] = diagonales[k_max+i] - k_max;	
				diagonales[k_max+i] = aux_2+k_max;	
				
				//swapeo el vector b
				double aux_3;
				aux_3 = b[k_max+i];
				b[k_max+i] = b[i];
				b[i] = aux_3;
			
			}
			for(int j=1;(j<=3) && (i+j)<n;j++){
				//Calculo el multiplicador
				if(abs(elem[i+j][diagonales[i+j]-j]) > e){
					int h = diagonales[i];
					int q = diagonales[i+j]-j;
					double m = elem[i+j][q]/elem[i][h];
					//Realizo el iésimo paso
					while(h<11 && q<11){
						elem[i+j][q] = elem[i+j][q] - m*elem[i][h];
						h++; q++;
					}
				
					//Modifico el vector b
					b[i+j] = b[i+j] - m*b[i];
				}
			}
		}
	}

	backward_substitution(res, diagonales);
	return res;
}


void BandMatrix::backward_substitution(vector<double>& res, vector<int> diagonales){
	int n = b.size();

	vector<double> nuevo;
	for(int i=0; i<res.size();i++){
		nuevo.push_back(0.0);
	}

	double acum;
	for(int i=n-1; i>=0; i--){
		acum = 0.0;
		for(int j=1; j<= 7; j++){
			if(i+j<n){
				if((diagonales[i]+j) < 10){
					acum += elem[i][diagonales[i]+j]*res[i+j];
				}
			}	
		}
		res[i] = (b[i]-acum)/elem[i][diagonales[i]];
	}
	
}


bool BandMatrix::hayQueIterar(int i,const vector<int>& diagonales, double e){
	bool hayQueIterar = false;
	for(int j=1; j< 4 && i+j<diagonales.size(); j++){
		if( diagonales[i+j]-j >= 0){
			if( abs(elem[i+j][diagonales[i+j]-j]) > e){
				hayQueIterar = true;
				break;
			}
		}
	}
	return hayQueIterar;
}


void BandMatrix::inicializar_estructuras(vector<double>& res, vector<int>& diagonales, int n){
	double no_inicializado = -999999.999999;
	for(int i=0; i< n; i++){
		res.push_back(no_inicializado);
	}
	for(int i=0; i < n; i++){
		diagonales.push_back(3);
	}
}
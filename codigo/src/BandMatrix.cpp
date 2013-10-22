#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include "../include/BandMatrix.h"
using namespace std;

BandMatrix::BandMatrix(double cos_theta_1,double sen_theta_1, double cos_theta_2,double sen_theta_2, int n, const vector<double> cargas){
	vector<double> v;
	for(int i = 0; i < n; i++){
		elem.push_back(v);
		for(int j = 0; j < 11; j++){
			elem[i].push_back(0.0);
		}
	}
	/// elem \in R^(n*8)
	
	//filas 0..n-1  !! columnas 0..7
	//columna 3 = diagonal
	
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
	elem[5][1] = -1; //-F4
	elem[5][2] = -cos_theta_2; //-cos(theta2)F3
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
	
	/** C n/4 -1_h -> F9 F10 F14 F13*/
	int medio = n/2 - 2;
	elem[medio][2] = -1; //-Fmedio-1
	elem[medio][3] = -cos_theta_1; //-cos(theta1)Fmedio
	elem[medio][6] = 1; //Fmedio+3
	elem[medio][7] = cos_theta_1; //cos(theta1)Fmedio+4
		
	/** C n/4 -1_v -> F10 F12 F14*/
	medio++;
	elem[medio][2] = sen_theta_1; //sen(theta1)Fmedio-1	
	elem[medio][4] = 1; //Fmedio+1
	elem[medio][6] = sen_theta_1; //sen(theta1)Fmedio+3
	
	/** C n/4_h -> F11 F15*/
	medio++; 
	elem[medio][2] = -1; // -Fmedio-1
	elem[medio][6] = 1; // Fmedio+3

	
	/** C n/4_v -> F12*/
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
			elem[i][1] = sen_theta_2; //-sen(theta2)Fi-2
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
	
	/* b = [0,0,0,c1,0,c2,0,c3...,0,cn/2-1,0,0] */
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

bool BandMatrix::hayQueIterar(int i,const vector<int>& diagonales, double e){
	bool hayQueIterar = false;
	for(int j=1; j< 4 && i+j<diagonales.size(); j++){
		if( abs(elem[i+j][diagonales[i+j]-j]) > e){
			hayQueIterar = true;
			break;
		}
	}
	return hayQueIterar;
}
vector<double> BandMatrix::resolver_sistema(){
	vector<double> res_swaps;
	vector<double> res;
	vector<int> diagonales;
	double no_inicializado = -999999.0707;
	double elem_diagonal;
	int k = 0; int j; int h; int q;
	vector<double> aux;
	double aux_2;
	double m;

	//Defino epsilon como 10**(-10)
	double e = 0.0000000001;
	int n = b.size();

	//Inicializo vector res	y res_swaps
	for(int i=0; i< n; i++){
		res.push_back(no_inicializado);
	}
	for(int i=0; i < n; i++){
		res_swaps.push_back(i);		
	}

	for(int i=0; i < n; i++){
		diagonales.push_back(3);
	}

	//Algoritmo de triangulacion de matriz:	
	for(int i=0; i<n; i++){
		elem_diagonal = elem[i][diagonales[i]];			
		
		if(hayQueIterar(i,diagonales,e)){
			
			if (abs(elem_diagonal) < e){
				//Fijarse si hace falta swapear.
				k=1;	
				//Encuentro la fila para swapear
				while(k<=3 && (k+i < n)){
					//~ if(abs(elem[i+k][3-k]) > e) break;
					if(abs(elem[i+k][diagonales[i+k]-k]) > e) break;
					k++;
				}
				
				//swapeo fila i con fila k+i
				aux = elem[k+i];	
				elem[k+i] = elem[i];
				elem[i] = aux;

				diagonales[i] -= k;	
				diagonales[k+i] += k;	
				//imprimo fila i
				
				//swapeo elem i de b con elem k+i
				aux_2 = b[k+i];
				b[k+i] = b[i];
				b[i] = aux_2;
				
				//Guardo info equivalente a la matriz de permutacion
				res_swaps[i] = k+i;
				res_swaps[k+i] = i;
			}
			
			j=1;
			while(j<=3 && i+j<n){
				//si estoy en la fila que swapee
				 if(j!=k){
					//Calculo el multiplicador
					if(abs(elem[i+j][diagonales[i+j]-j]) >e){
						h = diagonales[i];
						q = diagonales[i+j]-j;
						m = elem[i+j][q]/elem[i][h];
						while(h<11 && q<11){
							elem[i+j][q] = elem[i+j][q] - m*elem[i][h];
							h++; q++;
						}
						b[i+j] = b[i+j] - m*b[i];
					}
				}
				j++;
			}	
			k=0;
			
		}
		cout << "Iteracion " << i << " : ";
		for(int p=0; p<diagonales.size(); p++){
			if(p==i) cout << "[";
			cout << diagonales[p] << " ";
			if(p==i) cout << "] ";
		}
		cout << endl;
		cout << endl;
	}

	for(int i=0; i<diagonales.size(); i++){
		cout << diagonales[i] << endl;
	}
	backward_substitution(res,res_swaps, diagonales);
	return res;
}

void BandMatrix::backward_substitution(vector<double>& res, vector<double> res_swaps,vector<int> diagonales){
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
				acum += elem[i][diagonales[i]+j]*res[i+j];
			}	
		}
		res[i] = (b[i]-acum)/elem[i][diagonales[i]];
	}
	
	for(int i=0; i<res_swaps.size(); i++){
		nuevo[i] = res[res_swaps[i]];
	}

	res = nuevo;
}



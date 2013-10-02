#include <vector>
#include <iostream>
#include <fstream>
#include "../include/BandMatrix.h"
using namespace std;

BandMatrix::BandMatrix(double cos_theta_1,double sen_theta_1, double cos_theta_2,double sen_theta_2, int n){
	vector<double> v;
	for(int i = 0; i < n; i++){
		elem.push_back(v);
		for(int j = 0; j < 8; j++){
			elem[i].push_back(0.0);
		}
	}
	/// elem \in R^(n*8)
	
	//filas 0..n-1  !! columnas 0..7
	//columna 3 = diagonal
	
	/** C0_h */
	elem[0][3] = 1; //F0 = h0
	elem[0][5] = 1; //F2
	elem[0][6] = sen_theta_2; //sen(theta2)F3
	
	/** C0_v */
	elem[1][3] = 1; //F1
	elem[1][5] = cos_theta_2; //cos(theta2)F3
	
	/** C1_h -> F2 y F5*/
	elem[2][3] = 1; //F2
	elem[2][6] = -1; //-F5
	
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
	
	/** C n/2 -1_h -> F9 F10 F14 F13*/
	int medio = n/2 - 2;
	elem[medio][2] = -1; //-Fmedio-1
	elem[medio][3] = -cos_theta_1; //-cos(theta1)Fmedio
	elem[medio][6] = -1; //Fmedio+3
	elem[medio][7] = cos_theta_1; //cos(theta1)Fmedio+4
		
	/** C n/2 -1_v -> F10 F12 F14*/
	medio++;
	elem[medio][2] = sen_theta_1; //sen(theta1)Fmedio-1	
	elem[medio][4] = 1; //Fmedio+1
	elem[medio][7] = sen_theta_1; //sen(theta1)Fmedio+4
	
	/** C n/2_h -> F3 F6 F7*/
	elem[4][2] = -sen_theta_2; // - sen(theta2)*F3
	elem[4][5] = sen_theta_2; //F2
	elem[4][6] = 1; //+F7
	
	/** C n/2_v -> F3 F4 F6*/
	elem[5][1] = -1; //-F4
	elem[5][2] = -cos_theta_2; //-cos(theta2)F3
	elem[5][4] = -cos_theta_2; //-cos(theta2)F6
	
	
}

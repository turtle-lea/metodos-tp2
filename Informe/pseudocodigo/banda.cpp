
//Creacion de la matriz banda. Las funciones cargar_n_igual_{cant_secciones}
//inicializan los valores de las posiciones

BandMatrix::BandMatrix(double cos_theta_1,double sen_theta_1, 

	double cos_theta_2,double sen_theta_2, int n, vector<double> cargas){

	//Creo la matriz banda, n filas y 11 columnas
	vector<double> v;
	for(int i = 0; i < n; i++){
		elem.push_back(v);
		for(int j = 0; j < 11; j++){
			elem[i].push_back(0.0);
		}
	}
	
	// n==8 es el puente de 2 secciones. Es un caso especial
	// Las funciones cargar_n inicializan la matriz
	if(n==8){
		cargar_n_igual_2(cos_theta_1,

			sen_theta_2,cos_theta_2,sen_theta_2,n,cargas);
	}else{	
		cargar_n_mayor_2(cos_theta_1,sen_theta_2,

			cos_theta_2,sen_theta_2,n,cargas);
	}

	//Cargo el vector b, ubicando las cargas donde corresponde
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



//Algoritmo de ELIMINACION GAUSSIANA con pivoteo parcial
vector<double> BandMatrix::resolver_sistema(){
	vector<double> res;
	vector<int> diagonales;
	//Tolerancia para no igualar a 0
	double e = 0.0000000001;
	int n = b.size();

	//Incializo el vector de DIAGONALES en 3 para
	//cada posicion, y el vector res en 0.
	inicializar_estructuras(res,diagonales,n);

	//Algoritmo de triangulacion de matriz:	
	for(int i=0; i<n; i++){
		//Si es necesario hacer un paso de Gauss.
		//Si hay un cero en la columna i, debajo de 
		//la fila i (Solo es necesario revisar hasta i+4)
		if(hayQueIterar(i,diagonales,e)){
			double elem_diagonal = elem[i][diagonales[i]];			
			if(abs(elem_diagonal)<e){
				double max = abs(elem_diagonal);
				int k_max = 0;
	
				//Encuentro la fila para pivotear
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
	
				// modifico las diagonales
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
					//Realizo el iesimo paso
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
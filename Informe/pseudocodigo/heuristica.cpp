pair< pair<double,bool>, vector<int> > Bridge::heuristica(){
	vector<int> posiciones;	
	pair<double,bool> p;
	p = heuristica_aux(posiciones);
	//Al costo de las subestructuras le agrego el costo de haber insertado los pilares
	p.first = p.first + posiciones.size()*costo_pilar;
	pair< pair<double,bool>, vector<int> > res;
	res.first = p; res.second = posiciones;
	return res;
}

pair<double,bool> Bridge::heuristica_aux(vector<int>& posiciones){
	pair<double, bool> res;
	if(n==2){
		res.first = longitud_total*max_fuerza_obtenida;
		res.second = seguro();
	} else{
		if(seguro()){
			res.first = longitud_total*max_fuerza_obtenida;
			res.second = seguro();
		} else{

			//El puente no es seguro. Hay que dividirlo en subestructuras
			int i=calcular_indice_insercion();
			vector<double> c_1;
			for(int j=0; j<i;j++){
				c_1.push_back(cargas[j]);
			}
			vector<double> c_2;
			for(int j=i+1;j<cargas.size();j++){
				c_2.push_back(cargas[j]);
			}
			double l_1 = (l/n)*(i+1);
			double l_2 = (l/n)*(cargas.size()-i);

			Bridge b_izq(l_1,h,(i+1),c_1,max_modulo,costo_pilar);
			Bridge b_der(l_2,h,(cargas.size()-i),c_2,max_modulo,costo_pilar);

			posiciones.push_back(i);

			pair<double,bool> p1;
			pair<double,bool> p2;
			p1 = b_izq.heuristica_aux(posiciones);
			p2 = b_der.heuristica_aux(posiciones);

			//El costo es la suma de los costos de ambas subestructuras
			res.first = p1.first+p2.first;
			//El nuevo puente es seguro si ambas sub-estructuras son seguras
			res.second = p1.second && p2.second;
		}
	}
	return res;
}

int Bridge::calcular_indice_insercion(){
	int res;
	if(todas_iguales()){
		res = n/2;
		if(res%2==0){
			res--;
		}
	} else{
		int i=0;
		double max = 0;
		for(int j=0; j<cargas.size(); j++){
			if(abs(cargas[j] > max)){
				i=j;
				max = abs(cargas[j]);
			}
		}
		if(i==(cargas.size()-1)){
			res = (i-1);
		} else{
			if(i%2==1){
				res = i;
			} else {
				res = (i+1);
			}
		}
	}
	return res;
}
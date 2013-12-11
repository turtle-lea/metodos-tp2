double h; //altura del puente
double l; // span del puente
int n; // cant_secciones del puente

double max_modulo;	//max_valor que un link puede soportar
double max_fuerza_obtenida; // max_fuerza obtenida luego de resolver el sistema

double costo_pilar; // costo de insertar un nuevo pilar
double longitud_total; // longitud total del puente: para calcular el cp_e del enunciado (pag 4)

BandMatrix* banda;
vector<double> cargas

- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

longitud_total = (2*n-2)*(l/n) + (n-1)*h + n*sqrt((l/n)*(l/n)+h*h);

bool Bridge::seguro(){
	return max_modulo > max_fuerza_obtenida;
}
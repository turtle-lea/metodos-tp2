function A = loadBandMatrix(archivo,secciones) 
	aux = load(archivo);
	A = zeros(secciones*4,secciones*4);
	for k = 1:24
		A(k,1:k-3) = zeros(1,k-3);
		A(k,max(1,k-3): min((k-3)+10,24)) = aux(k,max(1,5-k):min(25-(k-3),11));
		A(k,k+11:24) = zeros(1,25-(k+11));
	end
end
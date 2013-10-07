function esBanda(A)
	[filas,columnas] = size(A);
	epsilon = 10**(-10)
	p = 0;
	q = 0;
	for f=1:filas
		for j=f+1:filas
			if(abs(A(j,f)) > epsilon)
				p = max(p,j-f);
			end
		end
		for j=f+1:columnas
			if(abs(A(f,j)) > epsilon)
				q = max(q,j-f);
			end
		end
	end
	printf("Es matriz %d %d\n",p,q)
end

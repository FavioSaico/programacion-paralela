#include <stdio.h>
#include <omp.h>
#include <math.h> // M_PI
#include <stdlib.h>

int cantPoints(int n){
    
    double x, y, cp,d;
    
    for (int i=0;i<n;i++){
    	x = (double)rand()/(double)RAND_MAX; // valores entre 0 y 1
    	y = (double)rand()/(double)RAND_MAX;

    	d = x*x + y*y; // distancia
    	
    	if(d<=1){ // para que un punto este dentro del circulo la distancia debe ser menor o igual a 1
    		cp++; // punto dentro del circulo y se aumenta
		}
	}
	return cp;
}

int main() {
	
	double x,y,d,api; // puntos X y Y, d es la distancia y api la aproximación de PI
	double n=1000000,cp=0; // cp es la cantidad de puntos que cayeron en el circulo, n es la cantidad de puntos que vamos a generar
	double inicio, duracion;
	
	// SECUENCIAL
	inicio = omp_get_wtime();
	cp = cantPoints(n); // cantidad de puntos
	api = 4.0*(cp/n);
	duracion = omp_get_wtime() - inicio;
	
	printf("Valor de Pi: %lf\n\n", M_PI);
	printf("SECUENCIAL\n");
	printf("Aproximacion de pi: %lf\n", api);
	printf("Error de aproximacion: %lf\n", M_PI - api);
	printf( "La duracion es = %lf segundos\n\n", duracion);

	// PARALELO
	cp = 0;
	int hilos = 10;
	int cant[hilos];
	
	inicio = omp_get_wtime();
	#pragma omp parallel num_threads(hilos)
	{  // cada hilo genera n/hilos puntos
	   int hilo = omp_get_thread_num();
	   cant[hilo] = cantPoints(n/hilos);
	}
	for( int i=0; i<hilos; i++ ) {
	    cp += cant[i]; // sumamos la cantidad de puntos que cayeron dentro del circulo
	}
	api = 4.0*(cp/n);
	duracion = omp_get_wtime() - inicio;
	
	printf("PARALELO\n");
	printf("Pi: %lf\n", M_PI);
	printf("Aproximacion de pi: %lf\n", api);
	printf("Error de aproximacion: %lf\n", M_PI - api);
	printf( "La duracion es = %lf segundos\n", duracion);
	
	return 0;
}

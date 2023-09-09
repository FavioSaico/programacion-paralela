/*
    Realiza la multiplicación de dos matrices cuadradas grandes (por ejemplo, 
    1000x1000) tanto de manera secuencial como en paralelo utilizando OpenMP. 
    Divide el trabajo en filas o bloques y mide el tiempo de ejecución en ambos casos.
*/
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define DIM 500
int A[DIM][DIM],B[DIM][DIM],C[DIM][DIM], D[DIM][DIM];

void llenar(int m[DIM][DIM]) {
    
    for (int i=0;i<DIM;i++){
    	for (int j=0;j<DIM;j++){ 
			m[i][j]=rand()%100; // de 0 a 100
		}
	}
 
}

void imprimir(int m[DIM][DIM]) {
    for(int i=0; i<DIM; i++ ) {
    	for (int j=0;j<DIM;j++){ 
			printf("v[%i][%i] = %i\n", i,j, m[i][j] );
		}
        
    }
}

void multiplicacion(int a[DIM][DIM], int b[DIM][DIM], int c[DIM][DIM], int inicio, int final){
    
    for(int i=inicio; i<final; i++){ 
        for(int j=0; j<DIM; j++){
            for(int k=0; k<DIM; k++){
                c[i][j] += a[i][k]*b[k][j];
            }
        }
    }
}

int main() {
    	double inicio, duracion;
	llenar(A);
	llenar(B);

    // SECUENCIAL
    inicio = omp_get_wtime();
	multiplicacion(A,B,C,0,DIM);
	duracion = omp_get_wtime() - inicio;
	
	printf( "Multiplicacion secuencial\n");
	printf( "La duracion es = %lf segundos\n\n", duracion);
    

	// PARALELA
	int bloque = DIM/5;
	inicio = omp_get_wtime();
	#pragma omp parallel num_threads(5)
	{
	   int hilo = omp_get_thread_num();
	   multiplicacion(A,B,D,hilo*bloque,(hilo+1)*bloque);
	}
	duracion = omp_get_wtime() - inicio;
	
	printf( "Multiplicacion paralela\n");
	printf( "La duracion es = %lf segundos\n", duracion);
	
	return 0;
}

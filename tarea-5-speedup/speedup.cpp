#include <stdio.h>
#include <time.h>
#include <omp.h>

int esPrimo(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main() {
	
	// SECUENCIAL
	clock_t inicio_s = clock();
	int limite1 = 1000000;
    int conteo1 = 0;
    
    clock_t inicio_fr_s = clock();
	for (int i = 2; i <= limite1; i++) {
        if (esPrimo(i)) {
            conteo1++;
        }
    }
    clock_t fin_s = clock();
    
    double tiempo_secuencial_fr = (double)(fin_s - inicio_fr_s) / CLOCKS_PER_SEC;
    double tiempo_secuencial_t = (double)(fin_s - inicio_s) / CLOCKS_PER_SEC;	
    
    printf("Numero de primos encontrados: %d\n", conteo1);
    printf("Tiempo de ejecucion secuencial: %f segundos\n", tiempo_secuencial_t);
	printf("Tiempo de ejecucion secuencial frac: %f segundos\n\n", tiempo_secuencial_fr);


	// PARALELO
 	clock_t inicio = clock();
    int limite = 1000000;
    int conteo = 0;

	clock_t inicio_mejora = clock();
    #pragma omp parallel for reduction(+:conteo)
    for (int i = 2; i <= limite; i++) {
        if (esPrimo(i)) {
            conteo++;
        }
    }
    clock_t fin = clock();
    double tiempo_paralelo_fr= (double)(fin - inicio_mejora) / CLOCKS_PER_SEC;
    double tiempo_paralelo_t = (double)(fin - inicio) / CLOCKS_PER_SEC;

    printf("Numero de primos encontrados: %d\n", conteo);
    printf("Tiempo de ejecucion paralela: %f segundos\n", tiempo_paralelo_t);
    printf("Tiempo de ejecucion paralela frac: %f segundos\n\n", tiempo_paralelo_fr);



	// APLICANDO LA LEY DE AMDAHL
	double speedup = tiempo_secuencial_t/tiempo_paralelo_t;
	double fraccion_mejora = tiempo_secuencial_fr/tiempo_secuencial_t;
	double speedup_mejora = tiempo_secuencial_fr/tiempo_paralelo_fr;
	
	double speedup_mejora_cal = (tiempo_secuencial_t*fraccion_mejora)/(tiempo_paralelo_t-tiempo_secuencial_t+tiempo_secuencial_t*fraccion_mejora);
	
	printf("Fraccion de Mejora: %f\n", fraccion_mejora);
	printf("Speedup de Mejora: %f\n", speedup_mejora);
	printf("Speedup de Mejora calculada: %f\n", speedup_mejora_cal);
	printf("Tiempo de ejecucion nuevo: %f\n", tiempo_paralelo_t);
	printf("Speedup total: %f\n\n", speedup);
	
    return 0;
}


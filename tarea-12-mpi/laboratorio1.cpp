/*
	Laboratorio 1: Análisis de Sentimiento en Redes Sociales
	
	Objetivo: Implementar un algoritmo paralelo utilizando MPI para analizar el sentimiento 
				de un conjunto de mensajes en redes sociales.
	
	Pasos:
	- Obtener un conjunto de mensajes de redes sociales (por ejemplo, tweets) para análisis.
	- Dividir el conjunto de mensajes en partes iguales y distribuirlo entre los procesos MPI.
	- Cada proceso realiza el análisis de sentimiento de su conjunto de mensajes utilizando una biblioteca o 
		algoritmo adecuado.
	- Realizar una comunicación colectiva (por ejemplo, MPI_Reduce) para combinar los resultados del análisis 
		de sentimiento de todos los procesos en uno solo.
	- El proceso maestro (rango 0) recibe el resultado final y lo presenta.

*/
#include <iostream>
#include <mpi.h>

const int ARRAY_SIZE = 12;

int main(int argc, char** argv) {
    
}





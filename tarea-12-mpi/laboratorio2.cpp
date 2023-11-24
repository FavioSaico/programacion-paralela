/*

	Laboratorio 2: Procesamiento de Imágenes en Paralelo
	Objetivo: Implementar un algoritmo paralelo utilizando MPI para procesar una 
				imagen de gran tamaño aplicando una serie de filtros.
	Pasos:
	- Dividir la imagen en partes iguales y distribuir cada parte entre los procesos MPI.
	- Cada proceso realiza el procesamiento de la imagen aplicando un filtro específico a su parte.
	- Realizar una comunicación punto a punto (por ejemplo, MPI_Send y MPI_Recv) para intercambiar
		las partes de la imagen entre los procesos vecinos, de manera que puedan procesar los píxeles 
		de borde correctamente.
	- Realizar una comunicación colectiva (por ejemplo, MPI_Gather) para combinar las partes procesadas
		y reconstruir la imagen completa en el proceso maestro.El proceso maestro guarda la 
		imagen resultante en un archivo y la muestra.

*/
#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    
    return 0;
}



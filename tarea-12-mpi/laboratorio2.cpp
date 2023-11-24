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
#include <opencv2/opencv.hpp>

using namespace cv;

void convertirBlancoNegro(Mat& img, int inicio, int fin) {
    for (int i = inicio; i < fin; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            Vec3b pixel = img.at<Vec3b>(i, j);
            uchar gris = (pixel[0] + pixel[1] + pixel[2]) / 3;
            img.at<Vec3b>(i, j) = Vec3b(gris, gris, gris);
        }
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

	// Solo el proceso 0 lee la imagen y las distribuye
    Mat imagen; // imagen como matriz
    Mat imagenPart;
    int filas, cols;
    int bloque, inicio, fin;
    if (rank == 0) {
        imagen = imread(argv[1]);
        if (imagen.empty()) {
            std::cerr << "Error al cargar la imagen." << std::endl;
            MPI_Finalize();
            return 1;
        }
        /*filas = imagen.rows;
        cols = imagen.cols;*/
        
        // Divide las filas entre los procesos
	    //bloque = filas / size; // filas por proceso
	    
	    for (int i=1; i<size; i++){
	    	/*Rect roi(0, i * bloque, imagen.cols, bloque);
	    	imagenPart = imagen(roi);*/
	    	
	    	//MPI_Send(imagenPart.data, filas * cols * 3, MPI_UNSIGNED_CHAR, i, 0, MPI_COMM_WORLD); // imagenPart.size()
	    	MPI_Send(imagen.data, filas * cols * 3, MPI_UNSIGNED_CHAR, i, 0, MPI_COMM_WORLD);
		}
        
    }
	filas = imagen.rows;
    cols = imagen.cols;
    
	// Divide las filas entre los procesos
   	bloque = filas / size;
    inicio = rank * bloque;
    fin = (rank == size - 1) ? filas : (rank + 1) * bloque;
	
	// Procesamiento paralelo de la imagen
	//MPI_Recv(imagenPart.data, filas * cols * 3, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
	if (rank != 0) {
		MPI_Recv(imagen.data, filas * cols * 3, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}
	
    convertirBlancoNegro(imagen, inicio, fin);
	
	// Convertir la parte procesada de la imagen a bytes
    std::vector<uchar> imagenBytes;
    imencode(".jpg", imagen, imagenBytes);
	
	// Recopila los resultados utilizando MPI_Gather
    std::vector<uchar> imagenCompletaBytes(size * bloque * cols * 3);
    
    MPI_Gather(imagenBytes.data(), imagenBytes.size(), MPI_UNSIGNED_CHAR,
               imagenCompletaBytes.data(), imagenBytes.size(), MPI_UNSIGNED_CHAR,
               0, MPI_COMM_WORLD);


	std::cout << "Proceso " << rank << " transformando las filas del "<< inicio <<" al "<< fin << std::endl;

	// Solo el proceso 0 guarda la imagen resultante
    if (rank == 0) {
    	Mat imagenCompleta = imdecode(imagenCompletaBytes, IMREAD_UNCHANGED);
        imwrite(argv[2], imagen); // guardamos la imagen con el nombre del segundo argumento.
    }

    MPI_Finalize();
    return 0;
}



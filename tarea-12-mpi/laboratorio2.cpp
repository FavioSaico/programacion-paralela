/*
	Laboratorio 2: Procesamiento de Imagenes en Paralelo
	Objetivo: Implementar un algoritmo paralelo utilizando MPI para procesar una 
				imagen de gran tamanio aplicando una serie de filtros.
	Pasos:
	- Dividir la imagen en partes iguales y distribuir cada parte entre los procesos MPI.
	- Cada proceso realiza el procesamiento de la imagen aplicando un filtro especifico a su parte.
	- Realizar una comunicacion punto a punto (por ejemplo, MPI_Send y MPI_Recv) para intercambiar
		las partes de la imagen entre los procesos vecinos, de manera que puedan procesar los pixeles 
		de borde correctamente.
	- Realizar una comunicacion colectiva (por ejemplo, MPI_Gather) para combinar las partes procesadas
		y reconstruir la imagen completa en el proceso maestro.El proceso maestro guarda la 
		imagen resultante en un archivo y la muestra.
*/
#include <iostream>
#include <mpi.h>
#include <opencv2/opencv.hpp>
#include <string>
using namespace cv;

void convertirBlancoNegro(Mat& img, int inicio, int fin) {
    // recorido de los pixeles
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

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Solo el proceso 0 lee la imagen
    Mat imagen;
    int filas, cols;
    if (rank == 0) {
        imagen = imread(argv[1]);
        if (imagen.empty()) {
            std::cerr << "Error al cargar la imagen." << std::endl;
            MPI_Finalize();
            return 1;
        }
        // asignamos el valor de las filas y columnas
        filas = imagen.rows;
        cols = imagen.cols;
    }

    // Broadcast de las filas y columnas de la imagen para todos los procesos
    MPI_Bcast(&filas, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&cols, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Divide las filas entre los procesos
    int filasPorProceso = filas / size;
    int inicio = rank * filasPorProceso;
    int fin = (rank == size - 1) ? filas : (rank + 1) * filasPorProceso;

    // Broadcast de la parte de la imagen que corresponde a cada proceso
    if (rank != 0) {
        imagen = Mat(filas, cols, CV_8UC3);
    }
    
    // Desde el proceso 0 enviamos la imagen al resto de procesos 
    if (rank == 0) {
        for (int i=1; i<size; i++){
            MPI_Send(imagen.data, filas * cols * 3, MPI_UNSIGNED_CHAR, i, 0, MPI_COMM_WORLD);
        }
    }
    
    // Los demás procesos reciben la imagen desde el el proceso 0
    if (rank != 0) {
        MPI_Recv(imagen.data, filas * cols * 3, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Procesamiento de la imagen
    convertirBlancoNegro(imagen, inicio, fin);

    // generamos una imagen por cada parte en blanco y negro
    std::string name = std::string(argv[1]) + std::to_string(rank) + ".jpg";
    imwrite(name, imagen);

    // Recopila los resultados de todos los procesos
    MPI_Gather(imagen.data + inicio * cols * 3, (fin - inicio) * cols * 3, MPI_UNSIGNED_CHAR, imagen.data, (fin - inicio) * cols * 3, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    // Solo el proceso 0 guarda la imagen resultante
    if (rank == 0) {
        name = std::string(argv[1]) + "_BN.jpg";
        imwrite(name, imagen);
    }

    MPI_Finalize();
    return 0;
}



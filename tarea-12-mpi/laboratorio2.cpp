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
#include <iostream>
#include <mpi.h>
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

    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (argc != 3) {
        if (rank == 0) {
            std::cerr << "Uso: " << argv[0] << " <imagen_entrada.jpg> <imagen_salida.jpg>" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    // Solo el proceso 0 lee la imagen
    Mat imagen;
    if (rank == 0) {
        imagen = imread(argv[1]);
        if (imagen.empty()) {
            std::cerr << "Error al cargar la imagen." << std::endl;
            MPI_Finalize();
            return 1;
        }
    }

    // Broadcast del tamaño de la imagen
    int filas, cols;
    if (rank == 0) {
        filas = imagen.rows;
        cols = imagen.cols;
    }
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
    MPI_Bcast(imagen.data, filas * cols * 3, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    // Procesamiento paralelo de la imagen
    convertirBlancoNegro(imagen, inicio, fin);

    // Recopila los resultados
    MPI_Gather(imagen.data + inicio * cols * 3, (fin - inicio) * cols * 3, MPI_UNSIGNED_CHAR, imagen.data, (fin - inicio) * cols * 3, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    // Solo el proceso 0 guarda la imagen resultante
    if (rank == 0) {
        imwrite(argv[2], imagen);
    }

    MPI_Finalize();
    return 0;
}



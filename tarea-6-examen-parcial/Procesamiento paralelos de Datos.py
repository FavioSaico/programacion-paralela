import cv2
import numpy as np
import multiprocessing
import time

def apply_filter(image_chunk, start_row, end_row, kernel, result, width):
    filtered_chunk = cv2.filter2D(image_chunk, -1, kernel)
    filtered_chunk_bytes = np.ndarray.tobytes(filtered_chunk)
    chunk_size = len(filtered_chunk_bytes) // width
    result[start_row * width * 1:end_row * width * 1] = filtered_chunk_bytes

def parallel_filter(image, kernel, num_processes=4):
    height, width = image.shape
    chunk_size = height // num_processes
    processes = []
    result = multiprocessing.RawArray('B', height * width * 1)  # Shared array of unsigned 8-bit integers

    for i in range(num_processes):
        start_row = i * chunk_size
        end_row = start_row + chunk_size if i < num_processes - 1 else height
        image_chunk = image[start_row:end_row]
        process = multiprocessing.Process(target=apply_filter, args=(image_chunk, start_row, end_row, kernel, result, width))
        processes.append(process)
        process.start()

    for process in processes:
        process.join()

    # Convert the shared array back to numpy array
    filtered_image = np.frombuffer(result, dtype=np.uint8)
    filtered_image = filtered_image.reshape((height, width))

    return filtered_image

if __name__ == "__main__":
    input_image_path = r"G:\triste\gato.jpg"

    # Intenta cargar la imagen en escala de grises
    input_image = cv2.imread(input_image_path, cv2.IMREAD_GRAYSCALE)
    if input_image is None:
        print("Error: No se pudo cargar la imagen. Verifica la ruta del archivo.")
    else:
        # Define el kernel para convertir la imagen a escala de grises
        kernel = np.array([[0.2989, 0.5870, 0.1140]])  # Coeficientes para la conversión a escala de grises

        # Calcula el tiempo de inicio
        start_time = time.time()

        # Aplica el filtro de forma paralela
        filtered_image = parallel_filter(input_image, kernel, num_processes=4)

        # Calcula el tiempo de finalización
        end_time = time.time()

        # Guarda la imagen de salida en blanco y negro
        output_image_path = r"G:\triste\DatosGato.jpg"
        cv2.imwrite(output_image_path, filtered_image)

        print(f"Procesamiento paralelo de la imagen completado. Tiempo de ejecución: {end_time - start_time} segundos. Imagen de salida en blanco y negro guardada como {output_image_path}")

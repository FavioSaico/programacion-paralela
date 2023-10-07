import cv2
from matplotlib import pyplot as plt
import numpy as np

def mostrar_imagen(titulo,imagen): # captura la imagen y lo transforma de BGR a RGB
    #imagen = cv2.cvtColor(imagen,cv2.COLOR_BGR2RGB) 
    plt.imshow(imagen)
    plt.title(titulo)
    plt.grid(False)
    plt.show

def dividir_imagen(imagen,w,h,N):
    # dividimos en ancho de la imagen
    a = w//N # retorna un número entero
    arr = []
    for i in range(N): # 0 a N-1
        tl = imagen[0:h, a*i:a*(i+1)]
        arr.append(tl)
    return arr

def mostrar_imagen_partes(partes,N): # mostramos las N partes de la imagen
    for i in range(N): 
        plt.subplot(1,N,i+1)
        plt.xticks([]), plt.yticks([]) # Quita los números de los ejes
        #arr[i] = cv2.cvtColor(partes[i],cv2.COLOR_BGR2RGB)
        plt.tight_layout(pad=1) # pad es la separación entre las partes
        plt.imshow(partes[i])
    plt.show()

def combinar_partes(partes):
    return np.hstack(partes)

def aplicar_BN(partes): # Convierte el subconjunto a escala de grises
    ab = cv2.cvtColor(partes,cv2.COLOR_BGR2GRAY)
    return cv2.cvtColor(ab, cv2.COLOR_BGR2RGB)
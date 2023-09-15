#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
using namespace std;

// Se define las dimensiones de la matriz y sus dimensiones en el heap
#define m 1000

int axa[m][m];
int bxb[m][m];
int res[m][m];

// Funcion para llenar una matriz con numeros aleatorios
void llenarMatrizAleatoria(int matriz[][m])
{
   for (int i = 0; i < m; i++)
   {
       for (int j = 0; j < m; j++)
       {
           matriz[i][j] = rand();
       }
   }
}

// Funcion para imprimir una parte de la matriz
void imprimirMatriz(int matriz[][m],int k)
{
   for (int i = 0; i < k; i++)
   {
       for (int j = 0; j < k; j++)
       {
           cout<<matriz[i][j]<<" ";
       }
       cout<<'\n';
   }
   cout<<'\n';
}

// Funcion para limpiar una matriz
void limpiarMatriz(int matriz[][m])
{
   for (int i = 0; i < m; i++)
   {
       for (int j = 0; j < m; j++)
       {
           matriz[i][j]=0;
       }
   }
}

// Funcion para multiplicar matrices secuencialmente
void multiplicarMatrices(int matriz1[][m], int matriz2[][m], int resultado[][m])
{
   for (int i = 0; i < m; i++)
   {
       for (int j = 0; j < m; j++)
       {
           resultado[i][j] = 0;
           for (int k = 0; k < m; k++)
           {
               resultado[i][j] += matriz1[i][k] * matriz2[k][j];
           }
       }
   }
}

// Funcion para multiplicar matrices paralelamente
void multiplicarMatricesParalela(int matriz1[][m], int matriz2[][m], int resultado[][m],int ind)
{
   for (int i=ind; i < m; i+=10)
   {
   	if(i>=m)return;
       for (int j=0; j < m; j++)
       {
           resultado[i][j] = 0;
           for (int k = 0; k < m; k++)
           {
               resultado[i][j] += matriz1[i][k] * matriz2[k][j];
           }
       }
   }
}

int main()
{
   srand(time(NULL)); // Inicializar la semilla para números aleatorios

   double inicio, duracion;
   
   //llenar la matriz
   llenarMatrizAleatoria(axa);
   llenarMatrizAleatoria(bxb);
   
   
   inicio = omp_get_wtime();
   multiplicarMatrices(axa, bxb, res);
   duracion = omp_get_wtime() - inicio;
   cout<<"\nMultiplicacion secuencial: "<<duracion<<'\n';
   imprimirMatriz(res, 3);
   
   limpiarMatriz(res);
   
   inicio = omp_get_wtime();
   #pragma omp parallel num_threads(10)
   {
       int hilo = omp_get_thread_num();
       multiplicarMatricesParalela(axa, bxb, res, hilo);
       
   }
   duracion = omp_get_wtime() - inicio;
   cout<<"\nMultiplicacion paralela: "<<duracion<<'\n';
   imprimirMatriz(res, 3);
   
   return 0;
}

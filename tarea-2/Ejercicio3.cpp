#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
using namespace std;

//#define m 1000


void llenar(vector<int>& v,int dim){
   for (int i = 0; i < dim; i++)
   {
		v[i] = rand();
   }
}

void mostrar(vector<int> v){
	for(int i=0;i<v.size();i++){
		cout<<v[i]<<" ";
	}
	cout<<'\n';
}

void merge(vector<int> &arr, int p, int q, int r) {
  
  // Create L ? A[p..q] and M ? A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  int L[n1], M[n2];

  for (int i = 0; i < n1; i++)
    L[i] = arr[p + i];
  for (int j = 0; j < n2; j++)
    M[j] = arr[q + 1 + j];
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

 while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = M[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
    j++;
    k++;
  }
}

void mergeSort(vector<int>&arr, int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;

    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    merge(arr, l, m, r);
  }
}

void mergeSortPar(vector<int>&arr, int l, int r,int dim){
	int max_hilos= omp_get_max_threads();
	int bloque=dim/8;
	
	#pragma omp parallel num_threads(8)
   {
   	int hilo = omp_get_thread_num();
   	for(int i=hilo*bloque;i<(hilo+1)*bloque;i++){
   		mergeSort(arr,hilo*bloque,(hilo+1)*bloque-1);
	   }
   }
   
   #pragma omp parallel num_threads(4)
   {
   	int i = omp_get_thread_num();
   		merge(arr, i*2000, i*2000 + ((i+1)*2000 -1 - i*2000) / 2 , (i+1)*2000 -1);	   
   }
   
   #pragma omp parallel num_threads(2)
   {
   	int i = omp_get_thread_num();
   		merge(arr, i*4000, i*4000 + ((i+1)*4000 -1 - i*4000) / 2 , (i+1)*4000 -1);	   
   }
   
	merge(arr, 0, 0 + (8000-1 - 0) / 2, 8000-1);
   
}

int main()
{
	

	srand(time(NULL)); // Inicializar la semilla para números aleatorios
	double inicio, duracion;
	int dim =8000;
	vector<int>arreglo1(dim);
	llenar(arreglo1,dim);
	vector<int>arreglo2=arreglo1;
	

	
	cout<<"Arreglo inicial\n";
//	mostrar(arreglo1);
	
	cout<<"Arreglo ordenado secuencialmente: ";
	inicio = omp_get_wtime();
	mergeSort(arreglo1,0,arreglo1.size()-1);
	duracion = omp_get_wtime() - inicio;
	cout<<duracion<<'\n';
	//mostrar(arreglo1);
	
	cout<<"Arreglo ordenado paralelamente: ";
	inicio = omp_get_wtime();
	#pragma omp parallel
	{
	mergeSortPar(arreglo2,0,arreglo2.size()-1,dim);
	}
	duracion = omp_get_wtime() - inicio;
	cout<<duracion<<'\n';
	//mostrar(arreglo2);
	return 0;
}

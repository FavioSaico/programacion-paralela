#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
using namespace std;
#define m 1000000
vector<int>pc;


void SieveOfEratosthenes(int n)
{
    bool prime[n + 1];
    memset(prime, true, sizeof(prime));
  
    for (int p = 2; p * p <= n; p++) {
        if (prime[p] == true) {
            for (int i = p * p; i <= n; i += p)
                prime[i] = false;
        }
    }
 
}

void SieveOfEratosthenes_Par()
{
	vector<int>vpi;
	bool prime[m+1];
    memset(prime, true, sizeof(prime));
  
    for (int p = 2; p * p <= 1070; p++) {
        if (prime[p] == true) {
            for (int i = p * p; i <= 1070; i += p)
                prime[i] = false;
        }
    }
    
    for(int i=2;i<=1070;i++){
    	if(prime[i]){
    		vpi.push_back(i);
		}
	}
	
	int bloque=18;
	
	#pragma omp parallel num_threads(10)
   {
       int hilo = omp_get_thread_num();
       //cout<<hilo<<'\n';
       for(int i=hilo*bloque;i<(hilo+1)*bloque;i++){
       	for(int p=vpi[i]*vpi[i];p<=m;p+=vpi[i]){
       		prime[p]=false;
		   }
	   }
   }
   
}
  
int eratosthenesOdd(int lastNumber, bool useOpenMP)
{
  // enable/disable OpenMP
  omp_set_num_threads(useOpenMP ? omp_get_num_procs() : 1);
  // instead of i*i <= lastNumber we write i <= lastNumberSquareRoot to help OpenMP
  const int lastNumberSqrt = (int)sqrt((double)lastNumber);
  int memorySize = (lastNumber-1)/2;
  // initialize
  char* isPrime = new char[memorySize+1];
#pragma omp parallel for
  for (int i = 0; i <= memorySize; i++)
    isPrime[i] = 1;
  // find all odd non-primes
#pragma omp parallel for schedule(dynamic)
  for (int i = 3; i <= lastNumberSqrt; i += 2)
    if (isPrime[i/2])
      for (int j = i*i; j <= lastNumber; j += 2*i)
        isPrime[j/2] = 0;
  // sieve is complete, count primes
  int found = lastNumber >= 2 ? 1 : 0;
#pragma omp parallel for reduction(+:found)
  for (int i = 1; i <= memorySize; i++)
    found += isPrime[i];
    
  delete[] isPrime;
  return found;
}

int main()
{
   srand(time(NULL)); // Inicializar la semilla para números aleatorios
   
   double inicio, duracion;
   
   inicio = omp_get_wtime();
   SieveOfEratosthenes(m);
   duracion = omp_get_wtime() - inicio;
   cout<<"\nCriba secuencial: "<<duracion<<'\n';
   
   inicio = omp_get_wtime();
   SieveOfEratosthenes_Par();
   duracion = omp_get_wtime() - inicio;
   cout<<"\nCriba paralela: "<<duracion<<'\n';
   
   inicio = omp_get_wtime();
   eratosthenesOdd(m,true);
   duracion = omp_get_wtime() - inicio;
   cout<<"\nCriba paralela de internet: "<<duracion<<'\n';
   
   return 0;
}

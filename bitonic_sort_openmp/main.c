#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
//#include "serial_bitonicSort.h"

enum dir {up = 0, down};


void swap(int *a, int *b){

    //printf("Swapping %d %d\n", *a, *b);

    *a = *a + *b; 
    *b = *a - *b;
    *a = *a - *b;

}

void test_and_swap(int *a, int *b, int dir){

    if(dir == (*a < *b)){
        swap(a, b);
    }

}


/*
Paralelizar com parallel_merge não deu bom.
- Overhead ficou enorme
- Algoritmo ficou muito pior do que o serial
*/
void _parallel_merge(int *v, int len, int dir){


    int step = len / 2;
    int i;
    /*
    Ao usar #pragma ... for é legal que a chave do for fique na próxima linha. sei la pq
    */
    #pragma omp parallel for schedule(static) shared(v, step) private(i)
    for(i = 0; i < step; i++)
    {
        if(dir == v[i] > v[i+step]){ // compAndSwap
            swap(&v[i], &v[i+step]);
        }

    }

    

}

void parallel_merge(int *v, int len, int dir){

    //int step = len / 2;

    for(int subvecs = 1; subvecs < len; subvecs*=2){

        for(int i = 0; i < subvecs; i++){
            int subvec_len = len / subvecs;
            _parallel_merge(v + i * subvec_len , subvec_len, dir);
        }

    }
    

}



void mergeBitonicSequence(int *v, int len, int dir){

    int step = len/2;

    while(step > 0){
        //printf("Step = %d\n", step);

        for(int i = 0, k = step; k < len; i++, k++){
              
            if(dir == v[i] > v[k]){
                swap(&v[i], &v[k]);
            }

        }
        step /= 2;
    }

}

void firstStep(int *v, int len){

    for(int i = 0, j = 1, direction = up; j < len; i+=2, j+=2, direction ^= down){
        //printf("i %d j %d dir %d\n", i, j, direction);
        test_and_swap(&v[i], &v[j], direction);
    }

}

void printVet(int *v, int len){
    for(int i = 0; i < len; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

void merge(int *v, int len){

    int cbs = 4;
    for(int cbs = 4; cbs < len; cbs *= 2){

        int step = cbs/2;
        int current = cbs;
        int cont_dir = 0;
        int dir = 0;
        while(step > 0){
            
       
            for(int i = 0, c = step, d = 0; (i < len) && (c < len); c+=current, i+=current, d++){
                for(int k = i, l = c; k < c; k++, l++){
                    
                    test_and_swap(&v[k], &v[l], dir);
                
                    cont_dir++;

                    if(cont_dir > cbs / 2 - 1){

                        cont_dir = 0;
                        if(dir == 0){
                        dir = 1;
                        } else {
                        dir = 0;
                        }
                    }
                }
            }
            step /= 2;
            current /= 2;
        }
    
    }

}

void bSort(int *v, int len, int dir){

    firstStep(v, len); // aparentemente ok

    merge(v, len); // Apesar do nome, essa função transforma uma sequencia aleatória em uma sequencia bitonica
    
    mergeBitonicSequence(v, len, dir);
    //parallel_merge(v, len, dir);
}

/*
Função retorna 0 para um vetor não ordenado de forma crescente
e retorna 1 para quando o vetor está ordenado.
*/
int isSorted(int *v, int len, int *idx_falha){
    for(int i = 0; i < len - 1; i++){
        if(v[i] > v[i + 1]){
            *idx_falha = i;
            return 0; 
        }
    }
    return 1; 
}

int main(){


    printf("Serial Bitonic Sort\n");

    int *v, len = 0, ini, fim, tid, nth, subvector_len;

    double start, end;

    FILE *f;
    f = stdin;

    fscanf(f,"%d", &len);
    printf("Serial Bitonic Sort com vetor de %d\n", len);
    v = malloc(sizeof(int) * len);

    for(int i = 0; i < len; i++){
        fscanf(f, "%d", (v+i));
    }
    
    start = omp_get_wtime();

    #pragma omp parallel default(none) private(ini, fim, tid) shared(v, nth, subvector_len, len) num_threads(4)
    {
        tid = omp_get_thread_num();
        nth = omp_get_num_threads();

        subvector_len = (int) len/nth;

        printf("Hello world from thread %d of %d threads \n", tid, nth);
        printf("Ordenando na direcao %s\n", tid % 2 == 0 ? "up" : "down");
        
        bSort(v + tid * subvector_len, subvector_len, tid % 2 == 0);
    
    }
    
    printf("Resultado:\n");


    /*
    - Cada thread ordena uma parcela do vetor
    - A quantidade de threads deve ser multiplo de 2
    - Para ordenar a sequencia global, é necessário rodar o mergeBitonicSequence log2(Threads)

    mergeBitonicSequence(v, len)
    mergeBitonicSequence(v, len)
    */

   #pragma omp parallel default(none) private(ini, fim, tid) shared(v, len, nth, subvector_len) num_threads(2)
    {
        tid = omp_get_thread_num();
        nth = omp_get_num_threads();

        subvector_len = len / nth;
        
        printf("Hello world from thread %d of %d threads \n", tid, nth);

        mergeBitonicSequence(v + tid * subvector_len, subvector_len, tid % 2 == 0);
    }
    
    mergeBitonicSequence(v, len, down);

    end = omp_get_wtime();

    /*for(int i = 0; i < 4; i++){

        printf("Vetor thread %d\n", i);
        printVet(v + i*len / 4, len / 4);
        printf("\n");

    }*/

    printf("t=%lf s\n", end - start);


    int idx_falha = -1;
    printf(isSorted(v, len, &idx_falha) ? ("\nOrdenado\n") : ("\nNao ordenado\n")); 

    if(idx_falha != -1)
        printf("falha no idx %d\n", idx_falha);

    free(v);

    return 0;
}
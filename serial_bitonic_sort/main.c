#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//#include "serial_bitonicSort.h"

enum dir {up = 0, down};


void swap(int *a, int *b){

    //printf("Swapping %d %d\n", *a, *b);

    *a = *a + *b; 
    *b = *a - *b;
    *a = *a - *b;

}

void test_and_swap(int *a, int *b, int dir){

    //if((*a > *b && dir == up) || (*a < *b && dir == down)){
    //    swap(a, b);
    //}

    if(dir == (*a < *b)){
        swap(a, b);
    }

}

void mergeBitonicSequence(int *v, int len){

    int step = len/2;
    while(step > 0){
        //printf("Step = %d\n", step);
        for(int i = 0, k = step; k < len; i++, k++){
              
            if(v[i] > v[k]){
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

void _bitonicSeq(int *v, int len, int dir){

    int step = len / 2;

    while(step > 0){

        for(int i = 0, k = step; k < len; i++, k++){
              
            if(v[i] > v[k] && dir == up || v[i] < v[k] && dir == down){
                swap(&v[i], &v[k]);
            }

        }
        step /= 2;
        printf("STEP %d\n", step);
        printVet(v, len);
    }

}

void merge(int *v, int len){

    int cbs = 4;
    for(int cbs = 4; cbs < len; cbs *= 2){

        //printf("CBS %d\n", cbs);
        int step = cbs/2;
        int current = cbs;
        int cont_dir = 0;
        int dir = 0;
        while(step > 0){
            
           // printf("STEP %d\n", step);
           
            for(int i = 0, c = step, d = 0; i < len && c < len; c+=current, i+=current, d++){
                //printf("(%d,%d) ", i,c);
                for(int k = i, l = c; k < c; k++, l++){
                   // printf(" (%d,%d) dir = %d",k,l, dir);
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
                //printf("\n");
            }
            step /= 2;
            current /= 2;
//            printf("Vetor\n");
//            printVet(v, len);
//            printf("\n");
        }
    
    }

}

void bitonicSequence(int *v, int len, int dir){

   for(int cbs = 4; cbs <= len / 2; cbs *= 2){
        
        for(int step = cbs/2; step > 1; step /= 2){
            printf("STEP %d CBS %d LEN %d\n", step, cbs, len);

            int j = 0, k = step;
            for(int i = 0; i < len/cbs; i++){ // Quantidade de subvetores considerando CBS

                for(int l = 0; l <cbs/step; j++, k++, l++){
                    
                    printf("%d,j,k (%d,%d)\n",i,j, k);

                }
                j += step;
                k += step;
                
                /*for(int j =  i*cbs, k = j+step, l = 0; l < cbs/2; j++, k++, l++){
                    printf("%d Comparando j,k (%d,%d)\n", i,j, k);
                    test_and_swap(&v[j], &v[k], (i % 2 != 0));
                }*/

            }

            printf("Vetor\n");
            printVet(v, len);
            printf("\n");

        }
        
        /*printf("STEP %d CBS %d\n", 1, cbs);
        int j = 0, k = 1;
        for(int i = 0; i < len/cbs; i++){ 
            for(int l = 0; l < cbs/2; l++){
                printf("%d Comparando j,k (%d,%d)\n", i,j, k);
                test_and_swap(&v[j], &v[k], (i % 2 != 0));

                j+=2;
                k+=2;
            }
        }*/

        printf("Vetor\n");
        printVet(v, len);
        printf("\n");

   }

}

void bSort(int *v, int len){

    firstStep(v, len); // aparentemente ok

    merge(v, len);
    mergeBitonicSequence(v, len);

}

/*
void _BitonicSort(int *v, int len, int dir){


    for(int cbs = 2; cbs <= len/2; cbs *=2){

        for(int step = cbs / 2; step > 0; step /= 2){

            printf("CBS %d STEP %d\n", cbs, step);

            for(int i = 0, j = 0, k = step; i < cbs/2 || i < 2; i++, 
            (step == 1) ? (j+=2) : (j++), (step == 1) ? (k+=2) : (k++) ){

                printf("i %d - j %d - k %d\n", i,j,k);


            }
        }

    }

}

void bitonicSort(int *v, int len){

    for(int currentBS = 2; currentBS < len; currentBS*=2){ // 2, 4, 8, 16 ...

        for(int step = currentBS / 2; step > 0 ; step /= 2){
            
            int dir = up, cont = currentBS/2;

            if(step == 1){

                for(int i = 0; i < len; i+=2){    
                    if(dir == up){
                        if(v[i] > v[i+step]){
                            swap(&v[i], &v[i+step]);
                        }
                    }else{
                        if(v[i] < v[i+step]){
                            swap(&v[i], &v[i+step]);
                        }
                    }

                    cont--;
                    if(cont == 0){
                        cont = currentBS/2;
                        if(dir == up){
                            dir = down;
                        }else {
                            dir = up;
                        }
                    }

                }
            }else {
                
                cont = currentBS/2;
                for(int i = 0; i < currentBS/2; i++){    
                    //printf("xDir %d Comparando v[%d]~v[%d] = %d %d\n", dir,i, i+step, v[i], v[i+step]);
                    if(dir == up){
                        if(v[i] > v[i+step]){
                            swap(&v[i], &v[i+step]);
                        }
                    }else{
                        if(v[i] < v[i+step]){
                            swap(&v[i], &v[i+step]);
                        }
                    }
                 

                    cont--;
                    if(cont == 0){
                        cont = currentBS/2;
                          if(dir == up){
                        dir = down;
                    }else {
                        dir = up;
                    }

                    }
                }

                cont = currentBS/2;
                for(int k = len/2; (k + step) < len ; k++){
                    //printf("Dir %d Comparando v[%d]~v[%d] = %d %d\n", dir,k, k+step, v[k], v[k+step]);
                    
                    if(dir == up){
                        if(v[k] > v[k+step]){
                            swap(&v[k], &v[k+step]);
                        }
                    }else{
                        if(v[k] < v[k+step]){
                            swap(&v[k], &v[k+step]);
                        }
                    }

                    cont--;
                    if(cont == 0){
                        cont = currentBS/2;
                           if(dir == up){
                        dir = down;
                    }else {
                        dir = up;
                    }
                    }

                }
            }
            
            printf("\n");
            for(int i = 0; i < 8; i++){
                printf("%d ", v[i]);
            }
            printf("\n");

        }
 
    }
}
*/

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

    int len = 0;
    int *v;

    FILE *f;
    f = stdin;

    fscanf(f,"%d", &len);
    
    v = malloc(sizeof(int) * len);

    for(int i = 0; i < len; i++){
        fscanf(f, "%d", (v+i));
    }

    bSort(v, len);

    int idx_falha = -1;
    printf(isSorted(v, len, &idx_falha) ? ("\nOrdenado\n") : ("\nNao ordenado\n")); 

    if(idx_falha != -1)
        printf("falha no idx %d\n", idx_falha);

    
    free(v);

    return 0;
}
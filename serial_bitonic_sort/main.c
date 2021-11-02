

#include <stdio.h>
//#include "serial_bitonicSort.h"

void swap(int *a, int *b){

    printf("Swapping %d %d\n", *a, *b);

    *a = *a + *b; 
    *b = *a - *b;
    *a = *a - *b;

}

enum dir {up = 0, down};

void bitSort(int *v, int len){

    int subArrayidx = len / 2; 

    for(int currentBS = 2; currentBS <= len; currentBS*=2){
        printf("CBS %d\n", currentBS);

        for(int step = currentBS / 2; step > 0 ; step /= 2){
            
            printf("CBS = %d Step %d\n", currentBS, step);

        }
    }



}

void mergeBitonicSequence(int *v, int len){

    int step = len/2;
    while(step > 0){
        printf("Step = %d\n", step);
        for(int i = 0, k = step; k < len; i++, k++){
            
            printf("Comparando v[%d]~v[%d]  = %d %d\n", i, k, v[i], v[k]);

            if(v[i] > v[k]){
                swap(&v[i], &v[k]);
            }

        }

        step /= 2;
    }

}

void bitonicSort(int *v, int len){

    //int currentBS = 2, step = currentBS/2, d = up;
    int dir = up, cont;
    for(int currentBS = 2; currentBS < len; currentBS*=2){
        printf("cBS %d\n",currentBS);

        cont = currentBS/2;
        for(int step = currentBS / 2; step > 0 ; step /= 2){
            
            printf("CBS = %d Step %d Dir %d\n", currentBS, step, dir);

            int dir = up;
            
            int cont = currentBS/2;

            if(step == 1){
                for(int i = 0; i < len; i+=2){    
                    printf("Dir %d Comparando v[%d]~v[%d]  = %d %d\n", dir, i, i + step, v[i], v[i + step]);
                    if(dir == up){
                        printf("up\n");
                        if(v[i] > v[i+step]){
                            swap(&v[i], &v[i+step]);
                        }
                    }else{
                        printf("down\n");
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
                    printf("xDir %d Comparando v[%d]~v[%d] = %d %d\n", dir,i, i+step, v[i], v[i+step]);
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
                    printf("Dir %d Comparando v[%d]~v[%d] = %d %d\n", dir,k, k+step, v[k], v[k+step]);
                    
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

int main(){


    printf("Serial Bitonic Sort\n");

    int len = 0;
    FILE *f;
    f = stdin;
    fscanf(f,"%d", &len);
    

    /*
    bitonicSort(v, 8);
    mergeBitonicSequence(v, 8);


    for(int i = 0; i < 8; i++){
        printf("%d ", v[i]);
    }*/


    return 0;
}

#include "random_seq.h"


void genRandomSeqToFile(int len, int max, char *fname){

    FILE *f;
    char n[10]; // 2147483647
    int n_len = 0;

    printf("File: %s\n", fname);
    printf("Generating %d random numbers\n", len);
    
    f = fopen(fname, "w");

    n_len = sprintf(n, "%d", len);

    fwrite(n, sizeof(char), n_len, f);
    fwrite("\n", sizeof(char), 1, f);

    for(int i = 0; i < len; i++){
    
        int r = rand() % max;
        char c = 32;

        n_len = sprintf(n, "%d", r);

        fwrite(n, sizeof(char), n_len, f);
        fwrite(&c, sizeof(char), 1, f);

    }

    fclose(f);
}
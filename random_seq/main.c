#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "random_seq.h"

int main(){

	int nfiles = 15;
	char n[16];

	for(int i = 10; i < 10 + nfiles; i++){
		
		int r = pow(2, i);
		sprintf(n, "seq%d.in", i - 10);
		genRandomSeqToFile(r, 1024, n);
		

	}


	return 0;

}

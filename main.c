#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "field.h"
#include "generation.h"

int main (int argc, char **argv){

	int inpCheck = errInpCheck(argv[1]);

       	if (inpCheck == 1){
		printf("plik '%s' nie istnieje\n" , argv[1]);
		return 1;
	}

	if (inpCheck == 2){
		printf("plik '%s' jest pusty\n", argv[1]);
		return 2;

	}
	
	int **A = fileRead(argv[1]);

        int k = columns(argv[1]);
        int n = rows(argv[1]);
			
        int **temp = memAllocation(k,n);

	for(int i = 0; i < k; i++)
		for(int j = 0; j < n; j++)
			temp[i][j] = A[i][j];
	
	if (argc < 3){
		printf("podaj ilosc iteracji lub uzyj w trybie 'sbs'\n");
		return 3;
	}

	if (strcmp(argv[2], "sbs") == 0){
	
		if (argc < 4){
			printf("podaj ilosc iteracji\n");
			return 3;
		}	

		printf("\nStan poczatkowy\n\n");

		int iter = atoi(argv[3]);

		int save = 0;

		for(int i = 0; i < iter+1; i++){
                        char c;
			outputScreen(A, k, n);
			printf("\nWpisz 's', zeby zapisac ten stan\n");
			printf("Albo cos innego, zeby kontynuowac\n");
			scanf("%s", &c);
			if (c == 's'){
				outputFile(A, k, n);	
				save++;
				printf("Ten stan zostal wpisany\n\n");
			}
                        if (i != iter){
                                printf("\nStan - %d\n\n", i+1);
                      		temp = fill(k, n, A, temp);
			}
                }
		
		if (save == 0){
			printf("\nZostal zapisany ostatni stan\n");
			outputFile(temp, k, n);
		}	
	} else {
		
		printf("\nStan poczatkowy\n\n");

		int iter = atoi(argv[2]);

		for(int i = 0; i < iter; i++){
			outputScreen(A, k, n);
			if (i != iter)
				printf("\nStan - %d\n\n", i+1);
			temp = fill(k, n, A, temp); 
                }
		
		outputScreen(temp, k, n);
		outputFile(temp, k, n);
	}	

        freeMem(temp, k);

        freeMem(A, k);

        return 0;
}

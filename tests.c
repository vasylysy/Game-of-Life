#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "field.h"
#include "generation.h"

int main(){

	int I0[5][4] = {
                {1, 0, 1, 0},
                {1, 1, 0, 0},
                {0, 1, 0, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
        };

	int I1[5][4] = {
		{1, 0, 0, 0},
		{1, 0, 1, 0},
		{1, 1, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};

	char *file = "testin/test.txt";

	int **A = fileRead(file);

	printf("\n 'columns()' check:");
		if (columns(file) == 5)
			printf(" OK\n\n");
		else
			printf(" Nie OK\n\n");
	
	printf("\n 'rows()' check:");
		if (rows(file) == 4)
			printf(" OK\n\n");
                else
                        printf(" Nie OK\n\n");

	int err = 0;

	for(int i = 0; i < columns(file); i++)
		for(int j = 0; j < rows(file); j++)
			if(I0[i][j] != A[i][j])
				err++;
	
	printf("\n 'fileRead(file)' check:");
		if (err == 0)
			printf(" OK\n\n");
		else
			printf(" Nie OK\n\n");
	
	int **temp = fileRead(file);

	temp = fill(columns(file), rows(file), A, temp);

	err = 0;

	for(int i = 0; i < columns(file); i++)
                for(int j = 0; j < rows(file); j++)
                	if(I1[i][j] != temp[i][j])
                        	err++;

        printf("\n 'fill()' check:");
                if (err == 0)
                        printf(" OK\n\n");
                else
                        printf(" Nie OK\n\n");

	return 0;
}

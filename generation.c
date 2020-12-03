#include <stdlib.h>

#include "generation.h"

int sumMoor(int i, int j, int k, int n, int **A){
	
	if (i == 0 && j == 0)
        	return A[1][0] + A[1][1] + A[0][1];

        if (i == k-1 && j == 0)
        	return A[i-1][0] + A[i-1][1] + A[i][1];

        if (i == 0 && j == n-1)
        	return A[0][j-1] + A[1][j-1] + A[1][j];

        if (i == k-1 && j == n-1)
        	return A[i][j-1] + A[i-1][j-1] + A[i-1][j];

        if (i == 0 && j > 0 && j < (n-1))
        	return A[0][j-1] + A[1][j-1] + A[1][j] + A[1][j+1] + A[0][j+1];

        if (i == (k-1) && j > 0 && j < (n-1))
        	return A[i][j+1] + A[i][j-1] + A[i-1][j+1] + A[i-1][j] + A[i-1][j-1];

        if (j == 0 && i > 0 &&  i < (k-1))
        	return A[i-1][0] + A[i+1][0] + A[i-1][1] + A[i][1] + A[i+1][1];

        if (j == (n-1) && i > 0 && i < (k-1))
        	return A[i+1][j] + A[i-1][j] + A[i-1][j-1] + A[i][j-1] + A[i+1][j-1];
       	
       	return A[i-1][j-1] + A[i][j-1] + A[i+1][j-1] + A[i-1][j] + A[i+1][j] + A[i-1][j+1] + A[i][j+1] + A[i+1][j+1];
	
}

int sumNeumann(int i, int j, int k, int n, int **A){

	if (i == 0 && j == 0)
                return A[1][0] + A[0][1];

        if (i == k-1 && j == 0)
                return A[i-1][0] + A[i][1];

        if (i == 0 && j == n-1)
          	return A[0][j-1] + A[1][j];      

        if (i == k-1 && j == n-1)
                return A[i][j-1] + A[i-1][j];

        if (i == 0 && j > 0 && j < (n-1))
                return A[0][j-1] + A[1][j] + A[0][j+1];

        if (i == (k-1) && j > 0 && j < (n-1))
                return A[i][j-1] + A[i][j+1] + A[i-1][j];

        if (j == 0 && i > 0 &&  i < (k-1))
                return A[i-1][0] + A[i+1][0] + A[i][1];

        if (j == (n-1) && i > 0 && i < (k-1))
                return A[i-1][j] + A[i+1][j] + A[i][j-1];

        return A[i][j-1] + A[i][j+1] + A[i-1][j] + A[i+1][j];
	}

int tempChange(int a, int sum){
	
	if (a == 0 && sum == 3)
        	return 1;

        if(a== 1 && (sum == 2 || sum == 3))
    		return 1;

	return 0;
}

int **fill(int k, int n, int **A, int **temp){
	
	for(int i = 0; i < k; i++)
        	for(int j = 0; j < n; j++){
                	int sum = sumMoor(i, j, k, n, A);     //change Neumann -> sumNeumann()
         		temp[i][j] = tempChange(A[i][j], sum);     
		}
       	for(int i = 0; i < k; i++)
		for(int j = 0; j < n; j++)
                	A[i][j] = temp[i][j];
	
	return temp;
}

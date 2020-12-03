#ifndef FIELD_H
#define FIELD_H

int columns(char *file);

int rows(char *file);

int ** memAllocation (int k, int n);

int **fileRead(char *file);

void outputFile(int **A, int k, int n);

void outputScreen(int **A, int k, int n);

void freeMem(int **A, int k);

int errInpCheck(char *file);

#endif

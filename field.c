#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <png.h>

int x, y;

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers;

void write_png_file(char* file_name) {
  FILE *fp = fopen(file_name, "wb");
  if (!fp)
    printf("[write_png_file] File %s could not be opened for writing", file_name);

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
    printf("[write_png_file] png_create_write_struct failed");

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
    printf("[write_png_file] png_create_info_struct failed");

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during init_io");

  png_init_io(png_ptr, fp);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during writing header");

  png_set_IHDR(png_ptr, info_ptr, width, height,
   bit_depth, color_type, PNG_INTERLACE_NONE,
   PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during writing bytes");

  png_write_image(png_ptr, row_pointers);

  if (setjmp(png_jmpbuf(png_ptr)))
    printf("[write_png_file] Error during end of write");

  png_write_end(png_ptr, NULL);

  for(y = 0; y < height; y++)
	  free(row_pointers[y]);
  free(row_pointers);

  fclose(fp);
}

void process_file(int k, int n, int ** A) {
  width = n;
 height = k; 
  bit_depth = 8;
  color_type = PNG_COLOR_TYPE_GRAY;

  number_of_passes = 7;
  row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * k);
  for (y=0; y<height; y++)
    row_pointers[y] = (png_byte*) malloc(sizeof(png_byte) * n);

  for (y=0; y<height; y++) {
    png_byte* row = row_pointers[y];
    for (x=0; x<width; x++) {
      if (A[y][x] == 0)
	      row[x] = 255;
      else row[x] = 0;
    }
  }
}

int columns(char *file){
	
	FILE *in = fopen(file, "r");

        int c, k = 0;

        while ((c = fgetc(in)) != EOF){   
        	if (c == '\n')
                k++;
        }

        fclose (in);
	
	return k;
}
	
int rows(char *file){
	FILE *in = fopen(file, "r");

	int c, n = 0;
		
	while ((c = fgetc(in)) != EOF){
		if (c == '1' || c == '0')
			n++;
		if(c == '\n')
			break;
	}
	
	fclose (in);

	return n;
}

int ** memAllocation (int k, int n){
	
	int **A = (int **)malloc(k*sizeof(int *));

	for(int i = 0; i < k; i++)
		A[i] = (int *)malloc(n*sizeof(int));

	return A;
}

int ** fileRead (char *file){
	
	FILE *in = fopen(file, "r");

	int k = columns(file);
	int n = rows(file);
		
	int **A = memAllocation(k,n);

        for(int i = 0; i < k; i++)
        	for(int j = 0; j < n; j++)
                fscanf(in, "%d", &A[i][j]);

	fclose(in);
	
	return A;	
}	

int errInpCheck (char *file){
	
	FILE *in = fopen(file, "r");
	
	if(in == NULL)
		return 1;
	
	if(columns(file) == 0)
		return 2;
	
	fclose(in);

	return 0;
}

void outputFile(int **A, int k, int n){
	FILE *out = fopen("out/output.txt", "w");
	
	for(int i = 0; i < k; i++){
		for(int j = 0; j < n; j++)
			fprintf(out, "%d ", A[i][j]);
		fprintf(out, "\n");
	}

	
	process_file(k, n, A);
	write_png_file("out/output.png");
	
	fclose(out);
}

void outputScreen(int **A, int k, int n){
	
	for(int i = 0; i < k; i++){
		for(int j = 0; j < n; j++)
			printf("%d ", A[i][j]);
		printf("\n");
	}

	printf("\n\n");
}

void freeMem(int **A, int k){
        for(int i = 0; i < k; i++)
                free(A[i]);

        free(A);
}

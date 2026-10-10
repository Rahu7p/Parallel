#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	struct timespec start, finish;
	double elapsed;

	int row, col;
	int* A = NULL;
	int* B = NULL;
	int* C = NULL;
	int result = 1;
	const int dimension = 10000;

	size_t datasize = sizeof(int) * dimension * dimension;

	A = (int*)malloc(datasize);
	B = (int*)malloc(datasize);
	C = (int*)malloc(datasize);

  clock_gettime(CLOCK_REALTIME, &start);	
	for (row = 0; row < dimension; row++) {
		for (col = 0; col < dimension; col++) {
			if( A )
				*(A + row*dimension + col) = row + col;
			if( B )
				*(B + row*dimension + col) = row + col;
		}
	}

	for (row = 0; row < dimension; row++) {
		for (col = 0; col < dimension; col++) {
			if( A )
				if( B )
					if( C )
						*(C + row*dimension + col) = *(A + row * dimension + col) + *(B + row * dimension + col);
		}
	}
	clock_gettime(CLOCK_REALTIME, &finish);
	
	elapsed = (finish.tv_sec - start.tv_sec) + (double)(finish.tv_nsec - start.tv_nsec) / 1000000000.0;

	for (row = 0; row < dimension; row++) {
		for (col = 0; col < dimension; col++) {
			if( C ) {
				if (*(C + row * dimension + col) != ((row + col) * 2)) {
					result = 0;
					break;
				}
			}
		}
	}

	if (result) {
		printf("Results verified!!! (%lf)\n", elapsed );
	}
	else {
		printf("Wrong results!!!\n");
	}

	free(A);
	free(B);
	free(C);

	return 0;
}

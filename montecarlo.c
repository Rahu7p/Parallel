#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static long num_trials = 100000000;

int main () {
    long i; 
    long Ncirc = 0; 
    double pi, x, y;
    double r = 1.0; // radius of circle. Side of squrare is 2*r

    double t_start = omp_get_wtime();
    for( i = 0; i < num_trials; i++ ){
        x = (rand() / (double)RAND_MAX); 
        y = (rand() / (double)RAND_MAX);
        if ( ((x * x) + (y * y)) <= r * r ) 
            Ncirc++;
    }
    double elapsed = omp_get_wtime() - t_start;
    
    pi = 4.0 * ((double)Ncirc / (double)num_trials);
    
    printf("\n %d trials, pi is %f (time = %f s) \r\n",num_trials, pi, elapsed);
}

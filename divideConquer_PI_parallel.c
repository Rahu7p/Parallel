#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static long num_steps = 1000000000;
#define MIN_BLK 10000000

double pi_comp(int Nstart,int Nfinish,double step);

int main ()
{
    int i;
    double step, pi, sum;
    step = 1.0/(double) num_steps;
    
    double t_start = omp_get_wtime();
#pragma omp parallel num_threads(4)
{
    #pragma omp single
    sum = pi_comp(0,num_steps,step);
}
    double elapsed = omp_get_wtime() - t_start;

    pi = step * sum;
    printf("Result = %20.18lf (time = %f s)\r\n", pi, elapsed);
}

double pi_comp(int Nstart,int Nfinish,double step)
{ 
    int i,iblk;
    double x, sum = 0.0,sum1, sum2;
    if( Nfinish - Nstart < MIN_BLK ) {
        for( i = Nstart; i < Nfinish; i++ ) {
            x = (i+0.5)*step;
            sum = sum + 4.0/(1.0+x*x);
        }
    }
    else {
        iblk = Nfinish-Nstart;
#pragma omp task shared(sum1)
        sum1 = pi_comp(Nstart, Nfinish-iblk/2,step);
#pragma omp task shared(sum2)
        sum2 = pi_comp(Nfinish-iblk/2, Nfinish, step);
#pragma omp taskwait
        sum = sum1 + sum2;
    }

    return sum;
}

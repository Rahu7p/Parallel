#include <stdio.h>
#include <time.h>

long cantidadIntervalos = 1000000000;
double acum = 0.0;

void main() {
struct timespec start, finish;
double elapsed;
long i;
double fdx, x, baseIntervalo;
baseIntervalo = 1.0 / cantidadIntervalos;

clock_gettime(CLOCK_REALTIME, &start);
for (i = 0, x = 0.0; i < cantidadIntervalos; i++) {
fdx = 4 / (1 + x * x);
acum = acum + (fdx * baseIntervalo);
x = x + baseIntervalo;
}
clock_gettime(CLOCK_REALTIME, &finish);

elapsed = (finish.tv_sec - start.tv_sec) + (double)(finish.tv_nsec - start.tv_nsec) / 1000000000.0;
printf("Resultado Secuencial= %20.18lf (%lf s)\n", acum, elapsed);
}

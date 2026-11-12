#include <stdio.h>
#include <unistd.h>
#include <omp.h>

int main(void) {
    int shared_var = -1;  // Declared outside the parallel region: shared.

    printf("Before parallel region:\n");
    printf("shared_var = %d\n\n", shared_var);

    omp_set_num_threads(4);
    #pragma omp parallel
    {
        int private_var;  // Declared inside the parallel region: private.
        int thread_id = omp_get_thread_num();

        private_var = thread_id;
        shared_var = thread_id;  // Intentionally unsynchronized data race.

        printf("Thread %d: shared_var = %d, private_var = %d\n",
               thread_id, shared_var, private_var);
    }

    printf("\nAfter parallel region:\n");
    printf("shared_var = %d\n", shared_var);

    return 0;
}

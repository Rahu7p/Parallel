#include <stdio.h>
#include <omp.h>
#include <windows.h>

int main(void) {
    int shared_var = 0;

    #pragma omp parallel num_threads(4)
    {
        int thread_id = omp_get_thread_num();

        if (thread_id == 0)
        {
            printf("Master thread %d: modifying shared_var...\n", thread_id);
            Sleep(5);
            shared_var = 42;
            printf("Master thread %d: shared_var set to %d\n", thread_id, shared_var);
        }

        printf("Thread %d: shared_var = %d (after barrier)\n", thread_id, shared_var);
    }

    printf("\nAll threads completed\n");
    return 0;
}

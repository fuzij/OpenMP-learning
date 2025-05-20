#include<stdio.h>
#include<omp.h>

int main(void){
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        printf("Hello World!: %d\n", tid);
    }
    return 0;
}
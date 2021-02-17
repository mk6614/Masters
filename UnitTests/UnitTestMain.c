
#include "../Benchmark.h"
#include "../TaskDefinition.h"
#include "stdio.h"



#define M   1000
#define N   1000

int int_matrix[M][N];
int int_vector[M];
int int_vector_res[N];

TASK(task1)
{
    startTask(1);
        int i,j;
    for(i=0; i<M; i++)
    {
        int sum = 0;
        for(j=0; j<N; j++) sum+=int_matrix[i][j]*int_vector[j];
        int_vector_res[i] = sum;
    }
    finishTask();
}

int fib(int n) 
{
    return (n < 2) ? n : fib(n-1) + fib(n-2);
}

TASK(task2)
{
    startTask(2);
    int x = fib(40);
    finishTask();
}


int main()
{

    initBenchmark();
    startBenchmark();
    for (int i=0; i< 20; i++); CALL_TASK(task1);
    for (int i=0; i< 10; i++); CALL_TASK(task2);
    finishBenchmark();
    printCounters((void*)printf);



    return 0;
}

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
    startTask(0,2);
        int i,j;
    for(i=0; i<M; i++)
    {
        int sum = 0;
        for(j=0; j<N; j++) sum+=int_matrix[i][j]*int_vector[j];
        int_vector_res[i] = sum;
    }
    finishTask(0);
}

int fib(int n) 
{
    return (n < 2) ? n : fib(n-1) + fib(n-2);
}

TASK(task2)
{
    startTask(0,3);
    int x = fib(40);
    finishTask(0);
}


TASK(task3)
{
    static int c = 0;
    startTask(0,4);
    if (c++ %2 == 0) 
    {
        volatile j;
        for (j=0; j<300000000;j++);
    } else {
        volatile j;
        for (j=0; j<100000000;j++);
    }
    printf("this is c: %d\r\n", c);
    finishTask(0);
}

int main()
{

    initBenchmark();
    startBenchmark();
    for (int i=0; i< 20; i++) CALL_TASK(task1);
    for (int i=0; i< 10; i++) CALL_TASK(task2);
    for (int i=0; i< 20; i++) CALL_TASK(task3);
    printCounters((void*)printf);
    for (int i=0; i< 40; i++) CALL_TASK(task3);
    printCounters((void*)printf);
    for (int i=0; i< 100; i++) CALL_TASK(task3);
    finishBenchmark();
    printCounters((void*)printf);



    return 0;
}
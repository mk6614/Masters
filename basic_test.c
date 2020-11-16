#include "perf.h"

/*
 * the basic test performs a set of 5 identical tasks:
 * Task 1 and Task 2 are executed 30 times, consecutively, through a function call (for i in 0..30 {call Task1; call Taks2;})
 * Task 3 is executed 30 times without a function call (for i in 0..30 {do Task3})
 * Task 4 and 5 are executed 30time, separately, through a function call (for i in 0..30 {call Task1;} for i in 0..30 {call Taks2;})
 */

#define SAMPLE_SIZE 10

MEASURE_TASK(Task1, 1)
{
	volatile uint32_t i;
    for (i=0; i<200000; i++);

}

MEASURE_TASK(Task2, 2)
{
	volatile uint32_t i;
    for (i=0; i<200000; i++);
}
MEASURE_TASK(Task4, 4)
{
	volatile uint32_t i;
	for (i=0; i<200000; i++);
}
MEASURE_TASK(Task5, 5)
{
	volatile uint32_t i;
	for (i=0; i<200000; i++);
}

void performBasicTest(void (*printf)(const char *fmt, ...))
{
	volatile uint32_t i;
	initPerformanceTest();
	for (i = 0; i<SAMPLE_SIZE; i++)
	{
		CALL_TASK(Task1);
		CALL_TASK(Task2);
	}
	for (i = 0; i<SAMPLE_SIZE; i++)
	{
		startTask(3);
		volatile uint32_t j;
		for (j=0; j<200000; j++);
		stopTask();
	}
	for (i = 0; i<SAMPLE_SIZE; i++)
	{
		CALL_TASK(Task4);
	}
	for (i = 0; i<SAMPLE_SIZE; i++)
	{
		CALL_TASK(Task5);
	}
	stopPerformanceTest();
	printCounters(printf);
}

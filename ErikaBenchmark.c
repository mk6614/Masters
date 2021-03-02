/*
 * benchmark.c
 *
 *  Created on: 2 Dec 2020
 *      Author: mojca
 */

#include "Benchmark.h"

void initBenchmark(void)
{
	__initPerfCounter();
	initTaskStack();
}

void startTask(uint8_t core_id, uint8_t task_id)
{
	__stopPerfCounter();
	onTaskStart(core_id, task_id, __readPerfCounter());
	__resetPerfCounter();
	__startPerfCounter();
}

void finishTask(uint8_t core_id)
{
	__stopPerfCounter();
	onTaskFinish(core_id, __readPerfCounter());
	__resetPerfCounter();
	__startPerfCounter();
}

void waitSemafor(uint8_t core_id)
{
	__stopPerfCounter();
	onSemaforWait(core_id, __readPerfCounter()); //pops the previous resource owner off the stack
	__resetPerfCounter();
	__startPerfCounter();
}

void semaforGreen(uint8_t core_id, uint8_t task_id)
{
	__stopPerfCounter();
	onSemaforGreen(core_id, task_id, __readPerfCounter()); //pushes the resource owner on the stack
	__resetPerfCounter();
	__startPerfCounter();
}

void startBenchmark(void)
{
	__stopPerfCounter();
	__resetPerfCounter();
	__startPerfCounter();
}

void finishBenchmark()
{
	int i;
	for (i=0; i< NUMBER_OF_CORES; i++) onFinish(i);
}

void printCounters(void (*printf)(const char *fmt, ...))
{
	printTaskCounters(printf);
}



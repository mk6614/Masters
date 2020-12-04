/*
 * benchmark.c
 *
 *  Created on: 2 Dec 2020
 *      Author: mojca
 */

#include "benchmark.h"

/**
 * \brief initialisation of the performance counter and structs to hold the values
 *
 *  The information for the init process is provided by benchmark_conf.h file:
 *  NUMBER_OF_TASKS+1 value holders (structs) are created (an additional one is used as an idle task)
 *  MEASURE_XXX defines what the benchmark measures
 */
void initBenchmark(void)
{
	__initPerfCounter();
	initTaskStack();
}

/**
 * \brief declare the starting point of the task
 */
void startTask(uint8_t task_id)
{
	__stopPerfCounter();
	onTaskStart(task_id, __readPerfCounter());
	__resetPerfCounter();
	__startPerfCounter();
}

/**
 * \brief declare the ending point of a task
 */
void finishTask()
{
	__stopPerfCounter();
	onTaskFinish(__readPerfCounter());
	__resetPerfCounter();
	__startPerfCounter();
}

/**
 * \brief declare the point of resource reservation
 */
void requestResource(uint8_t resource_id)
{
	__stopPerfCounter();
	onResourceRequest(resource_id, __readPerfCounter()); //pushes the resource owner on the stack
	__resetPerfCounter();
	__startPerfCounter();
}

/**
 * \brief declare the point of the gotten resource
 */

void takeResource(uint8_t resource_id)
{
	__stopPerfCounter();
	onResourceResume(resource_id, __readPerfCounter()); //pops the previous resource owner off the stack
	__resetPerfCounter();
	__startPerfCounter();
}

/**
 * \brief declare the point of the resource release
 */

void releaseResource(uint8_t resource_id)
{
	__stopPerfCounter();
	onResourceRelease(resource_id); //declares the idle task as the new resource owner
	__startPerfCounter();
}

/**
 * \brief declare the starting point of the measuring process
 *
 * Call this before the task execution (before the OS start)
 */

void startBenchmark(void)
{
	__resetPerfCounter();
	__startPerfCounter();
}

/**
 * \brief declare the ending point of the measuring process
 *
 * The user needs to decide when to stop the measuring process.
 * At this point the idle task is updated and the Counter can be printed and the report generated.
*/

void finishBenchmark(void)
{
	finishIdleTask(__readPerfCounter());
}

/**
 * \brief print the values of the task Counter
 * \param printf a blocking! function that prints to a desired output.
 *
 * The printf should be blocking so the measuring process is not affected by the resource reservation of the printing process
 */
void printCounters(void (*printf)(const char *fmt, ...))
{
	printTaskCounters(printf);
}

/**
 * \brief generates a report from the values of the Counter.
 * \param printf a blocking! function that prints to a desired output.
 *
 * The printf should be blocking so the measuring process is not affected by the resource reservation of the printing process
 *
 */
void generateReport(void (*printf)(const char *fmt, ...))
{

}




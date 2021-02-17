/*
 * benchmark.c
 *
 *  Created on: 2 Dec 2020
 *      Author: mojca
 */

#ifndef BENCHMARK_C_
#define BENCHMARK_C_

#include "BenchmarkCfg.h"
#include "TaskStack.h"
#include "PerformanceCounter.h"




/**
 * \brief initialises the performance counter and reserves space for task counters
 */
void initBenchmark(void);

/**
 * \brief declare the starting point of the task
 */
void startTask(uint8_t task_id);

/**
 * \brief declare the ending point of a task
 */
void finishTask(void);

/**
 * \brief declare the point of resource reservation
 */
void waitSemafor();

/**
 * \brief declare the point of the gotten resource
 */
/**
 * \brief declare the point of the resource release
 */
void semaforGreen(uint8_t task_id);
/**
 * \brief declare the starting point of the measuring process
 *
 * Call this before the task execution (before the OS start)
 */

void startBenchmark(void);

/**
 * \brief declare the ending point of the measuring process
 *
 * The user needs to decide when to stop the measuring process.
 * At this point the idle task is updated and the counters can be printed and the report generated.
*/

void finishBenchmark(void);

/**
 * \brief print the values of the task counters
 * \param printf a blocking! function that prints to a desired output.
 *
 * The printf should be blocking so the measuring process is not affected by the resource reservation of the printing process
 */
void printCounters(void (*printf)(const char *fmt, ...));

/**
 * \brief generates a report from the values of the counters.
 * \param printf a blocking! function that prints to a desired output.
 *
 * The printf should be blocking so the measuring process is not affected by the resource reservation of the printing process
 *
 */
void generateReport(void (*printf)(const char *fmt, ...));


#endif /* BENCHMARK_C_ */

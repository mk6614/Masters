/*
 * Benchmark.h
 *
 *  Created on: 2 Dec 2020
 *      Author: mojca
 */

#ifndef BENCHMARK_C_
#define BENCHMARK_C_

#include "BenchmarkCfg.h"
#include "TaskStack.h"
#include "PerformanceCounter.h"



/** \fn void initBenchmark(void)
 *      \brief initialises the performance counter and reserves space for task counters and initialises the stack.
 *      
 *      Initialization needs to be done from each core before the start of the measuring process. 
 */
void initBenchmark(void);

/** \fn void startBenchmark(void)
 *      \brief Resets and starts the hardware counter.
 *      
 *      It should be called from every core.
 */
void startBenchmark(void);

/** \fn void finishBenchmark(void)
 *      \brief Declare the ending point of the measuring process.
 *
 *      The user needs to decide when to stop the measuring process 
 *      (a multiple of a critical time section is desired).
 *      At this point the idle task is updated and the Counter can be printed 
 *      (with printCounters(void (*printf)(const char *fmt, ...)) function).
 * 
 *      This function should be called from every core.
*/
void finishBenchmark(void);

/** 
 * \fn void startTask(uint8_t core_id, uint8_t task_id)
 *      \brief Declare the starting point of a task.
 * 
 *      Each task should have a starting point, at which task is put on stack.
 *      The task remains on the stack until it reaches a finish point.
 *      TaskCounter logs the running time of the task.
 *      There can only be one starting point, or a guarantee that it will never execute two starting points within the same run.
 * 
 *      \param unit8_t core_id     the ID of the core which is executing the task
 *      \param unit8_t task_id     the ID of the executing task (has to be at the interval [NUMBER_OF_CORES, NUMBER_OF_TASKS + NUMBER_OF_CORES]).
 *      
*/
void startTask(uint8_t core_id, uint8_t task_id);

/** 
 * \fn void finishTask(uint8_t core_id)
 *      \brief Declare the finish point of a task.
 * 
 *      Each task should have at least one finish point, at which task is put off stack.
 *      The task remains off the stack until it reaches a starting point.
 *      TaskCounter logs the average running time and its variance.
 * 
 *      \param unit8_t core_id     the ID of the core which is executing the task
*/
void finishTask(uint8_t core_id);


/** 
 * \fn void waitSemafor(uint8_t core_id)
 *      \brief Declare the synchronisation request of a task.
 * 
 *      In a real time environment tasks often need a synchronisation mechanism.
 *      When a task request synchronisation it is put off the stack until the synchronisation is complete. 
 * 
 *      \param unit8_t core_id     the ID of the core which is executing the task 
*/
void waitSemafor(uint8_t core_id);


/** 
 * \fn void semaforGreen(uint8_t core_id, uint8_t task_id)
 *      \brief Declare the synchronisation of a task.
 * 
 *      When a task is synchronized it is put back on the stack.
 *      TaskCounter continiues to log the execution time.
 * 
 *      \param unit8_t core_id     the ID of the core which is executing the task 
 *      \param unit8_t task_id     the ID of the executing task (has to be at the interval [NUMBER_OF_CORES, NUMBER_OF_TASKS + NUMBER_OF_CORES]).
*/
void semaforGreen(uint8_t core_id, uint8_t task_id);



/**
 * \fn void printCounters(void (*printf)(const char *fmt, ...))
 *      \brief print the values of the task counters
 *
 *      The counter should be printed after the measuring process has been finished.
 *      The user can direct the information to a desired output by providing a printf-like function.
 * 
 *      \param printf a printf-like function that prints to a desired output.
*/
void printCounters(void (*printf)(const char *fmt, ...));

#endif /* BENCHMARK_C_ */

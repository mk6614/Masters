/*
 * task_stack.h
 *
 *  Created on: 2 Dec 2020
 *      Author: mojca
 */

#ifndef TASK_STACK_H_
#define TASK_STACK_H_

#include "TaskCounter.h"
#include "BenchmarkCfg.h"


typedef struct {
	uint8_t top;
	uint8_t stack[NUMBER_OF_TASKS+1];
} stack;

#define STACK_POP(s)	s.stack[s.top--]
#define STACK_PUSH(s,v)	s.stack[++s.top]=v
#define STACK_TOP(s)	s.stack[s.top]
#define STACK_INIT(s,initTask)	s.top=0;s.stack[0]=initTask
#define TASK_LIST_INIT(l)	uint8_t i=0; while(i++<NUMBER_OF_TASKS) initTaskCounter(&l[i])
#define RES_LIST_INIT(l)	for (i=0; i<NUMBER_OF_RESOURCES; i++) resource_list[i] = 0

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused"

static task_counter task_list[NUMBER_OF_TASKS+NUMBER_OF_CORES];
static stack task_stack[NUMBER_OF_CORES];

#pragma GCC diagnostic pop

/**
 * \brief init the task stack
 *
 * the task stack logs the execution order to update the task counters accordingly
 */
void initTaskStack(void);

/**
 * \brief updates the previously running task and pushes itself on the stack
 */
void onTaskStart(uint8_t core_id, uint8_t task_id, perf_counter tmp_counter);


/**
 * \brief updates and pops itself
 */
void onTaskFinish(uint8_t core_id, perf_counter tmp_counter);

/*
 *  \brief updates and pops itself from the stack
 */
void onSemaforWait(uint8_t core_id, perf_counter tmp_counter);

/*
 * \brief updates the previous task and pushes itself back on the stack
 */

void onSemaforGreen(uint8_t core_id, uint8_t task_id, perf_counter tmp_counter);

/**
 * \brief finishes the idle task
 */
void onFinish(uint8_t task_id);

/*
 * \brief prints all the counters' values
 */
void printTaskCounters(void (*printf)(const char *fmt, ...));







#endif /* TASK_STACK_H_ */

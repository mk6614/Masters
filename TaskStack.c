/*
 * task_stack.c
 *
 *  Created on: 2 Dec 2020
 *      Author: mojca
 */

#include "TaskStack.h"

void initTaskStack(void)
{
	STACK_INIT(task_stack); 		//put the idle task on stack
	int8_t i= 0;
	for (i=0; i<=NUMBER_OF_TASKS; i++)
	{
		initTaskCounter(&task_list[i]);
	}
}

void onTaskStart(uint8_t task_id, perf_counter tmp_counter)
{
	//update previously running
	updateTaskExecCounter(&task_list[STACK_TOP(task_stack)], tmp_counter);
	//push yourself on stack
	STACK_PUSH(task_stack,task_id);
}

void onTaskFinish(perf_counter tmp_counter)
{
	//finish task and pop itself
	finishTaskExecCounter(&task_list[STACK_POP(task_stack)], tmp_counter);
}


void onSemaforWait(perf_counter tmp_counter)
{
	//update itself
	updateTaskExecCounter(&task_list[STACK_POP(task_stack)], tmp_counter);
	//push the current owner of the resource on the task stack
	
}

void onSemaforGreen(uint8_t task_id, perf_counter tmp_counter)
{
	//update the task that released the resource and pop the task from stack
	updateTaskExecCounter(&task_list[STACK_TOP(task_stack)], tmp_counter);
	STACK_PUSH(task_stack, task_id);
}

void finishIdleTask(perf_counter tmp_counter)
{
	//update the task that was interrupted by this request
	finishTaskExecCounter(&task_list[0], tmp_counter);
}


void printTaskCounters(void (*printf)(const char *fmt, ...))
{
	uint8_t i = 0;
	printf("task id, task exec counter");
#ifdef MEASURE_WAITING_TIME
	printf(", semafor exec counter, waiting sum, waiting avg, waiting var, waiting min, waiting max");
#endif

#ifdef MEASURE_CLK
	printf(", clk sum, clk avg, clk var, clk min, clk max");
#endif
#ifdef MEASURE_INSTRUCTIONS
	printf(", instruction sum, instruction avg, instruction var, instruction min, instruction max");
#endif
	printf(NEW_LINE);

	for(i=0; i <= NUMBER_OF_TASKS; i++)
	{
		printf("%u, ", i);
		printCounter(&task_list[i], printf);
	}

}





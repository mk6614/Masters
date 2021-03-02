/*
 * task_stack.c
 *
 *  Created on: 2 Dec 2020
 *      Author: mojca
 */

#include "TaskStack.h"

void initTaskStack(void)
{
	int i,j;
	for (i=0;i<NUMBER_OF_CORES; i++) STACK_INIT(task_stack[i],i); //puts the idle tasks on stack
	for (j=0; j<NUMBER_OF_TASKS+NUMBER_OF_CORES; j++) initTaskCounter(&task_list[j]);

}

void onTaskStart(uint8_t core_id, uint8_t task_id, perf_counter tmp_counter)
{
	//update previously running
	updateTaskExecCounter(&task_list[STACK_TOP(task_stack[core_id])], tmp_counter);
	//push yourself on stack
	STACK_PUSH(task_stack[core_id],task_id);
}

void onTaskFinish(uint8_t core_id, perf_counter tmp_counter)
{
	//finish task and pop itself
	finishTaskExecCounter(&task_list[STACK_POP(task_stack[core_id])], tmp_counter);
}


void onSemaforWait(uint8_t core_id, perf_counter tmp_counter)
{
	//update itself
	updateTaskExecCounter(&task_list[STACK_POP(task_stack[core_id])], tmp_counter);
	//push the current owner of the resource on the task stack
	
}

void onSemaforGreen(uint8_t core_id, uint8_t task_id, perf_counter tmp_counter)
{
	//update the task that released the resource and pop the task from stack
	updateTaskExecCounter(&task_list[STACK_TOP(task_stack[core_id])], tmp_counter);
	STACK_PUSH(task_stack[core_id], task_id);
}

void onFinish(uint8_t task_id)
{
	finishIdleTask(&task_list[task_id]);
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

	for(i=0; i < NUMBER_OF_TASKS+2; i++)
	{
		printf("%u, ", i);
		printCounter(&task_list[i], printf);
	}

}





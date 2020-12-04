/*
 * task_stack.c
 *
 *  Created on: 2 Dec 2020
 *      Author: mojca
 */

#include "task_stack.h"


void initTaskStack(void)
{
	STACK_INIT(task_stack); 		//put the idle task on stack
	TASK_LIST_INIT(task_list); 		//init the task_list counters with init values
	RES_LIST_INIT(resource_list);	//init the resource reservation list
	//task_list[0].exec_counter = 1; 	//set the execution counter of the idle task
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
	//update and pop itself
	updateTaskExecCounter(&task_list[STACK_POP(task_stack)], tmp_counter);
}


void onResourceRequest(uint8_t resource_id, perf_counter tmp_counter)
{
	//update itself
	updateTaskExecCounter(&task_list[STACK_TOP(task_stack)], tmp_counter);
	//push the current owner of the resource on the task stack
	STACK_PUSH(task_stack, resource_list[resource_id]);
}

void onResourceResume(uint8_t resource_id, perf_counter tmp_counter)
{
	//update the task that released the resource and pop the task from stack
	updateTaskExecCounter(&task_list[STACK_POP(task_stack)], tmp_counter);
	//mark the ownership of the resource
	resource_list[resource_id] = task_stack.stack[task_stack.top]; //should equal task_id
}

void onResourceRelease(uint8_t resource_id)
{
	resource_list[resource_id] = 0; //pass the ownership to the idle task
}

void finishIdleTask(perf_counter tmp_counter)
{
	//update the task that was interrupted by this request
	updateTaskExecCounter(&task_list[STACK_TOP(task_stack)], tmp_counter);
	//finish the idle task
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
	printf("\n\b\r");

	for(i=0; i <= NUMBER_OF_TASKS; i++)
	{
		printf("%u, ", i);
		printCounter(&task_list[i], printf);
	}

}





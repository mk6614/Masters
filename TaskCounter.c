/*
 * TaskCounter.c
 *
 *  Created on: 2 Dec 2020
 *      Author: mojca
 */

#ifndef TASK_COUNTER_C_
#define TASK_COUNTER_C_

#include "BenchmarkCfg.h"
#include "TaskCounter.h"



void initTaskCounter(task_counter* counter)
{
	counter->exec_counter = 0;
	counter->clk_time = 0;
	counter->clk_mean = 0;
	counter->clk_min = 0xffffffff;
	counter->clk_max = 0;
	counter->clk_M2 = 0;
}

void updateTaskExecCounter(task_counter* counter, perf_counter tmp_counter)
{
	counter->clk_time += tmp_counter.clk;
}

void finishIdleTask(task_counter* counter)
{
	counter->exec_counter++;
	counter->clk_mean += counter->clk_time;
}

void finishTaskExecCounter(task_counter* counter, perf_counter tmp_counter)
{
	updateTaskExecCounter(counter, tmp_counter);
	counter->exec_counter++;
	int32_t d1 = counter->clk_time - counter->clk_mean;
	counter->clk_mean += d1 / counter->exec_counter;
	int32_t d2 = counter->clk_time - counter->clk_mean;
	counter->clk_M2 += d1 * d2;
	SET_MIN(counter->clk_time, counter->clk_min);
	SET_MAX(counter->clk_time, counter->clk_max);
	counter->clk_time=0;
}

void printCounter(task_counter* counter, void (*printf)(const char *fmt, ...))
{
	if (counter->exec_counter== 0) {
		printf("execution counter equals 0%s", NEW_LINE);
		return;
	} 
	else 
	{
		printf("%u", (unsigned int) counter->exec_counter);
		printf(", %lu, %lu, %ld, %lu", (unsigned long) counter->clk_mean,(unsigned long) (counter->clk_M2/counter->exec_counter), (unsigned long) counter->clk_min, (unsigned long) counter->clk_max);
		printf(NEW_LINE);
	}
}


#endif /* TASK_COUNTER_C_ */

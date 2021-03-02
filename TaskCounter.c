/*
 * task_counter.c
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
#ifdef MEASURE_WAITING_TIME
	counter->semafor_exec_counter = 0;
	counter->waiting_time = 0;
	counter->waiting_sum = 0;
	counter->waiting_min = 0xffffffff;
	counter->waiting_max = 0;
	counter->waiting_var = 0;
#endif
#ifdef MEASURE_CLK
	counter->clk_time = 0;
	counter->clk_sum = 0;
	counter->clk_min = 0xffffffff;
	counter->clk_max = 0;
	counter->clk_var = 0;
#endif
#ifdef MEASURE_INSTRUCTIONS
	counter->inst_sum = 0;
	counter->inst_time = 0;
	counter->inst_min = 0xffffffff;
	counter->inst_max = 0;
	counter->inst_var = 0;
#endif
}

void updateTaskExecCounter(task_counter* counter, perf_counter tmp_counter)
{
#ifdef MEASURE_WAITING_TIME

#endif
#ifdef MEASURE_CLK
	counter->clk_time += tmp_counter.clk;
#endif
#ifdef MEASURE_INSTRUCTIONS
	counter->inst_time += tmp_counter.ist;
#endif
}

void finishIdleTask(task_counter* counter)
{
	counter->exec_counter++;
#ifdef MEASURE_WAITING_TIME
	counter->semafor_exec_counter++;
#endif
#ifdef MEASURE_CLK
	counter->clk_sum += counter->clk_time;
#endif
#ifdef MEASURE_INSTRUCTIONS
	counter->inst_sum += counter->inst_time;
#endif
}

void finishTaskExecCounter(task_counter* counter, perf_counter tmp_counter)
{
	updateTaskExecCounter(counter, tmp_counter);
	int32_t tmp;
	counter->exec_counter++;
#ifdef MEASURE_WAITING_TIME
	counter->semafor_exec_counter++;
	counter->waiting_sum += counter->waiting_time;
	SET_MIN(counter->waiting_time, counter->clk_min);
	SET_MAX(counter->waiting_time, counter->clk_max);
	int32_t tmp = counter->waiting_sum/counter->semafor_exec_counter - counter->waiting_time;
	counter->waiting_var += tmp*tmp;
	counter->waiting_time = 0;
#endif
#ifdef MEASURE_CLK
	counter->clk_sum += counter->clk_time;
	SET_MIN(counter->clk_time, counter->clk_min);
	SET_MAX(counter->clk_time, counter->clk_max);
	tmp = (counter->clk_sum/counter->exec_counter) - counter->clk_time;
	//TODO: uporabi Welford's online algorithm
	counter->clk_var += tmp;
	counter->clk_time=0;
#endif
#ifdef MEASURE_INSTRUCTIONS
	counter->inst_sum += counter->inst_time;
	SET_MIN(counter->inst_time, counter->inst_min);
	SET_MAX(counter->inst_time, counter->inst_max);
	tmp = (counter->inst_sum/counter->exec_counter) - counter->inst_time;
	counter->inst_var += tmp*tmp;
	counter->inst_time = 0;
#endif
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
		#ifdef MEASURE_WAITING_TIME
				printf(", %u, %llu, %lu, %lu, %lu, %lu",(unsigned int) counter->semafor_exec_counter, (unsigned longlong) counter->waiting_sum, (long) (counter->clk_sum/counter->exec_counter), (unsigned long) counter->waiting_var, (unsigned long) counter->clk_min, (unsigned long) counter->clk_max);
		#endif
		#ifdef MEASURE_CLK
				printf(", %llu, %lu, %ld, %lu, %lu", (unsigned long long) counter->clk_sum,(unsigned long) (counter->clk_sum/counter->exec_counter), (long)counter->clk_var, (unsigned long) counter->clk_min, (unsigned long) counter->clk_max);
		#endif
		#ifdef MEASURE_INSTRUCTIONS
				printf(", %llu, %lu, %ld, %lu, %lu", (unsigned long long)counter->inst_sum, (unsigned long)(counter->inst_sum/counter->exec_counter), (long)counter->inst_var, (unsigned long)counter->inst_min, (unsigned long)counter->inst_max);
		#endif
				printf(NEW_LINE);
	}
}


#endif /* TASK_COUNTER_C_ */

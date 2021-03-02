/*
 * task_counter.h
 *
 *  Created on: 2 Dec 2020
 *      Author: mojca
 */

#ifndef TASK_COUNTER_H_
#define TASK_COUNTER_H_

#include "BenchmarkCfg.h"
#include "PerformanceCounter.h"

#define SET_MIN(x,min)	if (x<min) min=x;
#define SET_MAX(x,max)	if (x>max) max=x;


typedef struct {
#ifdef MEASURE_WAITING_TIME
	uint8_t semafor_exec_counter;
	uint32_t waiting_time;
	uint64_t waiting_sum;
	uint32_t waiting_min;
	uint32_t waiting_max;
	uint64_t waiting_var;
#endif
#ifdef MEASURE_CLK
	uint64_t clk_sum;
	int64_t clk_var;
	uint32_t clk_time;
	uint32_t clk_min;
	uint32_t clk_max;
#endif
#ifdef MEASURE_INSTRUCTIONS
	uint64_t inst_sum;
	uint32_t inst_time;
	uint32_t inst_min;
	uint32_t inst_max;
	uint64_t inst_var;
#endif

	uint8_t exec_counter;

} task_counter;

void initTaskCounter(task_counter* counter);

void updateTaskExecCounter(task_counter* counter, perf_counter tmp_counter);

void finishTaskExecCounter(task_counter* counter, perf_counter tmp_counter);

void printCounter(task_counter* counter, void (*printf)(const char *fmt, ...));

void finishIdleTask(task_counter* counter);



#endif /* TASK_COUNTER_H_ */

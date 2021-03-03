/*
 * TaskCounter.h
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
	//the mean and variance are calculated using Welford's online algorithm
	uint32_t clk_mean;
	uint32_t clk_M2; // variance = clk_M2 / exec_counter, stdv = sqrt(variance)
	
	uint32_t clk_time;
	uint32_t clk_min;
	uint32_t clk_max;

	uint8_t exec_counter;

} task_counter;

void initTaskCounter(task_counter* counter);

void updateTaskExecCounter(task_counter* counter, perf_counter tmp_counter);

void finishTaskExecCounter(task_counter* counter, perf_counter tmp_counter);

void printCounter(task_counter* counter, void (*printf)(const char *fmt, ...));

void finishIdleTask(task_counter* counter);



#endif /* TASK_COUNTER_H_ */

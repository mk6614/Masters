/*
 * perf_counter.h
 *
 *  Created on: 2 Dec 2020
 *      Author: mojca
 */


#ifndef PERF_COUNTER_H_
#define PERF_COUNTER_H_

#include "BenchmarkCfg.h"

typedef struct {
	uint32_t clk; //number of ticks
	uint32_t ist; //number of instructions
	uint32_t m1; //configurable
	uint32_t m2; //configurable
	uint32_t m3; //configurable
} perf_counter;

/**
 * \brief initialises the free-running performance counter on the board
 */
void __initPerfCounter(void);

/**
 * \brief start the performance counter
 */
void __startPerfCounter(void);

/**
 * \brief stop the performance counter
 */
void __stopPerfCounter(void);

/**
 * \brief read the performance counter
 */
perf_counter __readPerfCounter(void);

/**
 * \brief resets the performance counter values
 */
void __resetPerfCounter(void);




#endif /* PERF_COUNTER_H_ */

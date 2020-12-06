/*
 * per_config.h
 *
 *  Created on: 28 Oct 2020
 *      Author: Mojca Kolšek
 */

#ifndef PERF_CONFIG_H_
#define PERF_CONFIG_H_

#define TCPATH tc26xb

#ifndef USE_BR
#define NEW_LINE "\r\n"
#else
#define NEW_LINE "\n\b\r"
#endif


#define NUMBER_OF_TASKS 5
#define NUMBER_OF_RESOURCES 0

//user can measure on of the following per performance test:
#define MEASURE_CLK
//#define MEASURE_INSTRUCTIONS


/**
 * \brief measures the time spent waiting for a resource in CLK ticks
 *
 * If this parameter is defined, non others are allowed to be defined
 */
//#define MEASURE_WAITING_TIME


#ifdef  MEASURE_WAITING_TIME
	#if defined(MEASURE_CLK) || defined(MEASURE_INSTRUCTIONS)
		#error "MEASURE_WAITING_TIME can not be used with combination with other parameters."
	#endif
#endif

//what the test modules are measuring, is defined by MEASURE MODE
// consists of 4 numbers:
//	1 bit: either 0 or 1
// 3x3bits: dependant of the CPU architecture (1.6E/1.6(.1/.2)P)
#define MEASURE_MODE 0,0,0,0

//additionaliy, user can measure the waiting time of the task, caused by shared resources, by defining MEASURE_WAITING_TIME:
//#define MEASURE_WAITING_TIME






#endif /* PERF_CONFIG_H_ */

/*
 * benchmark.c
 *
 *  Created on: 2 Dec 2020
 *      Author: mojca
 */

#ifndef BENCHMARK_C_
#define BENCHMARK_C_


#include "perf_config.h"
#include "perf_counter.h"
#include "task_stack.h"


#if (defined(__GNUC__))
#if(!defined(TCPATH))
#error "Please define the TCPATH as defined in HighTec IDE" //example: #define TCPATH tc26xb
#endif
	#define TC_STR(s)		# s
	#define TC_INCLUDE(f)	TC_STR(f)
	#include TC_INCLUDE(TCPATH/Ifx_reg.h) // includes IfxCpu_reg.h, IfxCpu_bf.h and all others)
	#include "machine/intrinsics.h"
	#include "machine/stdlib.h"
    #include "stdint.h"
	#define MFCR _mfcr
	#define MTCR _mtcr
#elif (defined(__TASKING__))
	//#ifdef __CPU__
	//	#include __SFRFILE__(__CPU__)
	//#endif
    #include "IfxCpu_reg.h"
    #include "Ifx_Types.h"
	#define MFCR __mfcr
	#define MTCR __mtcr
#define uint8_t     uint8
#define uint32_t    uint32
#define uint64_t    uint64
#define int32_t     sint32
#else
#error "Unknown compilers. Please define __GNUC__ or __TASKING__"
#endif /* __GNUC__ || __TASKING__ */

/**
 * \brief initialisation of the performance counter and structs to hold the values
 *
 *  The information for the init process is provided by benchmark_conf.h file:
 *  NUMBER_OF_TASKS+1 value holders (structs) are created (an additional one is used as an idle task)
 *  MEASURE_XXX defines what the benchmark measures
 */

/**
 * \brief initialises the performance counter and reserves space for task counters
 */
void initBenchmark(void);

/**
 * \brief declare the starting point of the task
 */
void startTask(uint8_t task_id);

/**
 * \brief declare the ending point of a task
 */
void finishTask(void);

/**
 * \brief declare the point of resource reservation
 */
void requestResource(uint8_t resource_id);

/**
 * \brief declare the point of the gotten resource
 */
void takeResource(uint8_t resource_id);

/**
 * \brief declare the point of the resource release
 */
void releaseResource(uint8_t resource_id);
/**
 * \brief declare the starting point of the measuring process
 *
 * Call this before the task execution (before the OS start)
 */

void startBenchmark(void);

/**
 * \brief declare the ending point of the measuring process
 *
 * The user needs to decide when to stop the measuring process.
 * At this point the idle task is updated and the counters can be printed and the report generated.
*/

void finishBenchmark(void);

/**
 * \brief print the values of the task counters
 * \param printf a blocking! function that prints to a desired output.
 *
 * The printf should be blocking so the measuring process is not affected by the resource reservation of the printing process
 */
void printCounters(void (*printf)(const char *fmt, ...));

/**
 * \brief generates a report from the values of the counters.
 * \param printf a blocking! function that prints to a desired output.
 *
 * The printf should be blocking so the measuring process is not affected by the resource reservation of the printing process
 *
 */
void generateReport(void (*printf)(const char *fmt, ...));


#endif /* BENCHMARK_C_ */

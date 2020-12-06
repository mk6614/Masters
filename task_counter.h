/*
 * task_counter.h
 *
 *  Created on: 2 Dec 2020
 *      Author: mojca
 */

#ifndef TASK_COUNTER_H_
#define TASK_COUNTER_H_

#include "perf_config.h"
#include "perf_counter.h"


#if (defined(__GNUC__))
/*
#if(!defined(TCPATH))
#error "Please define the TCPATH as defined in HighTec IDE" //example: #define TCPATH tc26xb
#endif
	#define TC_STR(s)		# s
	#define TC_INCLUDE(f)	TC_STR(f)
	#include TC_INCLUDE(TCPATH/Ifx_reg.h) // includes IfxCpu_reg.h, IfxCpu_bf.h and all others
	#include "machine/intrinsics.h"
*/
    #include "stdint.h"
	#define MFCR _mfcr
	#define MTCR _mtcr
#elif (defined(__TASKING__))
	//#ifdef __CPU__
	//	#include __SFRFILE__(__CPU__)
	//#endif
    //#include "IfxCpu_reg.h"
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

#define SET_MIN(x,min)	if (x<min) min=x;
#define SET_MAX(x,max)	if (x>max) max=x;


typedef struct {
	uint8_t exec_counter;
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
	uint32_t clk_time;
	uint32_t clk_min;
	uint32_t clk_max;
	uint64_t clk_var;
#endif
#ifdef MEASURE_INSTRUCTIONS
	uint64_t inst_sum;
	uint32_t inst_time;
	uint32_t inst_min;
	uint32_t inst_max;
	uint64_t inst_var;
#endif

} task_counter;

void initTaskCounter(task_counter* counter);

void updateTaskExecCounter(task_counter* counter, perf_counter tmp_counter);

void finishTaskExecCounter(task_counter* counter, perf_counter tmp_counter);

void printCounter(task_counter* counter, void (*printf)(const char *fmt, ...));

void finishIdleTask(perf_counter tmp_counter);



#endif /* TASK_COUNTER_H_ */

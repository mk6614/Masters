/*
 * BenchmarkCfg.h
 *
 *  Created on: 28 Oct 2020
 *      Author: Mojca Kolšek
 */

#ifndef PERF_CONFIG_H_
#define PERF_CONFIG_H_

#define TCPATH tc26xb
#define ERIKA_OS

#define NEW_LINE "\r\n"

#define NUMBER_OF_CORES	2
#define NUMBER_OF_TASKS 5
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
//	1-bit number: either 0 or 1
// 	3 3-bit numbers: dependant of the CPU architecture (1.6E/1.6(.1/.2)P)
#define MEASURE_MODE 0,0,0,0

//additionaliy, user can measure the waiting time of the task, caused by shared resources, by defining MEASURE_WAITING_TIME:
//#define MEASURE_WAITING_TIME


#if (defined(UNITTEST_ENV))
	#include "stdint.h"
	#warning "Compiling for unit tests."
	#define uint8_t     unsigned char
	#define uint32_t    unsigned long
	#define uint64_t    unsigned long long
	#define int32_t     long
	#ifdef MEASURE_INSTRUCTIONS
		#undef MEASURE_INSTRUCTIONS
	#endif
#elif(defined(__GNUC__))
	#if (!defined(TCPATH))
		#error Please define the TCPATH as defined in HighTec IDE //example: #define TCPATH tc26xb
	#endif
	#define TC_STR(s)		# s
	#define TC_INCLUDE(f)	TC_STR(f)
	#include TC_INCLUDE(TCPATH/Ifx_reg.h) // includes IfxCpu_reg.h, IfxCpu_bf.h and all others
	#include "machine/intrinsics.h"
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
	#error Unknown compilers. Please define __GNUC__ or __TASKING__
#endif // UNITTEST_ENV

#endif /* PERF_CONFIG_H_ */

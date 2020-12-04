/*
 * perf_counter.h
 *
 *  Created on: 2 Dec 2020
 *      Author: mojca
 */


#ifndef PERF_COUNTER_H_
#define PERF_COUNTER_H_

#include "perf_config.h"


#if (defined(__GNUC__))
#if(!defined(TCPATH))
	#error "Please define the TCPATH as defined in HighTec IDE" //example: #define TCPATH tc26xb
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
#endif /* __GNUC__ || __TASKING__ */

//value of sticky overflow flag
#define OVF(c)	(0x8000 & c)
//returns the value of the counter c without the sticky bit
#define VALUE(c) (0x7FFF & c)

#define READ_COUNTER(c)		MFCR(c)
#define RESET_COUNTER(c)	MTCR(c, 0x0000)

static Ifx_CPU_CCTRL cctrl; //holds values for counter configuration

/**
 * \brief struct to store all counters
 * each counters last bit is sticky overflow flag
 */
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

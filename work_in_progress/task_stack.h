/*
 * task_stack.h
 *
 *  Created on: 2 Dec 2020
 *      Author: mojca
 */

#ifndef TASK_STACK_H_
#define TASK_STACK_H_

#include "task_counter.h"
#include "perf_config.h"


#if (defined(__GNUC__))
#if(!defined(TCPATH))
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
#endif /* __GNUC__ || __TASKING__ */

typedef struct {
	uint8_t top;
	uint8_t stack[NUMBER_OF_TASKS+1];
} stack;

#define STACK_POP(s)	s.stack[s.top--]
#define STACK_PUSH(s,v)	s.stack[++s.top]=v
#define STACK_TOP(s)	s.stack[s.top]
#define STACK_INIT(s)	s.top=0;s.stack[0]=0
#define TASK_LIST_INIT(l)	uint8_t i=0; while(i++<NUMBER_OF_TASKS) initTaskCounter(&l[i])
#define RES_LIST_INIT(l)	for (i=0; i<NUMBER_OF_RESOURCES; i++) resource_list[i] = 0

static task_counter task_list[NUMBER_OF_TASKS+1];
static stack task_stack;
static resource_priorities[NUMBER_OF_RESOURCES];
static resource_list[NUMBER_OF_RESOURCES];

/**
 * \brief init the task stack
 *
 * the task stack logs the execution order to update the task counters accordingly
 */
void initTaskStack(void);

/**
 * \brief updates the previously running task and pushes itself on the stack
 */
void onTaskStart(uint8_t task_id, perf_counter tmp_counter);


/**
 * \brief updates and pops itself
 */
void onTaskFinish(perf_counter tmp_counter);

/*
 *  \brief updates itself and pushes the owner of the resource on the stack
 */
void onResourceRequest(uint8_t resource_id, perf_counter tmp_counter);

/*
 * \brief updates the previous resource owner and marks itself as the new owner
 */
void onResourceResume(uint8_t resource_id, perf_counter tmp_counter);

/**
 * \brief marks the idle task as the new resource owner
 */
void onResourceRelease(uint8_t resource_id);

/**
 * \brief finishes the idle task
 */
void finishIdleTask(perf_counter tmp_counter);

/*
 * \brief prints all the counters' values
 */
void printTaskCounters(void (*printf)(const char *fmt, ...));







#endif /* TASK_STACK_H_ */

//#define __GNUC__

#include "perf_config.h"
#define TCPATH tc26xb

#if (defined(__GNUC__))
	#define TC_STR(s)		# s
	#define TC_INCLUDE(f)	TC_STR(f)
	#include TC_INCLUDE(TCPATH/Ifx_reg.h) // includes IfxCpu_reg.h, IfxCpu_bf.h and all others)
	#include "machine/intrinsics.h"
	#include "machine/stdlib.h"
    #include "stdint.h"

	//#include "stdint.h"
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
#error "Compiler is not supported"
#endif /* __GNUC__ || __TASKING__ */





//value of sticky overflow flag
#define OVF(c)	(0x8000 & c)
//returns the value of the counter c
#define VALUE(c) (0x7FFF & c)

#define READ_COUNTER(c)		MFCR(c)
#define RESET_COUNTER(c)	MTCR(c, 0x0000)

/**
 * \brief struct to store all counters
 * each counters last bit is sticky overflow flag
 */

typedef struct {
	uint32_t clk;
	uint32_t ist;
	uint32_t m1;
	uint32_t m2;
	uint32_t m3;
} perf_counter;

void __init_perf_counter(uint8_t m, uint8_t m1, uint8_t m2, uint8_t m3);
inline void __stopCounter(void);
inline void __startCounter(void);
inline perf_counter __read_counter(void);

typedef struct {
	uint8_t top;
	uint8_t stack[NUMBER_OF_TASKS+1];
} stack;

#define STACK_POP(s)	s.stack[s.top--]
#define STACK_PUSH(s,v)	s.stack[++s.top]=v
#define STACK_TOP(s)	s.stack[s.top]
#define STACK_INIT(s)	s.top=0;s.stack[0]=0
#define LIST_INIT(l)	uint8_t i=0; while(i++<NUMBER_OF_TASKS) initTaskCounter(&l[i])

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

static task_counter task_list[NUMBER_OF_TASKS+1];
static stack task_stack;

void initTaskCounter(task_counter* init);
void stopTaskCounter(task_counter* counter, perf_counter tmp_counter);
void pauseTaskCounter(task_counter* counter, perf_counter tmp_counter);


void initPerformanceTest(void);
void stopPerformanceTest(void);
void startTask(uint8_t priority);
void stopTask(void);
void waitForResource(void);
void resumeOnResource(uint8_t priority);
void getCounter(uint8_t priority, task_counter* ret);
void printCounters(void (*printf)(const char *fmt, ...));

void performBasicTest(void (*printf)(const char *fmt, ...));


/*
 * function wrappers: declare a task with MEASURE_TASK(FuncName), where FuncName is a void function name
 * the function is wrapped with startTask and stopTask for measuring purposes
 * Example:
 * 1)	define function void Task1(void)
 * 		 MEASURE_TASK(Task1) { int i; for (i=0; i<1000; i++) .... } -> call this function with TaskTask1();
 *
 */
#define DECLARE_TASK(FunName)	void ##FunName(void)
#define MEASURE_TASK(FunName, priority)	static void FunName(void); static void Task##FunName(void) { startTask(priority); FunName(); stopTask(); } static void FunName(void)
#define CALL_TASK(FunName)		Task##FunName();




#include "perf.h"

inline void __stopCounter(void)
{
	Ifx_CPU_CCTRL cctrl;
	//read counter
	cctrl.U    = __mfcr(CPU_CCTRL);
	/*clear Count Enable bit */
	cctrl.B.CE = 0;
	MTCR(CPU_CCTRL, cctrl.U);
}

inline void __startCounter(void)
{
	Ifx_CPU_CCTRL cctrl;
	//read counter
	cctrl.U    = __mfcr(CPU_CCTRL);
	/*set Count Enable bit */
	cctrl.B.CE = 1;
	MTCR(CPU_CCTRL, cctrl.U);
}



inline perf_counter __read_counter(void)
{
	perf_counter counter;
	counter.clk = READ_COUNTER(CPU_CCNT);
	counter.ist = READ_COUNTER(CPU_ICNT);
	counter.m1 = READ_COUNTER(CPU_M1CNT);
	counter.m2 = READ_COUNTER(CPU_M2CNT);
	counter.m3 = READ_COUNTER(CPU_M3CNT);
	return counter;
}


/**
 * \brief init performance counter with specified modes
 * \params have to be 0 or 1 (see CPU architecture manual)
 * @param m 	0 (normal) or 1 (tasking)
 * @param m1 	3 bits, implementation specific (TCXXX user manual)
 * @param m2 	3 bits, implementation specific
 * @param m3 	3 bits, implementation specific
 */
void __init_perf_counter(uint8_t m, uint8_t m1, uint8_t m2, uint8_t m3)
{
	//innit structure
	Ifx_CPU_CCTRL cctrl;
	//read the current unsigned access
	cctrl.U    = MFCR(CPU_CCTRL);
	cctrl.B.CE = 0;
	cctrl.B.M1 = 0x7 & m1;
	cctrl.B.M2 = 0x7 & m2;
	cctrl.B.M3 = 0x7 & m3;
	//write init structure to counter control register
	MTCR(CPU_CCTRL, cctrl.U);

	/* reset the counter */
	MTCR(CPU_CCNT, 0);
	MTCR(CPU_ICNT, 0);
	MTCR(CPU_M1CNT, 0);
	MTCR(CPU_M2CNT, 0);
	MTCR(CPU_M3CNT, 0);

	/*Enable the counter, set the counter mode */
	cctrl.B.CE = 1;
	cctrl.B.CM = 0x1 & m;
	MTCR(CPU_CCTRL, cctrl.U);
	RESET_COUNTER(CPU_CCTRL);
}

void initPerformanceTest()
{
	//TODO __init_perf_counter(m, m1, m2, m3);
	__init_perf_counter(0,0,0,0);
	LIST_INIT(task_list);
	STACK_INIT(task_stack);

	task_list[0].exec_counter=1;
}

void stopPerformanceTest(void)
{
	task_list[0].clk_sum += task_list[0].clk_time;
}



void stopTaskCounter(task_counter* counter, perf_counter tmp_counter)
{
	pauseTaskCounter(counter, tmp_counter);
	int32_t tmp;
	counter->exec_counter++;
#ifdef MEASURE_WAITING_TIME
	counter->semafor_exec_counter++;
	counter->waiting_sum += counter->waiting_time;
	SET_MIN(counter->waiting_time, counter->clk_min);
	SET_MAX(counter->waiting_time, counter->clk_max);
	int32_t tmp = counter->waiting_sum/counter->semafor_exec_counter - counter->waiting_time;
	counter->waiting_var += tmp*tmp;
	counter->waiting_time = 0;
#endif
#ifdef MEASURE_CLK
	counter->clk_sum += counter->clk_time;
	SET_MIN(counter->clk_time, counter->clk_min);
	SET_MAX(counter->clk_time, counter->clk_max);
	tmp = (counter->clk_sum/counter->exec_counter) - counter->clk_time;
	counter->clk_var += tmp*tmp;
	counter->clk_time=0;
#endif
#ifdef MEASURE_INSTRUCTIONS
	counter->inst_sum += counter->inst_time;
	SET_MIN(counter->inst_time, counter->inst_min);
	SET_MAX(counter->inst_time, counter->inst_max);
	tmp = (counter->inst_sum/counter->exec_counter) - counter->inst_time;
	counter->inst_var += tmp*tmp;
	counter->inst_time = 0;
#endif
}

void pauseTaskCounter(task_counter* counter, perf_counter tmp_counter)
{
#ifdef MEASURE_WAITING_TIME

#endif
#ifdef MEASURE_CLK
	counter->clk_time += tmp_counter.clk;
#endif
#ifdef MEASURE_INSTRUCTIONS
	counter->inst_time += tmp_counter.ist;
#endif
	RESET_COUNTER(CPU_CCNT);
}

void initTaskCounter(task_counter* counter)
{
	counter->exec_counter = 0;
#ifdef MEASURE_WAITING_TIME
	counter->semafor_exec_counter = 0;
	counter->waiting_time = 0;
	counter->waiting_sum = 0;
	counter->waiting_min = 0xffffffff;
	counter->waiting_max = 0;
	counter->waiting_var = 0;
#endif
#ifdef MEASURE_CLK
	counter->clk_time = 0;
	counter->clk_sum = 0;
	counter->clk_min = 0xffffffff;
	counter->clk_max = 0;
	counter->clk_var = 0;
#endif
#ifdef MEASURE_INSTRUCTIONS
	counter->inst_sum = 0;
	counter->inst_time = 0;
	counter->inst_min = 0xffffffff;
	counter->inst_max = 0;
	counter->inst_var = 0;
#endif

}

void startTask(uint8_t priority)
{
	__stopCounter();
	pauseTaskCounter(&task_list[STACK_TOP(task_stack)], __read_counter());
	STACK_PUSH(task_stack, priority);
	__startCounter();
}

void stopTask()
{
	__stopCounter();
	stopTaskCounter(&task_list[STACK_POP(task_stack)], __read_counter());
	__startCounter();
}

void waitForResource()
{
	__stopCounter();
	pauseTaskCounter(&task_list[STACK_POP(task_stack)], __read_counter());
	__startCounter();

}

void resumeOnResource(uint8_t priority)
{
	__stopCounter();
	pauseTaskCounter(&task_list[STACK_TOP(task_stack)], __read_counter());
	STACK_PUSH(task_stack, priority);
	__startCounter();
}

void getCounter(uint8_t priority, task_counter* ret)
{
	ret->exec_counter = task_list[priority].exec_counter;
#ifdef MEASURE_WAITING_TIME
	ret->semafor_exec_counter = task_list[priority].semafor_exec_counter;
	ret->waiting_time = task_list[priority].waiting_time;
	ret->waiting_sum = task_list[priority].waiting_sum;
	ret->waiting_min = task_list[priority].waiting_min;
	ret->waiting_max = task_list[priority].waiting_max;
	ret->waiting_var = task_list[priority].waiting_var;
#endif
#ifdef MEASURE_CLK
	ret->clk_time = task_list[priority].clk_time;
	ret->clk_sum = task_list[priority].clk_sum;
	ret->clk_min = task_list[priority].clk_min;
	ret->clk_max = task_list[priority].clk_max;
	ret->clk_var = task_list[priority].clk_var;
#endif
#ifdef MEASURE_INSTRUCTIONS
	ret->inst_sum = task_list[priority].inst_sum;
	ret->inst_time = task_list[priority].inst_time;
	ret->inst_min = task_list[priority].inst_min;
	ret->inst_max = task_list[priority].inst_max;
	ret->inst_var = task_list[priority].inst_var;
#endif
}

void printCounters(void (*printf)(const char *fmt, ...))
{
	int cnt = 0;
	printf("task id, task exec counter");
#ifdef MEASURE_WAITING_TIME
	printf(", semafor exec counter, waiting sum, waiting avg, waiting var, waiting min, waiting max");
#endif

#ifdef MEASURE_CLK
	printf(", clk sum, clk avg, clk var, clk min, clk max");
#endif
#ifdef MEASURE_INSTRUCTIONS
	printf(", instruction sum, instruction avg, instruction var, instruction min, instruction max");
#endif
	printf("\n\b\r");


	while (cnt <= NUMBER_OF_TASKS)
	{
	printf("%u, %u", (unsigned int) cnt, (unsigned int) task_list[cnt].exec_counter);
#ifdef MEASURE_WAITING_TIME
		printf(", %u, %llu, %lu, %lu, %lu, %lu",(unsigned int) task_list[cnt].semafor_exec_counter, (unsigned longlong) task_list[cnt].waiting_sum, (unsigned long) (task_list[cnt].clk_sum/task_list[cnt].exec_counter), (unsigned long) task_list[cnt].waiting_var, (unsigned long) task_list[cnt].clk_min, (unsigned long) task_list[cnt].clk_max);
#endif
#ifdef MEASURE_CLK
		printf(", %llu, %lu, %lu, %lu, %lu", (unsigned long long) task_list[cnt].clk_sum,(unsigned long) (task_list[cnt].clk_sum/task_list[cnt].exec_counter), (unsigned long)task_list[cnt].clk_var, (unsigned long) task_list[cnt].clk_min, (unsigned long) task_list[cnt].clk_max);
#endif
#ifdef MEASURE_INSTRUCTIONS
		printf(", %llu, %lu, %lu, %lu, %lu", (unsigned long long)task_list[cnt].inst_sum, (unsigned long)(task_list[cnt].inst_sum/task_list[cnt].exec_counter), (unsigned long)task_list[cnt].inst_var, (unsigned long)task_list[cnt].inst_min, (unsigned long)task_list[cnt].inst_max);
#endif
		cnt++;
		printf("\n\b\r");
	}
}





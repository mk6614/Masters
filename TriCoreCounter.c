/*
 * perf_counter.c
 *
 *  Created on: 2 Dec 2020
 *      Author: mojca
 */

#include "PerformanceCounter.h"


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


void __stopPerfCounter(void)
{
	/*clear Count Enable bit */
	cctrl.B.CE = 0;
	MTCR(CPU_CCTRL, cctrl.U);
}

void __startPerfCounter(void)
{
	cctrl.B.CE = 1;
	MTCR(CPU_CCTRL, cctrl.U);
}



perf_counter __readPerfCounter(void)
{
	perf_counter counter;
	counter.clk = READ_COUNTER(CPU_CCNT);
	counter.ist = READ_COUNTER(CPU_ICNT);
	counter.m1 = READ_COUNTER(CPU_M1CNT);
	counter.m2 = READ_COUNTER(CPU_M2CNT);
	counter.m3 = READ_COUNTER(CPU_M3CNT);
	return counter;
}

void __resetPerfCounter(void)
{
	RESET_COUNTER(CPU_CCNT);
	RESET_COUNTER(CPU_ICNT);
	RESET_COUNTER(CPU_M1CNT);
	RESET_COUNTER(CPU_M2CNT);
	RESET_COUNTER(CPU_M3CNT);
}


/**
 * \brief init performance counter with specified modes
 *
 * \param m 	0 (normal) or 1 (tasking)
 * \param m1 	3 bits, implementation specific (TCXXX user manual, for example TC26x_B-step UM)
 * \param m2 	3 bits, implementation specific
 * \param m3 	3 bits, implementation specific
 *
 * The M1,M2,M3 can be configured to measure instruction/data cache misses/hits, dispatch stall, branching...
 * The configuration depends on the CPU architecture (i.e. 1.6E does not have cache)
 */
void __initPerfCounter()
{
	//read the unsigned access
	cctrl.U    = MFCR(CPU_CCTRL);
	cctrl.B.CE = 0;
	cctrl.B.M1 = 0x7 & 0; //only 3 bits
	cctrl.B.M2 = 0x7 & 0;
	cctrl.B.M3 = 0x7 & 0;
	//write init structure to counter control register

	/* reset the counter values */
	MTCR(CPU_CCNT, 0);
	MTCR(CPU_ICNT, 0);
	MTCR(CPU_M1CNT, 0);
	MTCR(CPU_M2CNT, 0);
	MTCR(CPU_M3CNT, 0);

	//set the counter mode (0 - normal, 1 - tasking)
	cctrl.B.CM = 0x1 & 0; //only one bit
	//write params to register
	MTCR(CPU_CCTRL, cctrl.U);
}



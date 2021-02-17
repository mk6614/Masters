/*
 * perf_counter.c
 *
 *  Created on: 2 Dec 2020
 *      Author: Mojca Kolšek
 */

#include "../PerformanceCounter.h"
#include "time.h"

perf_counter end;
perf_counter start;
perf_counter res_counter;

void __stopPerfCounter(void)
{
	end.clk = (unsigned long) clock();
}

void __startPerfCounter(void)
{
	start.clk = (unsigned long) clock();
}



perf_counter __readPerfCounter(void)
{
	res_counter.clk = end.clk - start.clk;
	return res_counter;
}

void __resetPerfCounter(void)
{
	void;
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
	void;
}



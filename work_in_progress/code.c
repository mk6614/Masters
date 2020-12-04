/* ###*B*###
 * Erika Enterprise, version 3
 * 
 * Copyright (C) 2017 - 2019 Evidence s.r.l.
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License, version 2, for more details.
 * 
 * You should have received a copy of the GNU General Public License,
 * version 2, along with this program; if not, see
 * <www.gnu.org/licenses/old-licenses/gpl-2.0.html >.
 * 
 * This program is distributed to you subject to the following
 * clarifications and special exceptions to the GNU General Public
 * License, version 2.
 * 
 * THIRD PARTIES' MATERIALS
 * 
 * Certain materials included in this library are provided by third
 * parties under licenses other than the GNU General Public License. You
 * may only use, copy, link to, modify and redistribute this library
 * following the terms of license indicated below for third parties'
 * materials.
 * 
 * In case you make modified versions of this library which still include
 * said third parties' materials, you are obligated to grant this special
 * exception.
 * 
 * The complete list of Third party materials allowed with ERIKA
 * Enterprise version 3, together with the terms and conditions of each
 * license, is present in the file THIRDPARTY.TXT in the root of the
 * project.
 * ###*E*### */

/** \file	code.cpp
 *  \brief	Main application.
 *
 *  This file contains the code of main application for Erika Enterprise.
 *
 *  \author	Errico Guidieri
 *  \date  	2017
 */

/* ERIKA Enterprise. */
#include "ee.h"
//#include "benchmark.h"
#include "leds.h"
#include "uart_init_poll.c"

/* TASKs */
DeclareTask(Task1);
DeclareTask(Task2);
DeclareTask(Task3);
DeclareTask(Task4);
DeclareTask(Task5);



TASK(Task1)
{
	finishBenchmark();
	printCounters(my_printf);
	generateReport(my_printf);
	startTask(1);
	volatile uint32_t i;

	LEDON(1);
	osEE_tc_delay(1000000); //wait x microseconds
	//for(i=0; i< 20000000; i++);
	LEDOFF(1);

	ActivateTask(Task2);
	finishTask();
	TerminateTask();
}

TASK(Task2)
{
	startTask(2);
	volatile uint32_t i;

	LEDON(2);
	osEE_tc_delay(1000000); //wait x microseconds
	LEDOFF(2);

	ActivateTask(Task3);
	finishTask();
	TerminateTask();
}

TASK(Task3)
{
	startTask(3);
	volatile uint32_t i;

	LEDON(3);
	osEE_tc_delay(1000000); //wait x microseconds
	LEDOFF(3);

	ActivateTask(Task4);
	finishTask();
	TerminateTask();
}

TASK(Task4) {
	startTask(4);
	volatile uint32_t i;

	LEDON(4);
	osEE_tc_delay(1000000); //wait x microseconds
	LEDOFF(4);

	ActivateTask(Task5);
	finishTask();
	TerminateTask();
}

TASK(Task5) {
	startTask(5);
	volatile uint32_t i;

	LEDON(5);
	osEE_tc_delay(1000000); //wait x microseconds
	LEDOFF(5);

	finishTask();
	TerminateTask();
}

void idle_hook(void)
{
	while(1);
}

/*
 * MAIN TASK
 */
int main(void)
{
	initLEDs();
	LEDON(7);
	osEE_tc_delay(500000);
	_init_uart(115200);
	LEDON(6);
	//initBenchmark();
  //LEDOFF(1);
  StartOS(OSDEFAULTAPPMODE);


  return 0;
}


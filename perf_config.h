/*
 * per_config.h
 *
 *  Created on: 28 Oct 2020
 *      Author: Mojca Kolšek
 */

#ifndef PERF_CONFIG_H_
#define PERF_CONFIG_H_

#define NUMBER_OF_TASKS 5

//user can measure on of the following per performance test:
#define MEASURE_CLK
#define MEASURE_INSTRUCTIONS

//what the test modules are measuring, is defined by MEASURE MODE
#define MEASURE_MODE

//additionaliy, user can measure the waiting time of the task, caused by shared resources, by defining MEASURE_WAITING_TIME:
//#define MEASURE_WAITING_TIME






#endif /* PERF_CONFIG_H_ */

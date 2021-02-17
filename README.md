# Benchmark

The source files contain an implementation of the TriCore performance counter, which is able to number of count ticks, instruction and data/program cache hits and misses. 
The benchmark creates space for logging the counter for each task, specified by the user.
The benchmark can be run in 3 different environments;
* on pc, using makefile (the 17 feb. refactor has been tested)
* on TriCore target outside a real-time context, using HighTecIDE () (the 17 feb. refactor is not yet tested)
* on TriCore target inside a real-time context, using RTDruid IDE (Erika Enterprise) (the refactor is not zet tested)

## UnitTests folder and Makefile

With the `makefile` one can compile an executable for pc (with standard gcc compiler), namely `unittest_benchmark.exe`.
The makefile links to `UnitTest/UnitTestCounter.c` instead of `TriCoreCounter.c` and compiles all files with defined macro variable `UNITTEST_ENV`.

The file `UnitTests/UnitTestMain` demonstrates the use of the Benchmark;

* first, include the needed files;
  *  `Benchmark.h` file, which provides the functionality of the benchmark with through the use of so called TaskCounters,
  * `TaskDefinition.h` file, which describes the structure of the so called TASK function. When `UNITTEST_ENV` is defined, the TASK is defined as a `void` function.
  *  standard i/o library, to pass the needed `(void*) printf` like function to the benchmark print function,

```
#include "../Benchmark.h" 
#include "../TaskDefinition.h"
#include "stdio.h"
```
* define desired TASKs;
    * use TASK(name) macro to define a TASK
    * each TASK needs to be activated; activate the TASK by calling `startTask(id)` at the start of each TASK, where `id` is the tasks unique identification number on the interval `[1, NUMBER_OF_TASKS]`. You should define `NUMBER_OF_TASKS` as a macro variable in file `BenchmarkCfg.h`. Note that one additional TaskCounter will be created, utilized as an idle task, whose `id` corresponds to `0`.
    * each TASK needs to be terminated. If the TASK terminates at multiple point, declare all points. Terminate the TASK by calling `finishTask()` wherever needed.

```
TASK(task1)
{
    startTask(1)
    if (branch)
    {
        //some work
        finishTask();
    }
    else
    {
        //some other work
        finishTask();
    }
}
```
* execute the benchmark;
  * initialize the benchmark
  * start the benchmark
  * run TASKs
  * terminate the benchmark
  * print results

```
int main()
{
    initBenchmark();
    startBenchmark();
    for (int i=0; i<10; i++) CALL_TASK(task1);
    finishBenchmark();
    printCounters((void*) printf);
}
```

* compile and run;
  * calling makefile will produce `unittest_benchmark.exe`
  * running the executable should produce results similar to the following;

```
task id, task exec counter, clk sum, clk avg, clk var, clk min, clk max
0, 1, 0, 0, 0, 0, 0
1, 1, 0, 0, 0, 0, 0
2, 1, 906, 906, 0, 906, 906
3, execution counter equals 0
4, execution counter equals 0
5, execution counter equals 0
```

## Compiling for TriCore target

When compiling for a TriCore target, the following should hold;
* `UNITTEST_ENV` is not defined,
* either 1) `__GNUC__` is defined
  * `TCPATH` also needs to be defined, as it is in `HighTec IDE`
* or 2) `__TASKING__` is defined;
  *  `__SFRFILE__` and `__CPU__` must be defined as in `AURIX Developement Studio`

Define them in `BenchmarkCfg.h`.

## Compiling for Erika Enterprise

When compiling to use with Erika Enterprise OS, `ERIKA_OS` macro should be defined in `BenchmarkCfg.h`.
Currently, only HighTec GCC compiler has been tested, therefore please define `__GNUC__` and `TCPATH` as listed above.




## BenchmarkCfg.h
This file is used to set the constants of a benchmark execution.
Number of tasks has to be defined for perf.h and perf.c memory allocation.
The unit of memory per task (implemented as a C typedef struct, called task_counter), needed to perform a benchmark is dependant on the benchmark configuration.
The user can define 
* MEASURE_WAITING_TIME, which will log how much time does a task spend in waiting time (in ticks) (not yet implemented, can not be use in combination within others)
* MEASURE_CLK, which logs the specifics in units of clock ticks,
* MEASURE_INSTRUCTIONS, which logs the specifics in units of instructions,
* MEASURE_DATA/PROGRAM_CACHE_HITS/MISSES, which logs the specifics in units of data/program cache /hits//misses (not yet implemanted).


Each of the desired units to measure will report the following;
* execution count
* minimum execution time
* maximum execution time
* average execution time
* standard deviation of the execution time


## PerformanceCounter.h and TriCoreCounter.c or UnitTest/UnitTestCounter.c

The header file declares the structure for a hardware counter and declares the needed functions. The source files implement the functions, depending on the underlying hardware; compiling with makefile will use the `UnitTest/UnitTestCounter.c`, which implements a counter from `time.h` standard library, while compiling for TriCore target should use `TriCoreCounter.c`, which implements the TriCore Performance Counter. 


## TaskCounter.h and TaskCounter.c

The TaskCounter defines the structure to store and calculate the timing properties of a task.
The structure size depends on definitions in `BenchmarkCfh.h`;
Each of the desired measurements adds the following types to the `task_counter` struct;
* 8 bit unsigned integer to count the number of executions of the task in one benchmark run,
* 32 bit unsigned integer to log a counter for the currently executing execution of the task,
* 64 bit unsigned integer to log the sum of counter for all the executions of the task,
* 32 bit unsigned integer to log the variance of the counter from execution to execution,
* two 32 bit unsigned integers to log the minimum and maximum values of the counter.

## TaskStack.h and TaskStack.c

A simple stack structure is used to trace the task execution in the real-time OS context (Erika Enterprise).
Additionally, the file creates a TaskCounter list to store the needed structures. The size of the list is `NUMBER_OF_TASKS + 1`, where the zeroth task is the idle task.
Although not needed outside of OS, it is still used when `ERIKA_OS` is not defined.

## Benchmark.h, ErikaBenchmark.c and HighTecBecnhmark.c

The `Benchmark.h` header provides functions, used by the benchmark user.
The implementation depends on the context;
* the TASKSs can be executed within a real-time context, by the use od a real-time OS (like Erika Enterprise). When compiling with `ERIKA_OS` macro defined, the TASK is defines as is in Erika Enterprise. The user does not need to call the TASK explicitly.
* when TASKs are not executed within a real-time context, the user can explicitly call tasks as needed by using CALL_TASK, defined in `TaskDefinition.h` macro.

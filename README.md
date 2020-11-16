# Benchmark

The source files contain an implementation of the TriCore performance counter, which is able to number of count ticks, insturction and data/program cache hits and misses. 
The benchmark creates space for logging the counter for each task, specified by the user.
In `basic_test.c` a set of 5 tasks used to demonstrate the use of the benchmark.

## perf_config.h
This file is used to set the constants of a benhmark execution.
Number of tasks has to be defined for perf.h and perf.c memory allocation.
The unit of memory per task (implemented as a C typedef struct, called task_counter), needed to perform a benchmark is dependant on the benchmark configuration.
The user can define 
* MEASURE_WAITING_TIME, which will log how much time does a task spend in waiting time (not yet implemented)
* MEASURE_CLK, which logs the specifics in units of clock ticks,
* MEASURE_INSTRUCTIONS, which logs the specifics in units of instructions,
* MEASURE_DATA/PROGRAM_CACHE_HITS/MISSES, which logs the specifics in units of data/program cache /hits//misses (not yet implemanted),

* 8 bit unsigned integer to count the number of executions of the task in one benchmark run,
* 32 bit unsigned integer to log a counter for the currently executing execution of the task,
* 64 bit unsigned integer to log the sum of counter for all the executions of the task,
* 32 bit unsigned integer to log the variance of the counter from execution to execution,
* two 32 bit unsigned integers to log the minimum and maximum values of the counter.

## perf.c and perf.h
The files implement the performance counter and structures, and functions needed for logging the information.
The task priorities and resource allocation have to be known in order to track which task is currently executing on the CPU.
Each task must thus be wrapped by startTask(priority) and endTask() functions and each resource allocation must be wrapped by waitResource(resource_id) and takeResource(). 

(Note: resource allocation is not yet implemented intirely and simultanious task execution is not zet tested).

One extra unit of memory is allocated, to measure the time spent by none of the tasks (idle task). The reason is two-folded; a) avoiding the check for boundary conditions (no tasks on the stack), and b) measuring the time, not used by tasks.

## basic_test.c
The basic test initialises the benchmark and defines and calls 5 tasks, of which the execution time is measured by the benchmark. 
The basic test is used to test the benchmark in a simple, nonconcurrent environment. 
The basic test was run on TC264D B-Step;
* compiled with HighTec, executed on the CPU0 at speed 200MHz with the following results:

| task id | task exec counter | clk sum   | clk avg | clk var | clk min | clk max | instruction sum | instruction avg | instruction var | instruction min | instruction max |
|---------|-------------------|-----------|---------|---------|---------|---------|-----------------|-----------------|-----------------|-----------------|-----------------|
| TASK 0  | 1                 | 15924     | 15924   | 0       | 0       | 0       | 0               | 0               | 0               | 0               | 0               |
| TASK 1  | 100               | 440006000 | 4400060 | 0       | 4400060 | 4400060 | 2525639220      | 25256392        | 1555802062      | 2400302         | 477609212       |
| TASK 2  | 100               | 440005800 | 4400058 | 0       | 4400058 | 4400058 | 2765643020      | 27656430        | 1555802062      | 4800340         | 480009250       |
| TASK 3  | 100               | 440006000 | 4400060 | 0       | 4400060 | 4400060 | 4286614352      | 42866143        | 3363167544      | 482409318       | 720014466       |
| TASK 4  | 100               | 440006000 | 4400060 | 0       | 4400060 | 4400060 | 2517331976      | 25173319        | 3363167544      | 722414532       | 960019680       |
| TASK 5  | 100               | 440006000 | 4400060 | 0       | 4400060 | 4400060 | 748049600       | 7480496         | 3363167544      | 962419746       | 1200024894      |

* compiled with TASKING, executed on the CPU0 at speed of 200MHz with the following results:

| task id | task exec counter | clk sum  | clk avg | clk var  | clk min | clk max | instruction sum | instruction avg | instruction var | instruction min | instruction max |
|---------|-------------------|----------|---------|----------|---------|---------|-----------------|-----------------|-----------------|-----------------|-----------------|
| 0       | 1                 | 2432     | 2432    | 0        | 0       | 0       | 0               | 0               | 0               | 0               | 0               |
| 1       | 10                | 24005376 | 2400537 | 12748012 | 2400056 | 2404872 | 140025185       | 14002518        | 3747878941      | 1402244         | 26602793        |
| 2       | 10                | 24000560 | 2400056 | 0        | 2400056 | 2400056 | 154025465       | 15402546        | 3747878941      | 2802272         | 28002821        |
| 3       | 10                | 24000390 | 2400039 | 0        | 2400039 | 2400039 | 357029810       | 35702981        | 429459124       | 29402855        | 42003107        |
| 4       | 10                | 24000560 | 2400056 | 0        | 2400056 | 2400056 | 497032925       | 49703292        | 1444481269      | 43403144        | 56003441        |
| 5       | 10                | 24000560 | 2400056 | 0        | 2400056 | 2400056 | 637036275       | 63703627        | 1444481269      | 57403479        | 70003776        |
* compiled with TASKING, executed on the CPU1 at speed of 200MHz with the following results:

| task id | task exec counter | clk sum  | clk avg | clk var    | clk min | clk max | instruction sum | instruction avg | instruction var | instruction min | instruction max |
|---------|-------------------|----------|---------|------------|---------|---------|-----------------|-----------------|-----------------|-----------------|-----------------|
| 0       | 1                 | 1952     | 1952    | 0          | 0       | 0       | 0               | 0               | 0               | 0               | 0               |
| 1       | 10                | 14064701 | 1406470 | 2269453713 | 1400045 | 1464296 | 140002945       | 14000294        | 3747878941      | 1400020         | 26600569        |
| 2       | 10                | 14000680 | 1400068 | 28772      | 1400045 | 1400275 | 154003225       | 15400322        | 3747878941      | 2800048         | 28000597        |
| 3       | 10                | 14000340 | 1400034 | 0          | 1400034 | 1400034 | 357007570       | 35700757        | 429459124       | 29400631        | 42000883        |
| 4       | 10                | 14000450 | 1400045 | 0          | 1400045 | 1400045 | 497010685       | 49701068        | 1444481269      | 43400920        | 56001217        |
| 5       | 10                | 14000450 | 1400045 | 0          | 1400045 | 1400045 | 637014035       | 63701403        | 1444481269      | 57401255        | 70001552        |



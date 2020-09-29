# From TC2xx to TC3xx

Infineon offers two series of 32-bit AURIX Microcontrollers based on TriCore; TC2xx and TC3xx.
TC3xx series foremost upgrades the CPU and offers up to 6 core CPU, while TC2xx series reaches 3 cores.
Infineon offers, with both series, different RAM and Flash memory sizes, numbers of pins, numbers of CPUs and their processing speeds.
In addition to user manuals, [documentation and support](https://www.infineon.com/cms/en/product/microcontroller/32-bit-tricore-microcontroller/#collapse-3c47bc55-864c-11e7-89f3-40f2e90e8d04-2) of the architecture and Infenion Low-Level Drivers (iLLDs) is offered through so called ***Quick*** and ***Expert Trainings***.
The following changes are reported in those documents.

### System Architecture

TC3XX has shifted from ***scalar*** to ***superscalar*** Harvard architecture.
While TC2XX was offered with a combination of two different cores, namely TC 1.6E (Efficiency) and TC 1.6P (Performance), TC3XX is only offered with TC 1.6.2P cores.
TC 1.6E caches instruction only, while TC 1.6P and TC 1.6.2P cache both instruction and data.

| Properties        | TC2XX  | TC3XX  |
| ------------- |:-------------:| :-----:|
| cores     | up to 3 | up to 6 |
| flash      | up to 8MB      |   up to 16 MB |
| RAM | 2 MB |  6MB |
| clock speed | 133/200/300 MHz | 160/200/300 Mhz |
| CAN | MultiCAN+ | MCMCAN |
| Ethernet | 100 Mbit/s | 1000 Mbit/s |
| DMIPS/Mhz | 1.4 (E core) or 1.6 (P core) | 2.3 |
| number of pipeline stages | 4 (E core) or 6(P core) | 6 |
| ASCLIN channels | up to 4 | up to 6 |
| Delta-Sigma ADC | up to 20MHz | up to 40MHz |

### Clock Control Unit (CCU)

The clocking system was a part of System Control Unit (SCU).
The corresponding functions, used in TC2xx have kept the SCU prefix to serve backwards compatibility.

CCU still uses Phase Lock Loops (PLLs) for upscaling and Fractional Divider (FDR) to downscaling.
The clock can be used for external sources and provides periodical ***idle***, ***sleep*** and ***on*** states through Power Management System (PMS).

Note: Often, timers have to be additionally initialized and run in TC3xx.

Note: Clock Control Unit is not to be confused with Capture/Compare Unit 6 (CCU6).

### Memory Test Unit (MTU)

Memory Controller (MC), which provides access to RAM, is replaced by SRAM Support Hardware (SSH) (digital logic).
SSH offers the almost the same functionality as MC (MC offers more alarms).

### Central Processing Unit (CPU)

Jump from 1.6E (Efficiecy) and 1.6P (Performance) to 1.6.2P.
First 4 cores are are connected by System Resource Interconnect (SRI) Cross Bar Interconnect 0 (SRI0) and additional 2 CPUS can be connected by SRI Cross Bar Interconnect 1 (SRI1). The SRI0 and SRI1 are connected via a bridge. Performance is increased from 1.6 DIMPS/MHz (in 1.6P) to 2.3 DIMPS/MHz (in 1.6.2P).


### Flash Memory

Program Memory Unit (PMU) is replaced by DMU, PFI and FSI;

* Data Memory Unit (DMU) controls command sequences executed on the Program and Data Flash memories (PFLASH and DFLASH)
* Program Flash Interface (PFI) is added; it is used to connect CPU to Program Flash (PFLASH) point-to-point.
* Flash Standard Interface (FSI) is added to erase, program and verify operations on all flash memories.

Program Flash Banks (PFlash) and Data Flash Banks (DFlash) pages remain the sizes of 32 and 8 Bytes respectively.
DFLASH structure is improved to offer security features.

### Safety Management Unit (SMU)

Fault Signaling Protocol (FSP) can be configured to output 2 signals (while 00 represents faulty state), in addition to single pin output and single-bit timed protocol in TC2xx.


## Performance measurement metric

The performance of a given device is dependant of
1. the available resources (size of flash memories, processor speed, number of DMA channels...),
2. resource distribution (application specific (numbers of tasks per core, number of configured interrupts and DMA transfers) ...) and
3. additional running software (use of OS, iLLD).

The available resources are a constant for every TC board, while resource distribution is determined by the running application.
Use of an additional core can bring more available resource, but a core to core communication overhead can be introduced.
Additional software can bring certain advantages (i.e. abstraction level, safety and security...), but may introduce overhead.
Additional software can be compared by each other by comparing the respective overheads or the level of satisfaction of the desired added value.
For simplicity purposes, the additional software is not evaluated and the only additional software used are the iLLDs.

The goal of my metric is to best match a application to a board, which supports the needs of the application, with little resource overhead.
I.e., if one core wil suffice, one core should be used. 


### Execution time  and throughput
Both are often used metrics of performance.
Execution time evaluates the system by the time needed to execute a job J, while throughput measures how many jobs J can the system execute within a time frame.

Hypothesis 1: a board with more resources has shorter execution time
Hypothesis 2: a board with more resources has larger throughput

### Utilization (U)
Utilization is a unit often used in real-time systems and measures the utilization of CPU power based on a certain set of given tasks and their deadlines.
Utilization is a measure of time used vs. the time given and is thus measured in percents.

Hypothesis 3: more suitable board has a higher utilization (<=100%) for a given application A.
Hypothesis 4: a board with more resources has a lower utilization for a given application A.
Hypothesis 5: more resources can be added to support the application A (to achieve U <=100%).


### Number of ticks, instructions, and other events
Number of ticks (#t) per application is a good measurement when evaluating a CPU architecture, since it removes the speed of clock out of equation.
Together with number of instructions (#i) it can be used to evaluate the superscalar architecture features, announced in TC3XX.
TC2XX and TC3XX offer Performance Counters which can be used to count (pre)configured events (i.e. data cache misses/hits, program cache misses/hits...)

Hypothesis 6: superscalar architecture has a lower #t/#i index when compared to scalar architecture.
Hypothesis 7: number of instructions and number of ticks can vary for each measurement, depending on the then state of the system (due to interrupts, cache misses...).
Hypothesis 8: more memory resources results in less cache misses.

## Performance measurement load

The load can largely influence the measurement results in many ways, i.e:
* The application does little processing and its execution time is dependant mostly on the communication speed
    * Hypothesis: execution time is not dependant of many other resources and thus can not evaluate a board as a whole
* The application requires a lot of memory and causes many cache misses
    * Hypothesis :utilization is high but execution time is high and throughput is low
* The code is not optimized
    * Hypothesis: utilization is high but so are number of ticks and instructions
* The schedule is not optimized (bad distribution of resources)
    * Hypothesis: the utilization is high but execution time is high and throughput is low
* The application is not highly parallel
    * Hypothesis: utilization is low but number of ticks and instructions are also low

The load has to be considered while evaluation, that is all the metrics should be considered for evaluation score, while the load should highly resemble the work done by application A.
The mentioned cases thus have to be studied further.

## MAIN HYPOTHESIS:

For a certain application A, the best performance is offered by the board B which offers the least amount of resources that still support the application A and;
* execution time is low and throughput is high
* utilization is high,
* number of ticks and instructions are low.




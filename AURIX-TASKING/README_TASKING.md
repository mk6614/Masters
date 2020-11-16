# How to use with AURIX developement environment

This directory contains source files of two example projects, provided by AURIX IDE - BlinkyLed and ASCLIN.
The configuration of the LEDs and ASCLIN Tx is targeted at TC26x B-Step.
Place the `.c` and `.h` files of the benchmark in the project folder.
The file `Cpu0_Main.c` and `Cpu1_Main.c` contain the main functions for CPU0 and CPU1, which perform a basic test, defined in `basic_test.c`.
In order to corectly perform the test, only one test on one core may be executing at any time.
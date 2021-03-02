This page reports on possible warning and error messages during compile process.
Please refer to your own target hardware (unix(unittest)/HighTec/Erika)

# Warnings

## All architectures

* defined but not used;
  * 'task_list' defined but not used
  * 'task_stack' defined but not used

One shall ignore these warnings. The variables are used in runtime.

# Errors

## All Architectures

### undefined nacro errors:
  * TCPATH undefined or
  * Unknown compilers. Please define \_\_GNUC\_\_ or \_\_TASKING\_\_

Please determine your target hardware; the options are:
* unit test environment on a pc: define UNITTEST in 
* non OS environment an AURIX: define one of the following to decide on a compiler
  * \_\_GNUC\_\_ and TCPATH for Hightec GCC compiler
  * \_\_TASKING\_\_ and \_\_CPU\_\_ and \_\_SFRFILE\_\_
* OS environment: define ERIKA_OS and one of the non OS environments (decide on a compiler)

Define the selected environment macro in BenchmarkCfg.h.
You can obtain the right macro definitions from an example project in HighTec IDE or AURIX Development Studio accordingly.

## HighTec GCC Environment

### licence check failed error

Check if you have placed your licence file in the licence folder (default path is `C:\HighTec\licenses`).
If the licence is present, it might have expired.
The email for licence renewal is `tctcsupport@pls-mc.com`. The licence is bounded to your PC's MAC address.

## All Architectures

# Debugging

## HighTec GCC environment

### can't obtain a port in PuTTY

If you have Infineon DAS (Device Access Server) running, it may have overtaken the port. Close the DAS.

### cant print all numbers correctly

Compiling with iRAM configuration, the program can't allocate 64 bit integers. Change the _active_ configuration to iROM (HighTec: Preferences > C/C++ Build, 'Manage Configurations').

### cant print new lines correctly

You can change the definition of the NEW_LINE macro, defined in BenchmarkCfg.h.



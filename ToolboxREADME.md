# Minimal Toolbox for Benchmark Use

To build an example, the following tools are needed;
* [Free TriCore Entery Tool Chain](https://free-entry-toolchain.hightec-rt.com/) 
* [RT-Druid](http://www.erika-enterprise.com/) (Eclipse based GUI with java add-ons) version 3
* [UDE Starterkit](https://www.pls-mc.com/products/ude-starterkits/) or any other suitable debugging software

## Free TriCore Entery Tool Chain
The entry tool chain provides HighTec GCC compiler and an Eclipse based IDE.
Remember the install directory.

Compiling a HighTec Example project is recommended.

## RT-Druid and Erika Enterprise
Evidence offers an open source Real-Time Operating System (RTOS), suitable for hard-real time system implementation. The RTOS, namely Erika Enterprise, comes in 2 version (v2 and v3).
RT-Druid eases the implementation of a application by using OIL configuration language, specified by OSEK/VDX standard.
Further on, Erika Enterprise v3 is fully compliant with the OSEK standard, and almost fully nearly compliant with AUTOSAR OS standard.
With focus on the multi-core features within Erika Enterprise v3, the AURIX TriCore microcontrolers have been gaining more support.
To install RT-Druid, one can follow Erika's [Wiki Quick Start](http://www.erika-enterprise.com/wiki/index.php?title=Quick_start_guide).
To integrate Erika with TriCore AURIX, follow Erika's [Wiki Guide for AURIX](http://www.erika-enterprise.com/wiki/index.php?title=Infineon_Tricore_AURIX_build_with_RT-Druid).


Compiling an RT-Druid Example is recomended.  One must pay attention to not declare non-existent CPU units and set `MCU_DATA` in the `.oil` according to the microcontroller version.
I used AURIX TriBorad 264, B-Step, dual core; the corresponding `MCU_DATA` must be set to `26X` and no more that 2 CPU objects are defined.

## Debugging Software
While Erika recommends the use of [Lauterbatch Trace 32](https://www.lauterbach.com/frames.html?home.html), the (above linked) free UDE version can be used.
The version provides all Tricore configurations.
A `.elf` file, generated by RT-Druid (or any other source), can be uploaded to a connected target. 




# Examples

Both examples were exported from Eclipse based IDE as zipped projects.
ErikaExample was produced by Evidence's RT-Druid and HighTecExample by HighTec IDE.
Both examples were built for AURIX TC26x B-Step.


# Replicate example for a different AURIX TriCore

In ErikaExample, in `conf.oil` replace `MCU_DATA` with your AURIX MCU (derivative is only use by Laterbach's TRACE32 debugger).
You might also want to change the `led.h` and `uart_poll_init.c` files to match your pin layout.
These files can also be obtained from HighTec IDE by opening an Example for your desired MCU.
Do not forget to keep the benchmark source files in the `APP_SRC` of `conf.oil`

In HighTec you can open a new Example for your target MCU and add the header Benchmark files to the `h` folder and source Benchmark files to the `src` folder. You can dismiss the `ErikaBenchmark.c` file.
Include "Benchmark.h" and "TaskDefinition.h" wherever you need to use the Benchmark functionality.
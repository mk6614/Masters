CC = gcc
CFLAGS = -g -Wall

#ENV="-DUNITTEST_ENV" 

TRICORE_PATH="/cygdrive/c/HighTec/toolchains/tricore/v4.9.3.0-infineon-1.0/tricore/include/"

default: unittest clean

ENV = -DUNITTEST_ENV

	

ht_benchmark.o:	HighTecBenchmark.c Benchmark.h BenchmarkCfg.h
	gcc $(CFLAGS) $(ENV) -o Benchmark.o -c HighTecBenchmark.c

ee_benchmark:	EikaBenchmark.c Benchmark.h BenchmarkCfg.h
	gcc $(CFLAGS) $(ENV) -o Benchmark.o HighTecBenchmark.c

tc_perf_counter.o: TriCoreCounter.c PerformanceCounter.h BenchmarkCfg.h
	gcc $(CFLAGS) $(ENV) -o PerformanceCounter.o -c TriCoreCounter.c

unittest_perf_counter.o: UnitTests/UnitTestCounter.c PerformanceCounter.h BenchmarkCfg.h
	gcc $(CFLAGS) $(ENV) -o PerformanceCounter.o -c UnitTests/UnitTestCounter.c

task_counter.o: TaskCounter.c TaskCounter.h BenchmarkCfg.h
	gcc $(CFLAGS) $(ENV) -o TaskCounter.o -c TaskCounter.c

task_stack.o: TaskStack.c TaskStack.h BenchmarkCfg.h
	gcc $(CFLAGS) $(ENV) -o TaskStack.o -c TaskStack.c


unittest: ht_benchmark.o unittest_perf_counter.o task_counter.o task_stack.o BenchmarkCfg.h
	gcc $(CFLAGS) $(ENV) -o unittest_benchmark ./UnitTests/UnitTestMain.c Benchmark.o PerformanceCounter.o TaskCounter.o TaskStack.o

clean: 
	rm *.o
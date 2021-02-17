CC = gcc
CFLAGS = -g -Wall

default: unittest clean

unittest_perf_counter.o: UnitTests/UnitTestCounter.c PerformanceCounter.h
	gcc $(CFLAGS) -DUNITTEST_ENV -c UnitTests/UnitTestCounter.c

unittest_benchmark.o:	HighTecBenchmark.c Benchmark.h
	gcc $(CFLAGS) -DUNITTEST_ENV -c HighTecBenchmark.c

benchmark:	HighTecBenchmark.c Benchmark.h
	gcc $(CFLAGS) -DUNITTEST_ENV -c HighTecBenchmark.c

perf_counter.o: TriCoreCounter.c PerformanceCounter.h
	gcc $(CFLAGS) -DUNITTEST_ENV -c TriCoreCounter.c

task_counter.o: TaskCounter.c TaskCounter.h
	gcc $(CFLAGS) -DUNITTEST_ENV -c TaskCounter.c

task_stack.o: TaskStack.c TaskStack.h
	gcc $(CFLAGS) -DUNITTEST_ENV -c TaskStack.c


unittest: unittest_benchmark.o unittest_perf_counter.o task_counter.o task_stack.o
	gcc $(CFLAGS) -DUNITTEST_ENV -o unittest_benchmark ./UnitTests/UnitTestMain.c HighTecBenchmark.o UnitTestCounter.o TaskCounter.o TaskStack.o

clean: 
	rm *.o
#include <benchmark/benchmark.h>
#include <functional>


template <typename F>
void test1(F&& f) {
    f(1, 2, 3);
}

void test2(const std::function<void(int, int, int)>& f) {
    f(1, 2, 3);
}

void test3(std::function<void(int, int, int)> f) {
    f(1, 2, 3);
}

static void BM_Test1(benchmark::State& state) {
    for (auto _ : state)
        test1([](...){ });
}
BENCHMARK(BM_Test1);

static void BM_Test2(benchmark::State& state) {
    for (auto _ : state)
        test2([](...){ });
}
BENCHMARK(BM_Test2);

static void BM_Test3(benchmark::State& state) {
    for (auto _ : state)
        test3([](...){ });
}
BENCHMARK(BM_Test3);

BENCHMARK_MAIN();
/*
2019-12-26 01:20:43
Running ./main
Run on (16 X 3593.35 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x8)
  L1 Instruction 64 KiB (x8)
  L2 Unified 512 KiB (x8)
  L3 Unified 8192 KiB (x2)
Load Average: 0.09, 0.14, 0.20
***WARNING*** Library was built as DEBUG. Timings may be affected.
-----------------------------------------------------
Benchmark           Time             CPU   Iterations
-----------------------------------------------------
BM_Test1         4.73 ns         4.73 ns    149127722
BM_Test2         59.4 ns         59.4 ns     11894603
BM_Test3         58.0 ns         58.0 ns     11661738
*/

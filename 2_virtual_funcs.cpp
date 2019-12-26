#include <benchmark/benchmark.h>

struct Base {
    virtual void test() const = 0;
};

struct A : Base {
    void test() const override { }
};

struct C {
    void test() const { }
};

template <typename T>
void test(const T& t) {
    t.test();
}

static void BM_Test1(benchmark::State& state) {
    A a;
    for (auto _ : state)
        test(static_cast<const Base&>(a));
}
BENCHMARK(BM_Test1);

static void BM_Test2(benchmark::State& state) {
    C c;
    for (auto _ : state)
        test(c);
}
BENCHMARK(BM_Test2);

BENCHMARK_MAIN();

/*
Running ./main
Run on (16 X 3593.35 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x8)
  L1 Instruction 64 KiB (x8)
  L2 Unified 512 KiB (x8)
  L3 Unified 8192 KiB (x2)
Load Average: 0.26, 0.28, 0.27
***WARNING*** Library was built as DEBUG. Timings may be affected.
-----------------------------------------------------
Benchmark           Time             CPU   Iterations
-----------------------------------------------------
BM_Test1         5.12 ns         5.12 ns    135601465
BM_Test2         4.84 ns         4.84 ns    144260901
*/


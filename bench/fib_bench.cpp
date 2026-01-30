#include <benchmark/benchmark.h>
#include "../src/fib.h"
#include <cstdint>

static void BM_Fib(benchmark::State& state) {
    uint64_t x = 40;        // will vary slightly
    uint64_t acc = 0;

    for (auto _ : state) {
        // make input depend on previous work so compiler can't precompute
        x = (x * 1664525u + 1013904223u) % 50;   // cheap LCG, x in [0,49]
        benchmark::DoNotOptimize(x);

        for (int i = 0; i < 1000; ++i) {
            acc += fib(x);
        }
        benchmark::DoNotOptimize(acc);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_Fib);
static void BM_Empty(benchmark::State& state) {
    uint64_t acc = 0;
    for (auto _ : state) {
        for (int i = 0; i < 1000; ++i) {
            benchmark::DoNotOptimize(i);
            acc += (uint64_t)i;
        }
        benchmark::DoNotOptimize(acc);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_Empty);

BENCHMARK_MAIN();

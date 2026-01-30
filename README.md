# hello-perf

A minimal C++ **performance playground** I use to build a reliable
**build → test → benchmark** workflow before doing any real systems or
low-latency work.

This repo is intentionally small. The goal is not features, it’s
**correctness + measurement discipline**.

---

## What’s in this repo

```
hello-perf/
├── CMakeLists.txt
├── src/        # implementation (e.g. fib)
├── tests/      # GoogleTest unit tests
├── bench/      # Google Benchmark microbenchmarks
└── build/      # out-of-tree build artifacts
```

- **Tests** protect correctness
- **Benchmarks** protect honesty
- **CMake** locks the build configuration so results are reproducible

---

## Prerequisites

- macOS (Apple Silicon tested)
- Apple Clang (default `/usr/bin/clang++`)
- CMake ≥ 3.28
- Ninja
- GoogleTest
- Google Benchmark
- Xcode Command Line Tools

---

## Build, test, and benchmark

### 1. Configure (Release mode)

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
```

This step:
    - selects the compiler
    - locks optimization flags
    - generates Ninja build files

### 2. Build 

```bash
cmake --build build
```

### 3. Run unit tests

```bash
ctest --test-dir build --output-on-failure
```
If test fail, stop. Benchmark number are meaningless without correctness.

### 4. Run benchmarks

```bash
./build/fib_bench --benchmark_min_time=2s
```
    - `--benchmark_min_time=2s` ensures stable measurements
	-	use `1s` for quick iteration, `2s` for numbers you actually compare

### Expected Output
You should see:
- Tests passing
- Benchmark times in microseconds or nanoseconds

Example:
```
-----------------------------------------------------
Benchmark           Time             CPU   Iterations
-----------------------------------------------------
BM_Fib          15114 ns        14820 ns        47627
BM_Empty         2565 ns         2559 ns       251187
```

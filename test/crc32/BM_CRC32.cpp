#include <benchmark/benchmark.h>
#include "crc32.h"
#include <stdlib.h>
#include <string>

#define CRC32_USE32
#define CRC32_USE64
#define CRC32_USE128
#define CRC32_USE256
#define CRC32_USE512
#define CRC32_USE_SSE4_2

static void BM_CRC32(benchmark::State& state) {
  char* input = new char[state.range(0)];
  for (auto _ : state)
    crc32((uint8_t*) input, state.range(0));
  state.SetBytesProcessed(int64_t(state.iterations()) *
                          int64_t(state.range(0)));
  delete[] input;
}


static void BM_CRC32_32(benchmark::State& state) {
  char* input = new char[state.range(0)];
  for (auto _ : state)
    crc32_32((uint8_t*) input, state.range(0));
  state.SetBytesProcessed(int64_t(state.iterations()) *
                          int64_t(state.range(0)));
  delete[] input;
}

static void BM_CRC32_64(benchmark::State& state) {
  char* input = new char[state.range(0)];
  for (auto _ : state)
    crc32_64((uint8_t*) input, state.range(0));
  state.SetBytesProcessed(int64_t(state.iterations()) *
                          int64_t(state.range(0)));
  delete[] input;
}

static void BM_CRC32_128(benchmark::State& state) {
  char* input = new char[state.range(0)];
  for (auto _ : state)
    crc32_128((uint8_t*) input, state.range(0));
  state.SetBytesProcessed(int64_t(state.iterations()) *
                          int64_t(state.range(0)));
  delete[] input;
}

static void BM_CRC32_128_(benchmark::State& state) {
  char* input = new char[state.range(0)];
  for (auto _ : state)
    crc32_128_((uint8_t*) input, state.range(0));
  state.SetBytesProcessed(int64_t(state.iterations()) *
                          int64_t(state.range(0)));
  delete[] input;
}


#if defined(CRC32_USE_SSE4_2)
static void BM_CRC32_SSE_8(benchmark::State& state) {
  char* input = new char[state.range(0)];
  for (auto _ : state)
    crc32_sse_8((uint8_t*) input, state.range(0));
  state.SetBytesProcessed(int64_t(state.iterations()) *
                          int64_t(state.range(0)));
  delete[] input;
}

static void BM_CRC32_SSE_16(benchmark::State& state) {
  char* input = new char[state.range(0)];
  for (auto _ : state)
    crc32_sse_16((uint8_t*) input, state.range(0));
  state.SetBytesProcessed(int64_t(state.iterations()) *
                          int64_t(state.range(0)));
  delete[] input;
}

static void BM_CRC32_SSE_32(benchmark::State& state) {
  char* input = new char[state.range(0)];
  for (auto _ : state)
    crc32_sse_32((uint8_t*) input, state.range(0));
  state.SetBytesProcessed(int64_t(state.iterations()) *
                          int64_t(state.range(0)));
  delete[] input;
}

#endif
BENCHMARK(BM_CRC32)->Arg(8)->Arg(64)->Arg(512)->Arg(4<<10)->Arg(8<<10)->Arg(16<<10)->Arg(32<<10)->Arg(64<<10);
BENCHMARK(BM_CRC32_32)->Arg(8)->Arg(64)->Arg(512)->Arg(4<<10)->Arg(8<<10)->Arg(16<<10)->Arg(32<<10)->Arg(64<<10);
BENCHMARK(BM_CRC32_64)->Arg(8)->Arg(64)->Arg(512)->Arg(4<<10)->Arg(8<<10)->Arg(16<<10)->Arg(32<<10)->Arg(64<<10);
BENCHMARK(BM_CRC32_128)->Arg(8)->Arg(64)->Arg(512)->Arg(4<<10)->Arg(8<<10)->Arg(16<<10)->Arg(32<<10)->Arg(64<<10);
BENCHMARK(BM_CRC32_128_)->Arg(8)->Arg(64)->Arg(512)->Arg(4<<10)->Arg(8<<10)->Arg(16<<10)->Arg(32<<10)->Arg(64<<10);

#if defined(CRC32_USE_SSE4_2)
BENCHMARK(BM_CRC32_SSE_8)->Arg(8)->Arg(64)->Arg(512)->Arg(4<<10)->Arg(8<<10)->Arg(16<<10)->Arg(32<<10)->Arg(64<<10);
BENCHMARK(BM_CRC32_SSE_16)->Arg(8)->Arg(64)->Arg(512)->Arg(4<<10)->Arg(8<<10)->Arg(16<<10)->Arg(32<<10)->Arg(64<<10);
BENCHMARK(BM_CRC32_SSE_32)->Arg(8)->Arg(64)->Arg(512)->Arg(4<<10)->Arg(8<<10)->Arg(16<<10)->Arg(32<<10)->Arg(64<<10);
#endif

BENCHMARK_MAIN();
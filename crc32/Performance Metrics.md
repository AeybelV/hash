# Performance Metrics

The performance metrics listed are when compiled with -O3 on various microarchitectures.

- [Performance Metrics](#performance-metrics)
  - [x86\_64](#x86_64)
    - [Intel](#intel)
      - [Intel Raptor Lake](#intel-raptor-lake)
    - [AMD](#amd)
      - [Zen 3](#zen-3)

## x86_64

### Intel

#### Intel Raptor Lake

Intel i9-13900H @ 5.2 GHz

| **Function**  | **Throughput**  |
|:------------: |:--------------: |
|  crc32        | 6.981 MB/s      |
|  crc32_32     | 1.880 GB/s      |
|  crc32_64     | 2.749 GB/s      |
|  crc32_128    | 5.383 GB/s      |
|  crc32_128_   | 6.992 GB/s      |
|  crc32_sse_8  | 1.745 GB/s      |
|  crc32_sse_16 | 3.520 GB/s      |
|  crc32_sse_32 | 7.177 GB/s      |

### AMD

#### Zen 3

AMD 5600X @ 4.2GHz

| **Function**  | **Throughput**  |
|:------------: |:--------------: |
|  crc32        | 5.342 MB/s      |
|  crc32_32     | 1.594 GB/s      |
|  crc32_64     | 2.281 GB/s      |
|  crc32_128    | 4.406 GB/s      |
|  crc32_128_   | 5.181 GB/s      |
|  crc32_sse_8  | 1.403 GB/s      |
|  crc32_sse_16 | 2.826 GB/s      |
|  crc32_sse_32 | 5.772 GB/s      |

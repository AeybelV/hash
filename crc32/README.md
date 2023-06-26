# CRC32

Varius implementations of cyclic reduancy check (CRC) which can be used for error detecting. As CRC produces a check value of a fixed length, it can also be used as a hash function. Cross refetence the [Performance Metrics](Performance%20Metrics.md) for performance measurements.

- [CRC32](#crc32)
  - [Memoized Implementation](#memoized-implementation)
  - [Hardware Accelerated Methods](#hardware-accelerated-methods)
    - [x86 SSE4.2](#x86-sse42)

## Memoized Implementation

These are implementations of the algorithm that utilize lookup tables for performance. Uses polynomial `0xEDB88320`.

- `uint32_t crc32(const uint8_t* input, size_t length)`
  - Simple memoized approach using Sarwate algorithm, processes the input a byte at a time. Utilizes a 256 entry lookup table of uint32_t (1KiB)

- `uint32_t crc32_32(const uint8_t* input, size_t length)`
  - Sarwate algorithm, processes the input 32 bits (4 bytes) at a time. Utilizes a 4 KiB lookup table. Must define **CRC32_USE32** macro to use.

- `uint32_t crc32_64(const uint8_t* input, size_t length)`
  - Sarwate algorithm, processes the input 64 bits (8 bytes) at a time. Utilizes a 8 KiB lookup table. Must define **CRC32_USE64** macro to use.

- `uint32_t crc32_128(const uint8_t* input, size_t length)`
  - Sarwate algorithm, processes the input 128 bits (16 bytes) at a time. Utilizes a 16 KiB lookup table. Must define **CRC32_USE128** macro to use.

- `uint32_t crc32_128_(const uint8_t* input, size_t length)`
  - Loop unrolled version that processes the input a 128 bits (16 bytes) at a time. Utilizes a 16 KiB lookup table. Due to being unrolled, the function is faster than the normal version at the cost of more space for the function. Must define **CRC32_USE128** macro to use.

## Hardware Accelerated Methods

Implementations that utilize hardware instructions to perform CRC.

### x86 SSE4.2

x86 Processors with the SSE4.2 instructions sets can utilize the CRC32 instruction to hardware accelerated CRC calculation. The instruction uses the **Castagnoli Polynomial** `0x1EDC6F41` to implement CRC-32C. Using these functions are significantly faster than the memoized approach and do not use extra memory for lookup tables. The **CRC32_USE_SSE4_2** macro must be defined to use these functions

These functions are reccomended over the memoized approach if targetting x86 and you know the processor has SSE4.2; however most x86 processors since 2007 have it so these methods are highly reccomended.

- `uint32_t crc32_sse_8(const uint8_t* input, size_t length)`
  - Utilizes the crc32 instruction to accumulate a crc-32c value. Processes the message a byte at a time.

- `uint32_t crc32_sse_16(const uint8_t* input, size_t length)`
  - Utilizes the crc32 instruction to accumulate a crc-32c value. Processes the message 16 bits (2 bytes) at a time. Input size does not need to be a multiple of 2 bytes.
  
- `uint32_t crc32_sse_32(const uint8_t* input, size_t length)`
  - Utilizes the crc32 instruction to accumulate a crc-32c value. Processes the message 32 bits (4 bytes) at a time. Input size does not need to be a multiple of 4 bytes.
  
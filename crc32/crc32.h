/**
 * @file crc32.h
 * @author Aeybel Varghese (aeybelvarghese@gmail.com)
 * @brief Fast implementations of CRC32
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _CRC32_H
#define _CRC32_H

#include <stdint.h>
#include "crc32_lut.h"

#ifdef _MSC_VER
  #include <xmmintrin.h>
  #define PREFETCH(location) _mm_prefetch(location, _MM_HINT_T0)
#else
  #ifdef __GNUC__
    #define PREFETCH(location) __builtin_prefetch(location)
  #else
    #define PREFETCH(location) ;
  #endif
#endif

/**
 * @brief Simple CRC32 implementation using Sarwate Algorithm, utilizes a 256 entry lookup table of uint32_t (1KiB)
 * 
 * @param input Input message
 * @param length Length of the message
 * @return uint32_t CRC Result
 */
uint32_t crc32(const uint8_t* input, size_t length);

/**
 * @brief CRC32 implementation that processes the input message 4 bytes at a time. Utilizes a 4 KiB lookup table
 * 
 * @param input Input message
 * @param length Length of the message
 * @return uint32_t CRC Result
 */
uint32_t crc32_32(const uint8_t* input, size_t length);

/**
 * @brief CRC32 implementation that processes the input message 8 bytes at a time. Utilizes a 8 KiB lookup table
 * 
 * @param input Input message
 * @param length Length of the message
 * @return uint32_t CRC Result
 */
uint32_t crc32_64(const uint8_t* input, size_t length);

/**
 * @brief CRC32 implementation that processes the input message 16 bytes at a time. Utilizes a 16 KiB lookup table
 *
 * @param input Input message
 * @param length Length of the message
 * @return uint32_t CRC Result
 */
uint32_t crc32_128(const uint8_t* input, size_t length);

/**
 * @brief Loop unrolled CRC32 implementation that processes the input message 16 bytes at a time. Utilizes a 16 KiB lookup table. There is a slight possibility of slight performance gains using data prefetching by defining CRC32_ENABLE_PREFETCH, otherwise there might be slight throughput cut. The compiler should always optimize this at O3.
 *
 * @param input Input message
 * @param length Length of the message
 * @return uint32_t CRC Result
 */
uint32_t crc32_128_(const uint8_t* input, size_t length);

#if defined(CRC32_USE_SSE4_2)
/**
 * @brief CRC32 implementation using x86 CRC32 instruction in SSE4.2, CRC32_USE_SSE4_2 macro must be defined
 * 
 * @param input Input message
 * @param length Length of the message
 * @return uint32_t CRC Result
 */
uint32_t crc32_sse_8(const uint8_t* input, size_t length);

/**
 * @brief CRC32 implementation using x86 CRC32 instruction in SSE4.2, CRC32_USE_SSE4_2 macro must be defined
 * 
 * @param input Input message
 * @param length Length of the message
 * @return uint32_t CRC Result
 */
uint32_t crc32_sse_16(const uint8_t* input, size_t length);

/**
 * @brief CRC32 implementation using x86 CRC32 instruction in SSE4.2, CRC32_USE_SSE4_2 macro must be defined
 * 
 * @param input Input message
 * @param length Length of the message
 * @return uint32_t CRC Result
 */
uint32_t crc32_sse_32(const uint8_t* input, size_t length);

/**
 * @brief CRC32 implementation using x86 CRC32 instruction in SSE4.2, CRC32_USE_SSE4_2 macro must be defined
 * 
 * @param input Input message
 * @param length Length of the message
 * @return uint32_t CRC Result
 */
uint32_t crc32_sse_64(const uint8_t* input, size_t length);

#endif

#endif
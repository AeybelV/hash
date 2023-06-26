/**
 * @file crc32.c
 * @author Aeybel Varghese (aeybelvarghese@gmail.com)
 * @brief Fast implementations of CRC32
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdint.h>
#include <stdlib.h>
#include "crc32.h"

#if defined(CRC32_USE_SSE4_2)
#include <nmmintrin.h>
#endif

uint32_t crc32(const uint8_t* input, size_t length){
    
    uint32_t crc = 0xFFFFFFFFu;
    while(length--){
        crc = lookup[0][*input++ ^ (crc & 0xFF)] ^ (crc>>8);
    }

    return ~crc;

}

uint32_t crc32_32(const uint8_t* input, size_t length){

    uint32_t crc = 0xFFFFFFFFu;

    // 4 bytes at a time
    const uint32_t *ptr32 = (const uint32_t*) input;
    while(length >= 4){
        const uint32_t word1 = *ptr32++ ^ crc;
        crc =   lookup[0][(word1 >> 24  & 0xFF)] ^
                lookup[1][(word1 >> 16  & 0xFF)] ^
                lookup[2][(word1 >> 8   & 0xFF)] ^
                lookup[3][(word1        & 0xFF)];
        length -= 4;
    }

    // Remaining bytes < 4 in the input
    const uint8_t* remaining = (const uint8_t*) ptr32;
    while(length--){
        crc = lookup[0][*remaining++ ^ (crc & 0xFF)] ^ (crc>>8);
    }


    return ~crc;

}

uint32_t crc32_64(const uint8_t* input, size_t length){
    uint32_t crc = 0xFFFFFFFFu;

    // 8 bytes at a time
    const uint64_t *ptr64 = (const uint64_t*) input;
    while(length >= 8){
        const uint64_t word1 = *ptr64++ ^ crc;
        crc =   
                lookup[0][(uint32_t)(word1  >>56)   & 0xFF] ^
                lookup[1][(uint32_t)(word1  >>48)   & 0xFF] ^
                lookup[2][(uint32_t)(word1  >>40)   & 0xFF] ^
                lookup[3][(uint32_t)(word1  >>32)   & 0xFF] ^
                lookup[4][(uint32_t)(word1  >>24)   & 0xFF] ^
                lookup[5][(uint32_t)(word1  >>16)   & 0xFF] ^
                lookup[6][(uint32_t)(word1  >> 8)   & 0xFF] ^
                lookup[7][(uint32_t)(word1      )   & 0xFF];
        length -= 8;
    }

    // 4 bytes at a time
    const uint32_t *ptr32 = (const uint32_t*) ptr64;
    while(length >= 4){
        const uint32_t word1 = *ptr32++ ^ crc;
        crc =   lookup[0][(word1 >> 24  & 0xFF)] ^
                lookup[1][(word1 >> 16  & 0xFF)] ^
                lookup[2][(word1 >> 8   & 0xFF)] ^
                lookup[3][(word1        & 0xFF)];
        length -= 4;
    }

    // Remaining bytes < 4 in the input
    const uint8_t* remaining = (const uint8_t*) ptr32;
    while(length--){
        crc = lookup[0][*remaining++ ^ (crc & 0xFF)] ^ (crc>>8);
    }
    return ~crc;

}


uint32_t crc32_128(const uint8_t* input, size_t length){

    uint32_t crc = 0xFFFFFFFFu;

    // 16 bytes at a time
    // A 1Gb/s of throughput is achieved here by using 4 32-bit words instead of 64 bit
    const uint32_t *ptr128 = (const uint32_t*) input;
    while(length >= 16){
        const uint32_t word1   = *ptr128++ ^ crc;
        const uint32_t word2   = *ptr128++;
        const uint32_t word3 = *ptr128++;
        const uint32_t word4  = *ptr128++;
        crc  =      lookup[ 0][(word4   >> 24) & 0xFF] ^
                    lookup[ 1][(word4   >> 16) & 0xFF] ^
                    lookup[ 2][(word4   >>  8) & 0xFF] ^
                    lookup[ 3][(word4        )  & 0xFF] ^
                    lookup[ 4][(word3   >> 24) & 0xFF] ^
                    lookup[ 5][(word3   >> 16) & 0xFF] ^
                    lookup[ 6][(word3   >>  8) & 0xFF] ^
                    lookup[ 7][(word3        ) & 0xFF] ^
                    lookup[ 8][(word2   >> 24) & 0xFF] ^
                    lookup[ 9][(word2   >> 16) & 0xFF] ^
                    lookup[10][(word2   >>  8) & 0xFF] ^
                    lookup[11][(word2        ) & 0xFF] ^
                    lookup[12][(word1   >> 24) & 0xFF] ^
                    lookup[13][(word1   >> 16) & 0xFF] ^
                    lookup[14][(word1   >>  8) & 0xFF] ^
                    lookup[15][(word1        )  & 0xFF];
        length -= 16;
               
    }

    // 8 bytes at a time
    const uint64_t *ptr64 = (const uint64_t*) ptr128;
    while(length >= 8){
        const uint64_t current = *ptr64++ ^ crc;
        crc =   
                lookup[0][(uint32_t)(current  >>56)   & 0xFF] ^
                lookup[1][(uint32_t)(current  >>48)   & 0xFF] ^
                lookup[2][(uint32_t)(current  >>40)   & 0xFF] ^
                lookup[3][(uint32_t)(current  >>32)   & 0xFF] ^
                lookup[4][(uint32_t)(current  >>24)   & 0xFF] ^
                lookup[5][(uint32_t)(current  >>16)   & 0xFF] ^
                lookup[6][(uint32_t)(current  >> 8)   & 0xFF] ^
                lookup[7][(uint32_t)(current      )   & 0xFF];
        length -= 8;
    }

    // 4 bytes at a time
    const uint32_t *ptr32 = (const uint32_t*) ptr64;
    while(length >= 4){
        const uint32_t word1 = *ptr32++ ^ crc;
        crc =   lookup[0][(word1 >> 24  & 0xFF)] ^
                lookup[1][(word1 >> 16  & 0xFF)] ^
                lookup[2][(word1 >> 8   & 0xFF)] ^
                lookup[3][(word1        & 0xFF)];
        length -= 4;
    }

    // Remaining bytes < 4 in the input
    const uint8_t* remaining = (const uint8_t*) ptr32;
    while(length--){
        crc = lookup[0][*remaining++ ^ (crc & 0xFF)] ^ (crc>>8);
    }
    return ~crc;

}

// Defines how muuch to unroll the loop by.
const size_t CRC32_128_UNROLL_CNT = 4;
const size_t CRC32_128_UNROLL_BYTES = 16 * CRC32_128_UNROLL_CNT;

__attribute__((optimize("O3", "unroll-loops"))) uint32_t crc32_128_(const uint8_t* input, size_t length)
{

    uint32_t crc = 0xFFFFFFFFu;

    // Processed 16 bytes at a time
    // Performance with 4 32-bit words is better than with 2 64-bit or 1 128-bit word, we gain 1GB of throughput by doing so.
    const uint32_t* ptr128 = (const uint32_t*) input;
    while (length >= CRC32_128_UNROLL_BYTES + 256){
        #ifdef CRC32_ENABLE_PREFETCH
        PREFETCH(((const char*) ptr128) + 256);
        #endif
        for (size_t unrolling = 0; unrolling < CRC32_128_UNROLL_CNT; unrolling++){
        const uint32_t word1   = *ptr128++ ^ crc;
        const uint32_t word2   = *ptr128++;
        const uint32_t word3 = *ptr128++;
        const uint32_t word4  = *ptr128++;
        crc  =      lookup[ 0][(word4   >> 24) & 0xFF] ^
                    lookup[ 1][(word4   >> 16) & 0xFF] ^
                    lookup[ 2][(word4   >>  8) & 0xFF] ^
                    lookup[ 3][(word4        )  & 0xFF] ^
                    lookup[ 4][(word3   >> 24) & 0xFF] ^
                    lookup[ 5][(word3   >> 16) & 0xFF] ^
                    lookup[ 6][(word3   >>  8) & 0xFF] ^
                    lookup[ 7][(word3        ) & 0xFF] ^
                    lookup[ 8][(word2   >> 24) & 0xFF] ^
                    lookup[ 9][(word2   >> 16) & 0xFF] ^
                    lookup[10][(word2   >>  8) & 0xFF] ^
                    lookup[11][(word2        ) & 0xFF] ^
                    lookup[12][(word1   >> 24) & 0xFF] ^
                    lookup[13][(word1   >> 16) & 0xFF] ^
                    lookup[14][(word1   >>  8) & 0xFF] ^
                    lookup[15][(word1        )  & 0xFF];
        }
        length -= CRC32_128_UNROLL_BYTES;
    }

    // 8 bytes at a time
    const uint64_t *ptr64 = (const uint64_t*) ptr128;
    while(length >= 8){
        const uint64_t current = *ptr64++ ^ crc;
        crc =   
                lookup[0][(uint32_t)(current  >>56)   & 0xFF] ^
                lookup[1][(uint32_t)(current  >>48)   & 0xFF] ^
                lookup[2][(uint32_t)(current  >>40)   & 0xFF] ^
                lookup[3][(uint32_t)(current  >>32)   & 0xFF] ^
                lookup[4][(uint32_t)(current  >>24)   & 0xFF] ^
                lookup[5][(uint32_t)(current  >>16)   & 0xFF] ^
                lookup[6][(uint32_t)(current  >> 8)   & 0xFF] ^
                lookup[7][(uint32_t)(current      )   & 0xFF];
        length -= 8;
    }

    // 4 bytes at a time
    const uint32_t *ptr32 = (const uint32_t*) ptr64;
    while(length >= 4){
        const uint32_t word1 = *ptr32++ ^ crc;
        crc =   lookup[0][(word1 >> 24  & 0xFF)] ^
                lookup[1][(word1 >> 16  & 0xFF)] ^
                lookup[2][(word1 >> 8   & 0xFF)] ^
                lookup[3][(word1        & 0xFF)];
        length -= 4;
    }

    // Remaining bytes < 4 in the input
    const uint8_t* remaining = (const uint8_t*) ptr32;
    while(length--){
        crc = lookup[0][*remaining++ ^ (crc & 0xFF)] ^ (crc>>8);
    }
    return ~crc;

}

#if defined(CRC32_USE_SSE4_2)
__attribute__((optimize("O3", "unroll-loops"))) uint32_t crc32_sse_8(const uint8_t* input, size_t length){
    
    uint32_t crc = 0xFFFFFFFFu;
    while(length--){
        crc = _mm_crc32_u8(crc, *input++);
    }

    return ~crc;

}

__attribute__((optimize("O3", "unroll-loops"))) uint32_t crc32_sse_16(const uint8_t* input, size_t length){
    
    uint32_t crc = 0xFFFFFFFFu;
    const uint16_t* ptr16 = (const uint16_t*) input;

    while(length >= 2){
        crc = _mm_crc32_u16(crc, *ptr16++);
        length -=2;
    }

    const uint16_t* ptr8 = (const uint16_t*) ptr16;
    while(length--){
        crc = _mm_crc32_u8(crc, *ptr8++);
    }

    return ~crc;

}

__attribute__((optimize("O3", "unroll-loops"))) uint32_t crc32_sse_32(const uint8_t* input, size_t length){
    
    uint32_t crc = 0xFFFFFFFFu;

    const uint32_t* ptr32 = (const uint32_t*) input;
    while(length >= 4){
        crc = _mm_crc32_u32(crc, *ptr32++);
        length -= 4;
    }

    const uint8_t* ptr8 = (const uint8_t*) ptr32;
    while(length--){
        crc = _mm_crc32_u8(crc, *ptr8++);
    }

    return ~crc;

}
#endif
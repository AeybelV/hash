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

uint32_t crc32(const uint8_t* input, size_t length){
    uint32_t crc = 0xFFFFFFFFu;
    while(length--){
        crc = lookup[0][*input++ ^ (crc & 0xFF)] ^ (crc>>8);
    }

    return ~crc;
}

uint32_t crc32_32(const uint8_t* input, size_t length){
    uint32_t crc = 0xFFFFFFFFu;

    uint32_t *ptr32 = (uint32_t*) input;
    // 4 bytes at a time
    while(length >= 4){
        crc ^= *ptr32++;
        crc =   lookup[0][(crc >> 24  & 0xFF)] ^
                lookup[1][(crc >> 16  & 0xFF)] ^
                lookup[2][(crc >> 8   & 0xFF)] ^
                lookup[3][(crc        & 0xFF)];
        length -= 4;
    }
    uint8_t* remaining = (uint8_t*) ptr32;
    // Remaining bytes < 4 in the input
    while(length--){
        crc = lookup[0][*remaining++ ^ (crc & 0xFF)] ^ (crc>>8);
    }


    return ~crc;
}

uint32_t crc32_64(const uint8_t* input, size_t length){
    uint32_t crc = 0xFFFFFFFFu;

    uint64_t *ptr64 = (uint64_t*) input;
    // 8 bytes at a time
    while(length >= 8){
        uint64_t current = *ptr64++ ^ crc;
        crc =   lookup[7][(uint32_t)(current      )   & 0xFF] ^
                lookup[6][(uint32_t)(current  >> 8)   & 0xFF] ^
                lookup[5][(uint32_t)(current  >>16)   & 0xFF] ^
                lookup[4][(uint32_t)(current  >>24)   & 0xFF] ^
                lookup[3][(uint32_t)(current  >>32)   & 0xFF] ^
                lookup[2][(uint32_t)(current  >>40)   & 0xFF] ^
                lookup[1][(uint32_t)(current  >>48)   & 0xFF] ^
                lookup[0][(uint32_t)(current  >>56)   & 0xFF];
        length -= 8;
    }

    uint32_t *ptr32 = (uint32_t*) ptr64;
    // 4 bytes at a time
    while(length >= 4){
        crc ^= *ptr32++;
        crc =   lookup[0][(crc >> 24  & 0xFF)] ^
                lookup[1][(crc >> 16  & 0xFF)] ^
                lookup[2][(crc >> 8   & 0xFF)] ^
                lookup[3][(crc        & 0xFF)];
        length -= 4;
    }

    uint8_t* remaining = (uint8_t*) ptr32;
    // Remaining bytes < 4 in the input
    while(length--){
        crc = lookup[0][*remaining++ ^ (crc & 0xFF)] ^ (crc>>8);
    }
    return ~crc;
}


uint32_t crc32_128(const uint8_t* input, size_t length){
    uint32_t crc = 0xFFFFFFFFu;

    uint64_t *ptr128 = (uint64_t*) input;
    // 16 bytes at a time
    while(length >= 16){
        uint64_t left = *ptr128++ ^ crc;
        uint64_t right = *ptr128++;
        crc =   lookup[15][(uint32_t)(left      )   & 0xFF] ^
                lookup[14][(uint32_t)(left >> 8 )   & 0xFF] ^
                lookup[13][(uint32_t)(left >> 16)   & 0xFF] ^
                lookup[12][(uint32_t)(left >> 24)   & 0xFF] ^
                lookup[11][(uint32_t)(left >> 32)   & 0xFF] ^
                lookup[10][(uint32_t)(left >> 40)   & 0xFF] ^
                lookup[9 ][(uint32_t)(left >> 48)   & 0xFF] ^
                lookup[8 ][(uint32_t)(left >> 56)   & 0xFF] ^
                lookup[7][(uint32_t)(right      )   & 0xFF] ^
                lookup[6][(uint32_t)(right >> 8 )   & 0xFF] ^
                lookup[5][(uint32_t)(right >> 16)   & 0xFF] ^
                lookup[4][(uint32_t)(right >> 24)   & 0xFF] ^
                lookup[3][(uint32_t)(right >> 32)   & 0xFF] ^
                lookup[2][(uint32_t)(right >> 40)   & 0xFF] ^
                lookup[1][(uint32_t)(right >> 48)   & 0xFF] ^
                lookup[0][(uint32_t)(right >> 56)   & 0xFF];
        length -= 16;
    }
    uint64_t *ptr64 = (uint64_t*) ptr128;
    // 8 bytes at a time
    while(length >= 8){
        uint64_t current = *ptr64++ ^ crc;
        crc =   lookup[7][(uint32_t)(current      )   & 0xFF] ^
                lookup[6][(uint32_t)(current  >> 8)   & 0xFF] ^
                lookup[5][(uint32_t)(current  >>16)   & 0xFF] ^
                lookup[4][(uint32_t)(current  >>24)   & 0xFF] ^
                lookup[3][(uint32_t)(current  >>32)   & 0xFF] ^
                lookup[2][(uint32_t)(current  >>40)   & 0xFF] ^
                lookup[1][(uint32_t)(current  >>48)   & 0xFF] ^
                lookup[0][(uint32_t)(current  >>56)   & 0xFF];
        length -= 8;
    }

    uint32_t *ptr32 = (uint32_t*) ptr64;
    // 4 bytes at a time
    while(length >= 4){
        crc ^= *ptr32++;
        crc =   lookup[0][(crc >> 24  & 0xFF)] ^
                lookup[1][(crc >> 16  & 0xFF)] ^
                lookup[2][(crc >> 8   & 0xFF)] ^
                lookup[3][(crc        & 0xFF)];
        length -= 4;
    }

    uint8_t* remaining = (uint8_t*) ptr32;
    // Remaining bytes < 4 in the input
    while(length--){
        crc = lookup[0][*remaining++ ^ (crc & 0xFF)] ^ (crc>>8);
    }
    return ~crc;
}

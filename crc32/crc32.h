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

/**
 * @brief Simple CRC32 implementation using Sarwate Algorithm, utilizes a 256 entry lookup table of uint32_t (1KiB)
 * 
 * @param input Input message
 * @param length Length of the message
 * @return uint32_t CRC Result
 */
uint32_t crc32(const uint8_t* input, size_t length);

/**
 * @brief Simple CRC32 implementation using slicing by 4. 4 bytes are processed at a time from the input message, until finalizing with Sarwate. Utilizes 4 KiB lookup table
 * 
 * @param input Input message
 * @param length Length of the message
 * @return uint32_t CRC Result
 */
uint32_t crc32_32(const uint8_t* input, size_t length);

/**
 * @brief Simple CRC32 implementation using slicing by 8. 8 bytes are processed at a time from the input message, until finalizing with Sarwate. Utilizes 8 KiB lookup table
 * 
 * @param input Input message
 * @param length Length of the message
 * @return uint32_t CRC Result
 */
uint32_t crc32_64(const uint8_t* input, size_t length);

/**
 * @brief Simple CRC32 implementation using slicing by 16. 16 bytes are processed at a time from the input message, until finalizing with Sarwate. Utilizes 16 KiB lookup table
 *
 * @param input Input message
 * @param length Length of the message
 * @return uint32_t CRC Result
 */
uint32_t crc32_128(const uint8_t* input, size_t length);


#endif
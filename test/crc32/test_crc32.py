MAX_STRING_LENGTH = 262144
CRC32_ITERATIONS = 500

import ctypes
import zlib
from pathlib import Path
import os
from tqdm import tqdm
from zlib import crc32
from crc32c import crc32c

import string
import random

import numpy as np

from colorama import Fore, Back, Style


FAILED_TESTS = 0
file_path =Path(__file__).parent.resolve()

crc32_lib = ctypes.CDLL(os.path.join(file_path, '../bin/crc32.o'))
functions = [crc32_lib.crc32,crc32_lib.crc32_32,crc32_lib.crc32_64,crc32_lib.crc32_128,crc32_lib.crc32_128_]
functions_crc32c = [crc32_lib.crc32_sse_8,crc32_lib.crc32_sse_16,crc32_lib.crc32_sse_32]

def CRC32_Test(func):
    global FAILED_TESTS
    errors = []
    func.argtypes = (ctypes.POINTER(ctypes.c_char),ctypes.c_size_t)
    func.restype = ctypes.c_uint32
    for i in tqdm(range(CRC32_ITERATIONS), func.__name__):
        N = random.randint(0,MAX_STRING_LENGTH)
        input_str = ''.join(random.choices(string.ascii_letters, k=N))
        expected = crc32(input_str.encode('ascii'))
        actual = func(input_str.encode('ascii'),len(input_str))

        if(expected != actual):
            errors.append(input_str)

    if(len(errors) != 0):
        print(Fore.RED + "\n\tThere were %i failures" % len(errors))
        print(Style.RESET_ALL)
        error_array = np.array([errors])
        np.save("test/results/CRC32_%s_Errors" % func.__name__,error_array)
        FAILED_TESTS += 1
    else:
        print(Fore.GREEN + "\n\tPassed")
        print(Style.RESET_ALL)
    
def CRC32C_Test(func):
    global FAILED_TESTS
    errors = []
    func.argtypes = (ctypes.POINTER(ctypes.c_char),ctypes.c_size_t)
    func.restype = ctypes.c_uint32
    for i in tqdm(range(CRC32_ITERATIONS), func.__name__):
        N = random.randint(0,MAX_STRING_LENGTH)
        input_str = ''.join(random.choices(string.ascii_letters, k=N))
        expected = crc32c(input_str.encode('ascii'))
        actual = func(input_str.encode('ascii'),len(input_str))

        if(expected != actual):
            errors.append(input_str)

    if(len(errors) != 0):
        print(Fore.RED + "\n\tThere were %i failures" % len(errors))
        print(Style.RESET_ALL)
        error_array = np.array([errors])
        np.save("test/results/CRC32_%s_Errors" % func.__name__,error_array)
        FAILED_TESTS += 1
    else:
        print(Fore.GREEN + "\n\tPassed")
        print(Style.RESET_ALL)

if __name__ == '__main__':
    FAILED_TESTS = 0

    for func in functions:
        CRC32_Test(func)
    for func in functions_crc32c:
        CRC32C_Test(func)

    if FAILED_TESTS == 0:
        print(Fore.GREEN + "\n\n\t\tAll Tests passed\n\n")
        print(Style.RESET_ALL)
    else:
        print(Fore.RED + "\n\n\t\t%i Tests Failed\n\n" % FAILED_TESTS)
        print(Style.RESET_ALL)
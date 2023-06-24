#!/bin/bash 
set -e
echo
echo "========================= CRC32 =========================" 
echo
BASEDIR=$(dirname "$0")
gcc -fPIC -shared -o $BASEDIR/../bin/crc32.o crc32/crc32.c -DCRC32_USE32 -DCRC32_USE64 -DCRC32_USE128 -DCRC32_USE256 -DCRC32_USE512

python3 $BASEDIR/test_crc32.py


#!/bin/bash 
set -e
echo
echo "========================= CRC32 =========================" 
echo
BASEDIR=$(dirname "$0")
g++ $BASEDIR/BM_CRC32.cpp crc32/crc32.c -Icrc32/ -std=c++11 -lbenchmark -lpthread -O0 -g -o $BASEDIR/../bin/BM_CRC32-O0
g++ $BASEDIR/BM_CRC32.cpp crc32/crc32.c -Icrc32/ -std=c++11 -lbenchmark -lpthread -O2 -g -o $BASEDIR/../bin/BM_CRC32-O2
g++ $BASEDIR/BM_CRC32.cpp crc32/crc32.c -Icrc32/ -std=c++11 -lbenchmark -lpthread -O3 -g -o $BASEDIR/../bin/BM_CRC32-O3

$BASEDIR/../bin/BM_CRC32-O0 --benchmark_out=$BASEDIR/../results/CRC32-O0.csv --benchmark_out_format=csv
$BASEDIR/../bin/BM_CRC32-O2 --benchmark_out=$BASEDIR/../results/CRC32-O2.csv --benchmark_out_format=csv
$BASEDIR/../bin/BM_CRC32-O3 --benchmark_out=$BASEDIR/../results/CRC32-O3.csv --benchmark_out_format=csv
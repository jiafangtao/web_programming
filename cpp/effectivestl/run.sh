#! /bin/sh

set -e

clang -std=c++17 -lstdc++ main.cpp -o ./a
./a

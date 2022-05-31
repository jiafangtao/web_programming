#! /bin/sh

set -e

clang -lstdc++ main.cpp -o ./a
./a

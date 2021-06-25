#!/bin/sh
mkdir build -p -- build
cd build
cmake -GNinja ..
ninja && ./main
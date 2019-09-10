#!/usr/bin/env sh
mkdir build || true
cd build
cmake ..
make && make test

# Cracking the Coding Interview

Solve the question of Cracking the Coding Interview (6th Edition) with C++17

[![Build Status](https://travis-ci.org/dtrussel/crack.svg?branch=master)](https://travis-ci.org/dtrussel/crack)

## Dependencies
```
sudo apt install cmake ninja-build
```

Googletest is pulled in as a dependency as part of the cmake build.

## Build and Run
```
mkdir build && cd build
cmake -G Ninja -D CMAKE_BUILD_TYPE=Release ..
ninja
./run-crack
```

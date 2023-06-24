#!/usr/bin/env bash
mkdir -p build
cd build
cmake -GNinja -DCMAKE_BUILD_TYPE=Debug ../
ninja -j4
mv compile_commands.json ../

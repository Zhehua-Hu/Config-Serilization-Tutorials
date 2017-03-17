#!/usr/bin/env bash

rm -rf build/release/*
cd build/release
cmake -DCMAKE_BUILD_TYPE=Release ../../
make -j8
cd ../../

./bin/main


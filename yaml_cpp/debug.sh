#!/usr/bin/env bash

rm -rf build/debug/*
cd build/debug
cmake -DCMAKE_BUILD_TYPE=Debug ../../
make -j8
cd ../../

bin/main


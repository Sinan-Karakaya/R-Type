#!/bin/bash

isDebug=$1

if [ "$isDebug" = "debug" ]; then
    echo "Debug build"
    buildType="Debug"
else
    echo "Release build"
    buildType="Release"
fi

mkdir -p build
cd build
cmake -G Ninja .. -DCMAKE_BUILD_TYPE=$buildType
ninja
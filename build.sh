#!/bin/bash

if [[ $# == 0 ]]; then
    echo "missing \"release\" or \"debug\" build version argument"
    exit 1
fi

if [[ $1 == "release" ]]; then
    build_version="release"
elif [[ $1 == "debug" ]]; then
    build_version="debug"
else
    echo "unknown \"$1\" build version"
    exit 1
fi

cmake -DCMAKE_BUILD_TYPE=$build_version .

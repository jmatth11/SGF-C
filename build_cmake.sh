#!/bin/bash

if [ -z "$1" ]; then
  echo "directory must be supplied to build dependency with cmake."
  exit 1
fi

cd ./deps/$1
# shift the first argument off so we can pass the rest to the next call
shift
cmake -S . -B build $@ || exit 1
cmake --build build -j 4 || exit 1
cd -

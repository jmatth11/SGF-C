#!/bin/bash

if [ -z "$1" ]; then
  echo "directory must be supplied to build dependency with emscripten."
  exit 1
fi

cd ./deps/$1
# shift the first argument off so we can pass the rest to the next call
shift
emcmake cmake -S . -B web $@ || exit 1
cd ./web
emmake make -j4 || exit 1

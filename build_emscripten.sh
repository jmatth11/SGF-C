#!/bin/bash

if [ -z "$1" ]; then
  echo "directory must be supplied to build dependency with emscripten."
  exit 1
fi

cd ./deps/$1
# shift the first argument off so we can pass the rest to the next call
shift
emcmake cmake -S . -B web "-DCMAKE_EXE_LINKER_FLAGS=-s LEGACY_GL_EMULATION=1 -s GL_UNSAFE_OPTS=1 -sUSE_SDL=3" $@ || exit 1
cd ./web
emmake make -j4 || exit 1

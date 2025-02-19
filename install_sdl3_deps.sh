#!/bin/bash

if [ ! -d ./deps/sdl ]; then
  git clone --depth 1 --branch release-3.2.4 https://github.com/libsdl-org/SDL.git ./deps/sdl
  cd ./deps/sdl
  cmake -S . -B build -DSDL_STATIC=ON || exit 1
  cmake --build build -j 4 || exit 1
  cd -
fi

if [ ! -d ./deps/sdl_ttf ]; then
  git clone --recurse-submodules --depth 1 --branch preview-3.1.0 https://github.com/libsdl-org/SDL_ttf.git ./deps/sdl_ttf
  cd ./deps/sdl_ttf
  cmake -S . -B build -DSDL3_DIR=../sdl/build -DSDLTTF_VENDORED=ON || exit 1
  cmake --build build -j 4 || exit 1
fi

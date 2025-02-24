#!/bin/bash

if [ ! -d ./deps/sdl ]; then
  git clone --depth 1 --branch release-3.2.4 https://github.com/libsdl-org/SDL.git ./deps/sdl
  ./build_cmake.sh sdl -DSDL_STATIC=ON
fi

if [ ! -d ./deps/sdl_ttf ]; then
  git clone --recurse-submodules --depth 1 --branch preview-3.1.0 https://github.com/libsdl-org/SDL_ttf.git ./deps/sdl_ttf
  ./build_cmake.sh sdl_ttf -DSDL3_DIR=../sdl/build -DSDLTTF_VENDORED=ON
fi

if [ ! -d ./deps/sdl_image ]; then
  git clone --recurse-submodules --depth 1 --branch release-3.2.0 https://github.com/libsdl-org/SDL_image.git ./deps/sdl_image
  ./build_cmake.sh sdl_image -DSDL3_DIR=../sdl/build -DSDLIMAGE_VENDORED=ON
fi

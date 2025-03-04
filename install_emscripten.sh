#!/bin/bash

if [ ! -d ./deps/emsdk ]; then
  git clone https://github.com/emscripten-core/emsdk.git deps/emsdk || exit 1
  cd deps/emsdk || exit 1
  git pull || exit 1
  ./emsdk install latest || exit 1
  ./emsdk activate latest || exit 1
  source ./emsdk_env.sh || exit 1
  cd -
  ./build_emscripten.sh sdl
  ./build_emscripten.sh sdl_ttf -DSDL3_DIR=../sdl/web -DSDLTTF_VENDORED=ON
  ./build_emscripten.sh sdl_image -DSDL3_DIR=../sdl/web -DSDLIMAGE_VENDORED=ON
else
  cd ./deps/emsdk
  source ./emsdk_env.sh
  cd -
  ./build_emscripten.sh sdl
  ./build_emscripten.sh sdl_ttf -DSDL3_DIR=../sdl/web -DSDLTTF_VENDORED=ON
  ./build_emscripten.sh sdl_image -DSDL3_DIR=../sdl/web -DSDLIMAGE_VENDORED=ON -DSDLIMAGE_AVIF=OFF -DDAV1D_ASM=OFF
fi

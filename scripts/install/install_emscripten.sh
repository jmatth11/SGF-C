#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "${SCRIPT_DIR}/../.." && pwd)"

cd "${PROJECT_DIR}"

if [ ! -d ./deps/emsdk ]; then
  git clone https://github.com/emscripten-core/emsdk.git deps/emsdk || exit 1
  cd deps/emsdk || exit 1
  git pull || exit 1
  ./emsdk install latest || exit 1
  ./emsdk activate latest || exit 1
  source ./emsdk_env.sh || exit 1
  cd -
  "${SCRIPT_DIR}/../build/build_emscripten.sh" sdl
  "${SCRIPT_DIR}/../build/build_emscripten.sh" sdl_ttf -DSDL3_DIR=../sdl/web -DSDLTTF_VENDORED=ON
  "${SCRIPT_DIR}/../build/build_emscripten.sh" sdl_image -DSDL3_DIR=../sdl/web -DSDLIMAGE_VENDORED=ON -DSDLIMAGE_AVIF=OFF -DDAV1D_ASM=OFF
else
  cd ./deps/emsdk
  source ./emsdk_env.sh
  cd -
  "${SCRIPT_DIR}/../build/build_emscripten.sh" sdl
  "${SCRIPT_DIR}/../build/build_emscripten.sh" sdl_ttf -DSDL3_DIR=../sdl/web -DTTF_USE_HARFBUZZ -sUSE_HARFBUZZ -sUSE_FREETYPE -DSDLTTF_VENDORED=ON
  "${SCRIPT_DIR}/../build/build_emscripten.sh" sdl_image -DSDL3_DIR=../sdl/web -DSDLIMAGE_VENDORED=ON -DSDLIMAGE_AVIF=OFF -DDAV1D_ASM=OFF
fi

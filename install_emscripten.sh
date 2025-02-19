#!/bin/bash

build_emscripten_version() {
  cd ./deps/$1
  emcmake cmake -S . -B web $2 $3 || exit 1
  cd -
  cd ./deps/$1/web
  emmake make -j4 || exit 1
}

if [ ! -d ./deps/emsdk ]; then
  git clone https://github.com/emscripten-core/emsdk.git deps/emsdk || exit 1
  cd deps/emsdk || exit 1
  git pull || exit 1
  ./emsdk install latest || exit 1
  ./emsdk activate latest || exit 1
  source ./emsdk_env.sh || exit 1
  cd -
  build_emscripten_version sdl
  cd -
  build_emscripten_version sdl_ttf -DSDL3_DIR=../sdl/web -DSDLTTF_VENDORED=ON
else
  cd ./deps/emsdk
  source ./emsdk_env.sh
fi
cd -

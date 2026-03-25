#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "${SCRIPT_DIR}/../.." && pwd)"

cd "${PROJECT_DIR}"

if [ ! -d ./deps/sdl ]; then
  echo "================= installing SDL3 ================="
  git clone --depth 1 --branch release-3.4.0 https://github.com/libsdl-org/SDL.git ./deps/sdl
  "${SCRIPT_DIR}/../build/build_cmake.sh" sdl -DSDL_STATIC=ON -DSDL_X11_XTEST=OFF
fi

if [ ! -d ./deps/sdl_ttf ]; then
  echo "================= installing SDL3 TTF ================="
  git clone --recurse-submodules --depth 1 --branch release-3.2.2 https://github.com/libsdl-org/SDL_ttf.git ./deps/sdl_ttf
  "${SCRIPT_DIR}/../build/build_cmake.sh" sdl_ttf -DSDL3_DIR=../sdl/build -DSDLTTF_VENDORED=ON
fi

if [ ! -d ./deps/sdl_image ]; then
  echo "================= installing SDL3 Image ================="
  git clone --recurse-submodules --depth 1 --branch release-3.4.0 https://github.com/libsdl-org/SDL_image.git ./deps/sdl_image
  "${SCRIPT_DIR}/../build/build_cmake.sh" sdl_image -DSDL3_DIR=../sdl/build -DSDLIMAGE_VENDORED=ON
fi

if [ ! -d ./deps/sdl_mixer ]; then
  echo "================= installing SDL3 Mixer ================="
  git clone --depth 1 --branch release-3.2.0 https://github.com/libsdl-org/SDL_mixer.git ./deps/sdl_mixer
  "${SCRIPT_DIR}/../build/build_cmake.sh" sdl_mixer -DSDL3_DIR=../sdl/build
fi

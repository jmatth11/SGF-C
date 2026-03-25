#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

export LD_LIBRARY_PATH="${PROJECT_DIR}/deps/sdl/build:${PROJECT_DIR}/deps/sdl_ttf/build:${PROJECT_DIR}/deps/sdl_image/build:${PROJECT_DIR}/deps/cstd/lib"
source "${PROJECT_DIR}/deps/emsdk/emsdk_env.sh"

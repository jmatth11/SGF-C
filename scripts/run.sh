#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

cd "${PROJECT_DIR}"
LD_LIBRARY_PATH=./deps/sdl/build:./deps/sdl_ttf/build:./deps/sdl_image/build:./deps/cstd/lib:./deps/websocket-c/zig-out/lib ./bin/main

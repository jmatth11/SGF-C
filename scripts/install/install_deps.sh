#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "${SCRIPT_DIR}/../.." && pwd)"

cd "${PROJECT_DIR}"

sudo apt-get install -y wget meson pkg-config ragel gtk-doc-tools gcc g++ libfreetype6-dev libglib2.0-dev libcairo2-dev nasm

if [ ! -d ./deps/cstd ]; then
  git clone https://github.com/jmatth11/cstd.git deps/cstd
fi
if [ ! -d "./deps/websocket-c" ]; then
  git clone https://github.com/jmatth11/websocket-c.git deps/websocket-c
fi

"${SCRIPT_DIR}/../install/build_deps.sh" || exit 1

"${SCRIPT_DIR}/install_sdl3_deps.sh" || exit 1

source "${SCRIPT_DIR}/install_emscripten.sh" || exit 1

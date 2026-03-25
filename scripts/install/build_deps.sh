#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(cd "${SCRIPT_DIR}/../.." && pwd)"

cd "${PROJECT_DIR}"

cd deps/cstd
./install_deps.sh
zig build
make
cd -

cd deps/websocket-c
./install_deps
zig build -Doptimize=ReleaseSafe
cd -

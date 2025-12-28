#!/bin/bash

# build cstd
cd deps/cstd
./install_deps.sh
zig build
make
cd -

# build websocket-c
cd deps/websocket-c
./install_deps
zig build -Doptimize=ReleaseSafe
cd -


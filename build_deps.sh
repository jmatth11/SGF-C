#!/bin/bash

# build cstd
cd deps/cstd
make
zig build
cd -

# build websocket-c
cd deps/websocket-c
zig build
cd -


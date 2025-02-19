#!/bin/bash

sudo apt-get install -y wget meson pkg-config ragel gtk-doc-tools gcc g++ libfreetype6-dev libglib2.0-dev libcairo2-dev

# install core dependencies.
if [ ! -d ./deps/array_template ]; then
  git clone https://github.com/jmatth11/array_template.git deps/array_template
fi

./install_sdl3_deps.sh || exit 1

source ./install_emscripten.sh || exit 1

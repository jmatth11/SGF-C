if [ ! -d ./deps/emsdk ]; then
  mkdir -p emscripten
  git clone https://github.com/emscripten-core/emsdk.git deps/emsdk || exit 1
  cd deps/emsdk || exit 1
  git pull || exit 1
  ./emsdk install latest || exit 1
  ./emsdk activate latest || exit 1
  source ./emsdk_env.sh || exit 1
  cd -
  mkdir -p ./emscripten/sdl
  cd ./emscripten/sdl
  emcmake cmake ../../deps/sdl || exit 1
  emmake make -j4 || exit 1
  cd -
  mkdir -p ./emscripten/sdl_ttf
  cd ./emscripten/sdl_ttf
  emcmake cmake ../../deps/sdl_ttf -DSDL3_DIR=../sdl || exit 1
  emmake make -j4 || exit 1
else
  cd ./deps/emsdk
  source ./emsdk_env.sh
fi
cd -

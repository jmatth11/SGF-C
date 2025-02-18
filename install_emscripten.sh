if [ ! -d ./deps/emsdk ]; then
  mkdir -p ./libs
  git clone https://github.com/emscripten-core/emsdk.git deps/emsdk || exit 1
  cd deps/emsdk || exit 1
  git pull || exit 1
  ./emsdk install latest || exit 1
  ./emsdk activate latest || exit 1
  source ./emsdk_env.sh || exit 1
  cd -
  cd ./libs
  emcmake cmake ../deps/sdl/ || exit 1
  emmake make -j4 || exit 1
else
  cd ./deps/emsdk
  source ./emsdk_env.sh
fi
cd -

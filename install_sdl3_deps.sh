if [ ! -d ./deps/sdl ]; then
  mkdir -p ./deps/sdl || exit 1
  wget https://github.com/libsdl-org/SDL/releases/download/release-3.2.4/SDL3-3.2.4.tar.gz -O sdl.tar.gz || exit 1
  tar -xzf sdl.tar.gz -C ./deps/sdl || exit 1
  rm sdl.tar.gz
  cd ./deps/sdl
  sdl_folder=$(ls)
  mv $sdl_folder/* .
  rm -rf $sdl_folder
  cmake -S . -B build || exit 1
  cmake --build build -j 4 || exit 1
  cd -
fi

if [ ! -d ./deps/sdl_ttf ]; then
  mkdir -p ./deps/sdl_ttf || exit 1
  wget https://github.com/libsdl-org/SDL_ttf/releases/download/preview-3.1.0/SDL3_ttf-3.1.0.tar.gz -O sdl_ttf.tar.gz || exit 1
  tar -xzf sdl_ttf.tar.gz -C ./deps/sdl_ttf || exit 1
  rm sdl_ttf.tar.gz
  cd ./deps/sdl_ttf
  sdl_ttf_folder=$(ls)
  mv $sdl_ttf_folder/* .
  rm -rf $sdl_ttf_folder
  cmake -S . -B build -DSDL3_DIR=../sdl/build || exit 1
  cmake --build build -j 4 || exit 1
fi

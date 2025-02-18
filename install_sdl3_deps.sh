if [ ! -d ./deps/sdl ]; then
  mkdir -p ./deps/sdl || exit 1
  wget https://github.com/libsdl-org/SDL/releases/download/release-3.2.4/SDL3-3.2.4.tar.gz -O sdl.tar.gz
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

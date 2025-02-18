sudo apt-get install -y wget

# install core dependencies.
if [ ! -d ./deps/array_template ]; then
  git clone https://github.com/jmatth11/array_template.git deps/array_template
fi

./install_sdl3_deps.sh || exit 1

source ./install_emscripten.sh || exit 1

# Simple GUI Framework (SGF)

**!! WORK IN PROGRESS !!**

Project to have a general structure for me to create native and web apps with the SDL3 framework.

This project will install and locally build all SDL/emscripten dependencies for native and emscripten builds.


## Install Dependencies

Run the `./install_deps.sh` file to handle installing and building all needed dependencies.

## Build project

Use the `Makefile` to build the project.

For native
```bash
$ make
```

For emscripten
```bash
$ make web ARCH=web
```

Clean built files
```bash
$ make clean
```

## Run the Project

Run the native build with the `./run.sh` file at the base of the repo.

Run the emscripten field by building and running the Go application in `web`.

```bash
$ go build main.go
$ ./main
```

It runs on `localhost:8100`.

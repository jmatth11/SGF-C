# Simple GUI Framework (SGF)

**!! WORK IN PROGRESS !!**

Project to have a general structure for creating native and web apps with the SDL3 framework.

## Project Structure

```
SGF-C/
├── core/              # Shared framework code
│   └── src/
│       ├── components/  # UI components
│       ├── entities/    # Core entities
│       ├── logic/      # Game logic
│       ├── scenes/     # Scene definitions
│       └── types/      # Type definitions
├── platform/          # Platform-specific code
│   ├── native/        # Native implementation
│   └── web/           # Web implementation + Go server
├── resources/         # Fonts, icons, assets
├── scripts/           # Build and utility scripts
├── deps/              # Dependencies
├── bin/               # Native binary output
├── build/             # Web build output
└── obj/               # Object files
```

## Install Dependencies

Run the install script:
```bash
./scripts/install/install.sh
```

## Build Project

Use the `Makefile` to build the project.

### Native Build
```bash
make
```
Output: `bin/main`

### Web Build
```bash
make web ARCH=web
```
Output: `build/index.html`

### Clean Built Files
```bash
make clean
```

## Run Project

### Native
```bash
./scripts/run.sh
```

### Web
```bash
cd platform/web
go build -o server main.go
./server -d ../../build
```
Access at `localhost:8100`

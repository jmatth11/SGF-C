CFLAGS=-Wall -g -Wextra -std=c11
LIBS=-L./deps/sdl/build -L./deps/sdl_ttf/build -lSDL3 -lSDL3_ttf -lm -pthread -L./deps/cstd/lib -lcustom_std
WEB_LIBS=-L./deps/sdl/web -L./deps/sdl_ttf/web -l:libSDL3.a -l:libSDL3_ttf.a -L./deps/cstd/lib -l:libcustom_std.a -L./deps/cstd/deps/utf8-zig/zig-out/lib/ -l:libutf8-zig.a
WEB_DIR=./web
OBJ=obj
BIN=bin
INCLUDES=-I. -I./deps/sdl/include -I./deps/sdl_ttf/include -I./deps/cstd/headers/ -I./deps/cstd/deps/utf8-zig/headers
SOURCES=$(shell find . -name '*.c' -not -path './plugins/*' -not -path './deps/*' -not -path './libs/*')
OBJECTS=$(addprefix $(OBJ)/,$(SOURCES:%.c=%.o))
DEBUG_OBJECTS=$(patsubst %.c, $(OBJ)/%-debug.o, $(SOURCES))
DEPS=$(shell find . -maxdepth 3 -name Makefile -printf '%h\n' | grep -v 'unittest' | grep -v '^.$$')
RESOURCE_DIR=./resources
ifeq ($(ARCH), web)
$(info emscripten)
CC=emcc
TARGET=index.html
else
$(info native)
CC=clang
TARGET=main
endif

.PHONY: all
all: deps src

.PHONY: web
web:
	$(CC) $(CFLAGS) $(INCLUDES) $(WEB_LIBS) -o $(WEB_DIR)/$(TARGET) $(SOURCES) --embed-file $(RESOURCE_DIR)

.PHONY: src
src: $(OBJECTS)
	$(CC) $^ -O2 $(CFLAGS) $(LIBS) -o $(BIN)/$(TARGET)

.PHONY: debug
debug: deps_debug debugsrc

.PHONY: debugsrc
debugsrc: $(DEBUG_OBJECTS)
	$(CC) $^ -ggdb $(CFLAGS) $(LIBS) -o $(BIN)/$(TARGET)

$(OBJ)/%.o: %.c
	@mkdir -p $(dir $@)
	@mkdir -p $(BIN)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDES)

$(OBJ)/%-debug.o: %.c
	@mkdir -p $(dir $@)
	@mkdir -p $(BIN)
	$(CC) -ggdb -c -o $@ $< $(CFLAGS) $(INCLUDES)

.PHONY: clean
clean:
	@rm -rf $(OBJ)/* 2> /dev/null
	@rm -f $(BIN)/* 2> /dev/null

.PHONY: clean_deps
clean_deps:
	$(foreach dir, $(DEPS), $(shell cd $(dir) && $(MAKE) clean))

.PHONY: clean_all
clean_all: clean clean_deps

.PHONY: deps
deps:
	@for i in $(DEPS); do\
		cd $${i} && $(MAKE) && cd -;\
	done

.PHONY: deps_debug
deps_debug:
	@for i in $(DEPS); do\
		cd $${i} && ($(MAKE) debug || $(MAKE)) && cd -;\
	done


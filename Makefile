CFLAGS=-Wall -Wextra -std=c11 -fsanitize=undefined
# linker flag to satisfy GNU-stack warnings
LINKER_FLAGS=-z noexecstack

LIBS=-L./deps/sdl/build
LIBS+=-L./deps/sdl_ttf/build
LIBS+=-L./deps/sdl_image/build
LIBS+=-lSDL3
LIBS+=-lSDL3_ttf
LIBS+=-lSDL3_image
LIBS+=-lm
LIBS+=-pthread
LIBS+=-L./deps/cstd/deps/utf8-zig/zig-out/lib
LIBS+=-lutf8-zig
LIBS+=-L./deps/cstd/lib
LIBS+=-lcustom_std
LIBS+=-L./deps/websocket-c/zig-out/lib
LIBS+=-l:libws.a

WEB_LIBS=-L./deps/sdl/web
WEB_LIBS+=-L./deps/sdl_ttf/web
WEB_LIBS+=-l:libSDL3.a
WEB_LIBS+=-l:libSDL3_ttf.a
WEB_LIBS+=-L./deps/cstd/deps/utf8-zig/zig-out/lib/
WEB_LIBS+=-lwebutf8-zig
WEB_LIBS+=-L./deps/cstd/zig-out/lib
WEB_LIBS+=-lwebcustom_std

INCLUDES=-I.
INCLUDES+=-I./deps/sdl/include
INCLUDES+=-I./deps/sdl_ttf/include
INCLUDES+=-I./deps/sdl_image/include
INCLUDES+=-I./deps/cstd/headers/
INCLUDES+=-I./deps/cstd/deps/utf8-zig/headers
INCLUDES+=-I./deps/websocket-c/headers

SOURCES=$(shell find ./src -name '*.c')
OBJECTS=$(addprefix $(OBJ)/,$(SOURCES:%.c=%.o))
DEPS=$(shell find ./deps -maxdepth 2 -name Makefile -printf '%h\n' | grep -v 'unittest' | grep -v '^.$$')

RESOURCE_DIR=./resources
WEB_DIR=./web
OBJ=obj
BIN=bin
TARGET=main
CC=clang

ifeq ($(ARCH), web)
$(info emscripten)
CC=emcc
TARGET=index.html
undefine OBJECTS
endif

ifeq ($(DEBUG), 1)
	CFLAGS+= -ggdb
else
	CFLAGS+= -O2
endif

.PHONY: all
all: src

.PHONY: src
src: $(OBJECTS)
ifeq ($(ARCH), web)
	$(CC) $(CFLAGS) $(INCLUDES) $(WEB_LIBS) -o $(WEB_DIR)/$(TARGET) $(SOURCES) --embed-file $(RESOURCE_DIR)
else
	$(CC) $^ $(CFLAGS) -o $(BIN)/$(TARGET) $(LIBS) $(LINKER_FLAGS)
endif

$(OBJ)/%.o: %.c
	@mkdir -p $(dir $@)
	@mkdir -p $(BIN)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDES)

.PHONY: clean
clean:
	@rm -rf $(OBJ)/* 2> /dev/null
	@rm -f $(BIN)/* 2> /dev/null

#.PHONY: clean_deps
#clean_deps:
#	$(foreach dir, $(DEPS), $(shell cd $(dir) && $(MAKE) clean))

.PHONY: clean_all
clean_all: clean clean_deps

# doesn't work with more than 1 depth dependencies
#.PHONY: deps
#deps:
#	@for i in $(DEPS); do\
#		$(MAKE) -C $${i} MAKEFLAGS= ; \
#	done
#
#.PHONY: deps_debug
#deps_debug:
#	@for i in $(DEPS); do\
#		cd $${i} && ($(MAKE) debug || $(MAKE)) && cd -;\
#	done


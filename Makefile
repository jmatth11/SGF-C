CFLAGS=-Wall -Wextra -std=c11
LIBS=-L./deps/sdl/build -L./deps/sdl_ttf/build -L./deps/sdl_image/build -lSDL3 -lSDL3_ttf -lSDL3_image -lm -pthread
WEB_LIBS=-L./deps/sdl/web -L./deps/sdl_ttf/web -L./deps/sdl_image/web -l:libSDL3.a -l:libSDL3_ttf.a -l:libSDL3_image.a
WEB_DIR=./web
OBJ=obj
BIN=bin
INCLUDES=-I. -I./deps/sdl/include -I./deps/sdl_ttf/include -I./deps/sdl_image/include
SOURCES=$(shell find . -name '*.c' -not -path './plugins/*' -not -path './deps/*' -not -path './libs/*')
OBJECTS=$(addprefix $(OBJ)/,$(SOURCES:%.c=%.o))
DEBUG_OBJECTS=$(patsubst %.c, $(OBJ)/%-debug.o, $(SOURCES))
DEPS=$(shell find . -maxdepth 3 -name Makefile -printf '%h\n' | grep -v 'unittest' | grep -v '^.$$')
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
	$(CC) $(CFLAGS) $(INCLUDES) $(WEB_LIBS) -o $(WEB_DIR)/$(TARGET) $(SOURCES)

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
	$(shell cd $(UTF_DEP) && $(MAKE) clean)

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


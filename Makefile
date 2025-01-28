CC=clang
CFLAGS=-Wall -Wextra -std=c11
LIBS=-lSDL3 -lm -pthread
OBJ=obj
BIN=bin
INCLUDES=-I.
SOURCES=$(shell find . -name '*.c' -not -path './plugins/*' -not -path './deps/*')
OBJECTS=$(addprefix $(OBJ)/,$(SOURCES:%.c=%.o))
DEBUG_OBJECTS=$(patsubst %.c, $(OBJ)/%-debug.o, $(SOURCES))
DEPS=$(shell find . -name Makefile -printf '%h\n' | grep -v 'unittest' | grep -v '^.$$' | grep -v 'utf8-zig')
TARGET=main

.PHONY: all
all: deps src

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


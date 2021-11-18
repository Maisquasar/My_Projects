PROGRAM=game

# Add your objs to generate in OBJS var
OBJS= src/game.o src/core/render.o src/datas/moves.o src/datas/species.o src/rules/rules.o src/tools/textures.o src/tools/keyboardHolder.o src/core/fight.o

CC?=g++
TARGET?=$(shell $(CC) -dumpmachine)

CXXFLAGS=-O0 -g -Wall -Wextra -Wno-unused-parameter
CPPFLAGS=-Iinclude -Ithird_party/include -MMD
LDFLAGS=-Lthird_party/libs-$(TARGET)
LDLIBS=-lraylib

ifeq ($(TARGET),x86_64-linux-gnu)
LDLIBS+=-ldl -lpthread -lm
else ifeq ($(TARGET),x86_64-pc-cygwin)
LDLIBS+=-lgdi32
endif

DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: $(PROGRAM)

-include $(DEPS)

%.o: %.c
	$(CC) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

$(PROGRAM): $(OBJS)
	$(CC) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

build.tar.gz: $(PROGRAM) $(wildcard assets/*)
	tar czf build.tar.gz $(PROGRAM) assets

clean:
	rm -f $(OBJS) $(DEPS) build.tar.gz $(PROGRAM)
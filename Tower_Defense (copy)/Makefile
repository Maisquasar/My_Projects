PROGRAM=tower

# Add your objs to generate in OBJS var
OBJS=src/main.o src/render.o src/textureloader.o src/map.o src/action.o src/mathHelper.o src/rounds.o src/particle.o

CXX?=g++
TARGET?=$(shell $(CXX) -dumpmachine)

OPTIM_FLAGS?=-O0
CXXFLAGS=$(OPTIM_FLAGS) -g -Wall -Wextra -Wno-unused-parameter 
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

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

$(PROGRAM): $(OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

build.tar.gz: $(PROGRAM) $(wildcard assets/*)
	tar czf build.tar.gz $(PROGRAM) assets

clean:
	rm -f $(OBJS) $(DEPS) $(PROGRAM) build.tar.gz

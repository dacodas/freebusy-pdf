.SUFFIXES:

C_SOURCES = $(shell find src -name '*.c')
C_OBJECTS = $(patsubst src/%.c,build/c/%.o,$(C_SOURCES))

CXX_SOURCES = $(shell find src -name '*.cpp')
CXX_OBJECTS = $(patsubst src/%.cpp,build/c/%.o,$(CXX_SOURCES))

C_FLAGS = -g
CXX_FLAGS = -g

build/freebusy: $(C_OBJECTS) $(CXX_OBJECTS)
	g++ $(CXX_FLAGS) -Isrc -o $@ $^ -lcairo -lical

build/c/%.o: src/%.cpp
	g++ $(CXX_FLAGS) -Isrc -o $@ -c $<

build/c/%.o: src/%.c
	gcc $(C_FLAGS) -Isrc -o $@ -c $<

build/c/main.o: src/strokeHelper.c.in

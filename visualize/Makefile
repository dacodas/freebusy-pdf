.SUFFIXES:

C_SOURCES = $(shell find src -name '*.c')
C_OBJECTS = $(patsubst src/%.c,build/c/%.o,$(C_SOURCES))

CXX_SOURCES = $(shell find src -name '*.cpp')
CXX_OBJECTS = $(patsubst src/%.cpp,build/c/%.o,$(CXX_SOURCES))

build/freebusy: $(C_OBJECTS) $(CXX_OBJECTS)
	g++ -Isrc -o $@ $^ -lcairo

build/c/%.o: src/%.cpp
	g++ -Isrc -o $@ -c $<

build/c/%.o: src/%.c
	gcc -Isrc -o $@ -c $<

build/c/main.o: src/strokeHelper.c.in

build/freebusy-calendar: build/specification.o src/main.cpp
	g++ -Isrc -o $@ src/main.cpp build/specification.o -lcairo

build/specification.o: src/specification.c
	gcc -Isrc -o $@ -c $<

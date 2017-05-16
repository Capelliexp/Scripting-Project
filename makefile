CC=g++
CFLAGS=-I lua/src -I irrlicht/include/ irrlicht/lib/Linux/libIrrlicht.a -L/usr/lib/x86_64-linux-gnu/mesa -lGL -lX11 -lXxf86vm -otask3 -L lua/src -llua -std=c++11

Project: main.cpp luaFunctions.cpp globals.h lua/src/liblua.a irrlicht/lib/Linux/libIrrlicht.a
	$(CC) main.cpp $(CFLAGS) -o $@ -ldl

lua/src/liblua.a:
	cd lua/src; make linux

irrlicht/lib/Linux/libIrrlicht.a:
	cd irrlicht/source/Irrlicht/; make linux
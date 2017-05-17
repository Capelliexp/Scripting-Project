CC=g++
CFLAGS=-I project/lua/src -I project/irrlicht/include/ project/irrlicht/lib/Linux/libIrrlicht.a -L/usr/lib/x86_64-linux-gnu/mesa -lGL -lX11 -lXxf86vm -otask3 -L project/lua/src -llua -std=c++11

main: project/main.cpp project/luaFunctions.cpp project/globals.h project/lua/src/liblua.a project/irrlicht/lib/Linux/libIrrlicht.a
	$(CC) project/main.cpp $(CFLAGS) -o $@ -ldl

project/lua/src/liblua.a:
	cd project/lua/src; make linux

project/irrlicht/lib/Linux/libIrrlicht.a:
	cd project/irrlicht/source/Irrlicht/; make linux
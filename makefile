CC=g++
CFLAGS=-I project/lua/src -I project/irrlicht/include/ project/irrlicht/lib/Linux/libIrrlicht.a -L/usr/lib/x86_64-linux-gnu/mesa -lGL -lX11 -lXxf86vm -otask3 -L project/lua/src -llua -std=c++11

main: project/main.cpp project/luaFunctions.cpp project/globals.h project/lua/src/liblua.a project/irrlicht/lib/Linux/libIrrlicht.a project/TriangleNode.cpp
	$(CC) project/main.cpp $(CFLAGS) -o $@ -ldl

project/lua/src/liblua.a:
	cd project; curl https://www.lua.org/ftp/lua-5.3.4.tar.gz -o lua.tgz; \
	tar -xzvf lua.tgz; \
	mv lua-5.3.4 lua; \
	cd lua/src; make linux; \
	cd ..; cd ..; \
	rm lua.tgz; \
	cd ..; \

project/irrlicht/lib/Linux/libIrrlicht.a:
	cd project; \
	curl -L -oirr.zip http://downloads.sourceforge.net/project/irrlicht/Irrlicht%20SDK/1.8/1.8.4/irrlicht-1.8.4.zip; \
	unzip irr.zip; \
	mv irrlicht-1.8.4 irrlicht; \
	cd irrlicht/source/Irrlicht/; make linux; \
	cd ..; cd ..; cd ..; \
	rm irr.zip; \
	cd ..; \

clean:
	rm -f main; \
	cd project; rm -rf lua; rm -rf irrlicht; \
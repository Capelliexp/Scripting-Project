#ifndef LUAFUNCTIONS_CPP
#define LUAFUNCTIONS_CPP

#include "globals.h"

static int AddMesh(lua_State *L){   //AddMesh({{x1,y1,z1}, {x2,y2,z2}, {x3,y3,z3}})  -  OBS! 1 parameter
    int args = lua_gettop(L);
    int point1[3], point2[3], point3[3];

    lua_rawgeti(L, 1, 1);
    point1[0] = lua_tonumber(L, 3);
    lua_rawgeti(L, 1, 2);
    point1[1] = lua_tonumber(L, 4);
    lua_rawgeti(L, 1, 3);
    point1[2] = lua_tonumber(L, 5);

    std::cout << "   AddMesh() coords: "/* << std::endl*/;
    std::cout << point1[0] << " " << point1[1] << " " << point1[2] /*<< ", " << x2 << " " << y2 << " " << z2 << ", " << x3 << " " << y3 << " " << z3*/ << std::endl;

    return 0;
}

static int AddBox(lua_State *L){   //AddBox({xPos,yPos,zPos}, size, name)
    int args = lua_gettop(L);
    int point[3], size;
    std::string name = "";

    //point = (L, 1);
    size = lua_tonumber(L, 2);
    name = lua_tostring(L, 3);

    /*  //funkar lite
    lua_rawgeti(L, 1, 2);
    point[0] = lua_tonumber(L, 3);
    lua_rawgeti(L, 1, 3);
    point[1] = lua_tonumber(L, 4);
    lua_rawgeti(L, 1, 4);
    point[2] = lua_tonumber(L, 5);
    */

    //something something size

    //something something name

    std::cout << "   AddBox() coords: "/* << std::endl*/;
    std::cout << point[0] << " " << point[1] << " " << point[2] << std::endl;

    return 0;
}

static int GetNodes(lua_State *L){  //GetNodes()

    return 0;
}

static int Camera(lua_State *L){    //Camera({xPos,yPos,zPos}, {xLook,yLook,zLook})

    return 0;
}

static int Snapshot(lua_State *L){  //Snapshot(name)

    return 0;
}

static int AddTexture(lua_State *L){  //AddTexture({{{1.0,0.5,0.5},...},{{0.5,0.5,1.0},...}...}, "yoyo")  -  OBS! 2 parameters, varying size of parameter 1

    return 0;
}

#endif
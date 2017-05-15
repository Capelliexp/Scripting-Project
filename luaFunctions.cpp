#ifndef LUAFUNCTIONS_CPP
#define LUAFUNCTIONS_CPP

#include "globals.h"

static int AddMesh(lua_State *L){   //AddMesh({{x1,y1,z1}, {x2,y2,z2}, {x3,y3,z3}})  -  OBS! 1 paramater
    int x1, y1, z1, x2, y2, z2, x3, y3, z3;

    x1 = lua_tonumber(L, 1);
    y1 = lua_tonumber(L, 2);
    z1 = lua_tonumber(L, 3);

    std::cout << "AddMesh() coords:" << std::endl;
    std::cout << " " << x1 << " " << y1 << " " << z1 /*<< ", " << x2 << " " << y2 << " " << z2 << ", " << x3 << " " << y3 << " " << z3*/ << std::endl;

    return 0;
}

static int AddBox(lua_State *L){   //AddBox({xPos,yPos,zPos}, size, name)

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

#endif
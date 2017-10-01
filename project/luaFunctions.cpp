#ifndef LUAFUNCTIONS_CPP
#define LUAFUNCTIONS_CPP

#include "globals.h"

/*static int AddMesh(lua_State *L){
    luaL_checktype(L, 1, LUA_TTABLE);

    if(lua_gettop(L) > 1)
        return luaL_error(L, "ERROR: number of arguments");

    int meshCount = 0;
    int verticeCount = luaL_len(L,1);

    if((verticeCount < 3) || ((verticeCount%3) != 0))
        return luaL_error(L, "ERROR: invalid number of coordinates");

    for(int i = 0; i < (verticeCount/3); i++){  //loop once for every mesh to be drawn
        float point[9];
        
        for(int i = 0; i < 3; i++){   //1 loop for every 1 point (with x,y,z-values)
            lua_rawgeti(L, 1, (i+1)+(3*meshCount));   //add table to stack (1x3 values)
            if(lua_istable(L, -1) != 1)
            return luaL_error(L, "ERROR: invalid table");
                    
            lua_rawgeti(L, -1, 1);  //x_i to stack
            lua_rawgeti(L, -2, 2);  //y_i to stack
            lua_rawgeti(L, -3, 3);  //z_i to stack
            if(lua_isnumber(L, -1) != 1 || lua_isnumber(L, -2) != 1 || lua_isnumber(L, -3) != 1)
                return luaL_error(L, "ERROR: invalid coordinates");
                    
            point[0+(3*i)] = lua_tonumber(L, -3);    //stack spot x to point1[0]
            point[1+(3*i)] = lua_tonumber(L, -2);    //stack spot y to point1[1]
            point[2+(3*i)] = lua_tonumber(L, -1);    //stack spot z to point1[2]

            lua_rawgeti(L, -4, 4);   //checking size of array
            luaL_argcheck(L, (lua_type(L, -1) != LUA_TNUMBER), 0, "ERROR: number of components");
        }

        float uv1[2] = {0,0}; float uv2[2] = {1,0}; float uv3[2] = {0.5,1};
        float point1[3] = {point[0], point[1], point[2]};
        float point2[3] = {point[3], point[4], point[5]};
        float point3[3] = {point[6], point[7], point[8]};

        if(!NewTriangle(point1, point2, point3, uv1, uv2, uv3, "", ""))
            return luaL_error(L, "ERROR: unable to create triangle");

        meshCount++;
    }
    return 0;
}*/

static int AddMesh(lua_State *L){
    luaL_checktype(L, 1, LUA_TTABLE);

    if(lua_gettop(L) > 1)
        return luaL_error(L, "ERROR: number of arguments");

    int meshCount = 0;
    int verticeCount = luaL_len(L,1);

    if((verticeCount < 3) || ((verticeCount%3) != 0))
        return luaL_error(L, "ERROR: invalid number of coordinates");

    for(int i = 0; i < (verticeCount/3); i++){  //loop once for every mesh to be drawn
        float point[9];
        
        for(int j = 0; j < 3; j++){   //1 loop for every 1 point (with x,y,z-values)

            lua_rawgeti(L, 1, (j+1)+(3*i));   //add table to stack (1x3 values)
            if(lua_istable(L, -1) != 1)
                return luaL_error(L, "ERROR: invalid table");
            
            lua_rawgeti(L, -1, 1);  //x_i to stack
            lua_rawgeti(L, -2, 2);  //y_i to stack
            lua_rawgeti(L, -3, 3);  //z_i to stack
            if(lua_isnumber(L, -1) != 1 || lua_isnumber(L, -2) != 1 || lua_isnumber(L, -3) != 1)
                return luaL_error(L, "ERROR: invalid coordinates");
                    
            point[0+(3*j)] = lua_tonumber(L, -3);    //stack spot x to point1[0]
            point[1+(3*j)] = lua_tonumber(L, -2);    //stack spot y to point1[1]
            point[2+(3*j)] = lua_tonumber(L, -1);    //stack spot z to point1[2]

            lua_pop(L, 3);  //new - remove the top 3 elements on the stack (solves segmentation fault)

            lua_rawgeti(L, -1, 4);   //checking size of array
            luaL_argcheck(L, (lua_type(L, -1) != LUA_TNUMBER), 0, "ERROR: number of components");
        }

        float uv1[2] = {0,0}; float uv2[2] = {1,0}; float uv3[2] = {0.5,1};
        float point1[3] = {point[0], point[1], point[2]};
        float point2[3] = {point[3], point[4], point[5]};
        float point3[3] = {point[6], point[7], point[8]};

        if(!NewTriangle(point1, point2, point3, uv1, uv2, uv3, "", ""))
            return luaL_error(L, "ERROR: unable to create triangle");

        meshCount++;
    }
    return 0;
}

static int AddBox(lua_State *L){   //AddBox({xPos,yPos,zPos}, size, name)
    float coords[3], size;
    std::string name = "";

    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TNUMBER);

    if(lua_gettop(L) > 3)
        return luaL_error(L, "ERROR: number of arguments");

    size = lua_tonumber(L, 2);

    if(lua_isstring(L, 3)) name = lua_tostring(L, 3);
    else lua_pushinteger(L, -1);

    lua_rawgeti(L, 1, 1);   //push xPos to next position in stack (4)
    lua_rawgeti(L, 1, 2);   //push yPos to next position in stack (5)
    lua_rawgeti(L, 1, 3);   //push zPos to next position in stack (6)

    if(lua_isnumber(L, 4) != 1 || lua_isnumber(L, 5) != 1 || lua_isnumber(L, 6) != 1)
        return luaL_error(L, "ERROR: invalid coordinates");

    coords[0] = lua_tonumber(L, 4);  //retrieve xPos from stack at 4
    coords[1] = lua_tonumber(L, 5);  //retrieve yPos from stack at 5
    coords[2] = lua_tonumber(L, 6);  //retrieve zPos from stack at 6

    lua_rawgeti(L, 1, 4);   //checking number of arguments
    if(lua_isnumber(L, -1) == 1)
        return luaL_error(L, "ERROR: number of components");

    NewBox(size, coords, "", name);

    return 0;
}

static int GetNodes(lua_State *L){  //GetNodes()
    //call with: for k,v in pairs(getNodes()) do for kk,vv in pairs(v) do print(k,kk,vv) end end

    std::string str1 = "";
    std::string str2 = "";
    std::string str3 = "";
    std::string type = "";

    lua_newtable(L); //create table_master in stack (1)

    for(int i = 0; i < name.size(); i++){

        if(name[i] != ""){

            if(trianglenode[i] != NULL) type = "triangle";
            else if(meshnode[i]->getType() == irr::scene::ESNT_CUBE) type = "cube    ";
            else type = "sphere  ";

            //str1 = std::to_string(i);
            str1 = std::to_string(GetID(i));
            str2 = type;
            str3 = name[i];

            const char * c1 = str1.c_str();
            const char * c2 = str2.c_str();
            const char * c3 = str3.c_str();

            lua_newtable(L);    //create table_i in stack (i+2)

            lua_pushstring(L, "ID:");
            lua_pushstring(L, c1);
            lua_settable(L, -3);    //table_i[1] = str1 (pops -1 & -2)

            lua_pushstring(L, "Type:");
            lua_pushstring(L, c2);
            lua_settable(L, -3);    //table_i[2] = str2 (pops -1 & -2)

            lua_pushstring(L, "Name:");
            lua_pushstring(L, c3);
            lua_settable(L, -3);    //table_i[3] = str3 (pops -1 & -2)

            lua_pushinteger(L, i+1);
            lua_insert(L, -2);
            lua_settable(L, -3);    //table_master[i+1] = table_i[]
        }
    }

    return 1;
}

static int Camera(lua_State *L){    //Camera({xPos,yPos,zPos}, {xLook,yLook,zLook})
    float pos[3], look[3];

    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TTABLE);

    if(lua_gettop(L) > 2)
        return luaL_error(L, "ERROR: number of arguments");

    //---------------

    lua_rawgeti(L, 1, 1);   //xPos to stack (3)
    lua_rawgeti(L, 1, 2);   //yPos to stack (4)
    lua_rawgeti(L, 1, 3);   //zPos to stack (5)
    if((lua_isnumber(L, 3) != 1) || (lua_isnumber(L, 4) != 1) || (lua_isnumber(L, 5) != 1))
        return luaL_error(L, "ERROR: invalid coordinates (Pos)");

    pos[0] = lua_tonumber(L, 3);  //stack spot 3 to pos[0]
    pos[1] = lua_tonumber(L, 4);  //stack spot 4 to pos[1]
    pos[2] = lua_tonumber(L, 5);  //stack spot 5 to pos[2]

    //---------------

    lua_rawgeti(L, 2, 1);   //xLook to stack (6)
    lua_rawgeti(L, 2, 2);   //yLook to stack (7)
    lua_rawgeti(L, 2, 3);   //zLook to stack (8)
    if(lua_isnumber(L, 6) != 1 || lua_isnumber(L, 7) != 1 || lua_isnumber(L, 8) != 1)
        return luaL_error(L, "ERROR: invalid coordinates (Look)");

    look[0] = lua_tonumber(L, 6);  //stack spot 3 to pos[0]
    look[1] = lua_tonumber(L, 7);  //stack spot 4 to pos[1]
    look[2] = lua_tonumber(L, 8);  //stack spot 5 to pos[2]

    //---------------

    lua_rawgeti(L, 1, 4);   //checking number of arguments (9)
    lua_rawgeti(L, 2, 4);   //checking number of arguments (10)
    if(lua_isnumber(L, -1) == 1 || lua_isnumber(L, -2) == 1)
        return luaL_error(L, "ERROR: number of components");

    MoveCamera(pos, look);

    return 0;
}

static int Snapshot(lua_State *L){  //Snapshot(name)
    luaL_checktype(L, 1, LUA_TSTRING);
    std::string name = lua_tostring(L, 1);
    captureScene = name;
    captureSceneCount = 1;

    return 0;
}

#endif

#ifndef LUAFUNCTIONS_CPP
#define LUAFUNCTIONS_CPP

#include "globals.h"

static int AddMesh(lua_State *L){   //AddMesh({{x1,y1,z1}, {x2,y2,z2}, {x3,y3,z3}, ...})  -  OBS! 1 parameter
    float point1[3], point2[3], point3[3];

    luaL_checktype(L, 1, LUA_TTABLE);

    //------------------------

    lua_rawgeti(L, 1, 1);   //add table 1 to stack (1x3 värden) (2)
    if(lua_istable(L, 2) != 1)
        return luaL_error(L, "ERROR: invalid table (point1)");
    lua_rawgeti(L, 2, 1);   //x1 to stack (3)
    lua_rawgeti(L, 2, 2);   //y1 to stack (4)
    lua_rawgeti(L, 2, 3);   //z1 to stack (5)
    if(lua_isnumber(L, 3) != 1 && lua_isnumber(L, 4) != 1 && lua_isnumber(L, 5) != 1)
        return luaL_error(L, "ERROR: invalid coordinates (point1)");
    point1[0] = lua_tonumber(L, 3);  //stack spot 3 to point1[0]
    point1[1] = lua_tonumber(L, 4);  //stack spot 4 to point1[1]
    point1[2] = lua_tonumber(L, 5);  //stack spot 5 to point1[2]

    //------------------------

    lua_rawgeti(L, 1, 2);   //add table 2 to stack (1x3 värden) (6)
    if(lua_istable(L, 6) != 1)
        return luaL_error(L, "ERROR: invalid table (point2)");
    lua_rawgeti(L, 6, 1);   //x2 to stack (7)
    lua_rawgeti(L, 6, 2);   //y2 to stack (8)
    lua_rawgeti(L, 6, 3);   //z2 to stack (9)
    if(lua_isnumber(L, 7) != 1 && lua_isnumber(L, 8) != 1 && lua_isnumber(L, 9) != 1)
        return luaL_error(L, "ERROR: invalid coordinates (point2)");
    point2[0] = lua_tonumber(L, 7);  //stack spot 7 to point2[0]
    point2[1] = lua_tonumber(L, 8);  //stack spot 8 to point2[1]
    point2[2] = lua_tonumber(L, 9);  //stack spot 9 to point2[2]

    //------------------------

    lua_rawgeti(L, 1, 3);   //add table 3 to stack (1x3 värden) (10)
    if(lua_istable(L, 10) != 1)
        return luaL_error(L, "ERROR: invalid table (point3)");
    lua_rawgeti(L, 10, 1);   //x2 to stack (11)
    lua_rawgeti(L, 10, 2);   //y2 to stack (12)
    lua_rawgeti(L, 10, 3);   //z2 to stack (13)
    if(lua_isnumber(L, 11) != 1 && lua_isnumber(L, 12) != 1 && lua_isnumber(L, 13) != 1)
        return luaL_error(L, "ERROR: invalid coordinates (point3)");
    point3[0] = lua_tonumber(L, 11);  //stack spot 11 to point3[0]
    point3[1] = lua_tonumber(L, 12);  //stack spot 12 to point3[1]
    point3[2] = lua_tonumber(L, 13);  //stack spot 13 to point3[2]

    //------------------------

    lua_rawgeti(L, 2, 4);   //checking number of arguments (14)
    lua_rawgeti(L, 6, 4);   //checking number of arguments (15)
    lua_rawgeti(L, 10, 4);   //checking number of arguments (16)
    if(lua_isnumber(L, 14) == 1 || lua_isnumber(L, 15) == 1 || lua_isnumber(L, 16) == 1)
        return luaL_error(L, "ERROR: number of components");

    //------------------------

    /*std::cout <<
        "   point1: (" << point1[0] << "," << point1[1] << "," << point1[2] << ")" << std::endl <<
        "   point2: (" << point2[0] << "," << point2[1] << "," << point2[2] << ")" << std::endl <<
        "   point3: (" << point3[0] << "," << point3[1] << "," << point3[2] << ")" << std::endl;*/

    float uv1[2] = {0,0}; float uv2[2] = {1,0}; float uv3[2] = {0.5,1};
    NewTriangle(point1, point2, point3, uv1, uv2, uv3, "", "");

    return 0;
}

static int AddMesh(lua_State *L){
	luaL_checktype(L, 1, LUA_TTABLE);
	
	int meshCount = 0;
	while(1){
		float point[9];
		
		for(int i = 0; i < 3; i++){
			    lua_rawgeti(L, 1, i+(3*meshCount));   //add table to stack (1x3 values)
				if(lua_istable(L, 2) != 1)
					if(meshCount > 0 && i == 1)
						return 0;
					else
						return luaL_error(L, "ERROR: invalid table");
						
				lua_rawgeti(L, 2, 1);   //x_i to stack (3)	//fel!!!
				lua_rawgeti(L, 2, 2);   //y_i to stack (4)
				lua_rawgeti(L, 2, 3);   //z_i to stack (5)
				if(lua_isnumber(L, 3) != 1 && lua_isnumber(L, 4) != 1 && lua_isnumber(L, 5) != 1)
					return luaL_error(L, "ERROR: invalid coordinates");
					
				point[0+(3*i)] = lua_tonumber(L, 3);//fel!!!  //stack spot 3 to point1[0]
				point[1+(3*i)] = lua_tonumber(L, 4);  //stack spot 4 to point1[1]
				point[2+(3*i)] = lua_tonumber(L, 5);  //stack spot 5 to point1[2]
		}
		
		meshCount++;
	}
}

static int AddBox(lua_State *L){   //AddBox({xPos,yPos,zPos}, size, name)
    float coords[3], size;
    std::string name = "";

    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TNUMBER);

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

    lua_rawgeti(L, 1, 4);   //checking number of arguments (7)
    if(lua_isnumber(L, 7) == 1)
        return luaL_error(L, "ERROR: number of components");

    /*std::cout << "   AddBox() coords: ";
    std::cout << coords[0] << " " << coords[1] << " " << coords[2] << std::endl;
    std::cout << "   size: " << size << ", name: " << name << std::endl;*/

    NewBox(size, coords, "", name);

    return 0;   //return 1 (seccessful) / 0 (failed)
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

    lua_rawgeti(L, 1, 1);   //xPos to stack (3)
    lua_rawgeti(L, 1, 2);   //yPos to stack (4)
    lua_rawgeti(L, 1, 3);   //zPos to stack (5)
    if(lua_isnumber(L, 3) != 1 && lua_isnumber(L, 4) != 1 && lua_isnumber(L, 5) != 1)
        return luaL_error(L, "ERROR: invalid coordinates (Pos)");
    pos[0] = lua_tonumber(L, 3);  //stack spot 3 to pos[0]
    pos[1] = lua_tonumber(L, 4);  //stack spot 4 to pos[1]
    pos[2] = lua_tonumber(L, 5);  //stack spot 5 to pos[2]

    lua_rawgeti(L, 2, 1);   //xPos to stack (6)
    lua_rawgeti(L, 2, 2);   //yPos to stack (7)
    lua_rawgeti(L, 2, 3);   //zPos to stack (8)
    if(lua_isnumber(L, 6) != 1 && lua_isnumber(L, 7) != 1 && lua_isnumber(L, 8) != 1)
        return luaL_error(L, "ERROR: invalid coordinates (Look)");
    look[0] = lua_tonumber(L, 6);  //stack spot 3 to pos[0]
    look[1] = lua_tonumber(L, 7);  //stack spot 4 to pos[1]
    look[2] = lua_tonumber(L, 8);  //stack spot 5 to pos[2]

    lua_rawgeti(L, 1, 4);   //checking number of arguments (9)
    lua_rawgeti(L, 2, 4);   //checking number of arguments (10)
    if(lua_isnumber(L, 9) == 1 || lua_isnumber(L, 10) == 1)
        return luaL_error(L, "ERROR: number of components");

    /*std::cout << "   New Pos: ";
    std::cout << pos[0] << " " << pos[1] << " " << pos[2] << std::endl;
    std::cout << "   New Look: ";
    std::cout << look[0] << " " << look[1] << " " << look[2] << std::endl;*/

    camera->setPosition(irr::core::vector3df(pos[0],pos[1],pos[2]));
    camera->setTarget(irr::core::vector3df(look[0],look[1],look[2]));

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

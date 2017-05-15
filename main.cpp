#include <irrlicht.h>

#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <sys/time.h>
#include <unistd.h>

#include "luaFunctions.cpp"
#include "globals.h"

#define STR_SIZE 128

int CreateIrrBase(){
    irrDevice = irr::createDevice( irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(800, 600),
            16, false, false, false, 0);

    driver = irrDevice->getVideoDriver();
    smgr = irrDevice->getSceneManager();
    irrGUIEnv = irrDevice->getGUIEnvironment();

    irrDevice->setWindowCaption(L"Project");

    //-----

    light.resize(light.size()+2);
    light[0] = smgr->addLightSceneNode( 0, irr::core::vector3df(-50.0f,10.0f,0.0f), irr::video::SColorf(1.0f,1.0f,1.0f,1.0f), 500.0f );
    light[1] = smgr->addLightSceneNode( 0, irr::core::vector3df(50.0f,30.0f,0.0f), irr::video::SColorf(1.0f,1.0f,1.0f,1.0f), 500.0f );

    camera = smgr->addCameraSceneNodeFPS(0, 1.0f, 0.5f, -1, 0, 0, false, 0.f, false, true); //parent, rotSpeed, moveSpeed,...
    camera->setPosition(irr::core::vector3df(60,60,10));
    camera->setTarget(irr::core::vector3df(0,0,0));

    return 1;
}

int ReadLuaScript(lua_State* L, int argc, char** argv){
    if(argc > 1){   //main-parameter
        if(luaL_dofile(L, argv[1])){
            printf("error executing lua file");
            return 0;
        }
        else{
            printf("lua file executed");
            return 1;
        }
    }
    return 1;
}

int CreateLuaFunctions(lua_State* L){
    lua_pushcfunction(L, AddMesh);
    lua_setglobal(L, "AddMesh");

    lua_pushcfunction(L, AddBox);
    lua_setglobal(L, "AddBox");

    lua_pushcfunction(L, GetNodes);
    lua_setglobal(L, "GetNodes");

    lua_pushcfunction(L, Camera);
    lua_setglobal(L, "Camera");

    lua_pushcfunction(L, Snapshot);
    lua_setglobal(L, "Snapshot");

    return 1;
}

int CreateForms(){
    {   //1
        name.push_back("box");
        meshnode.resize(meshnode.size()+1);
        meshnode[meshnode.size()-1] = smgr->addCubeSceneNode(
            5,0,1,irr::core::vector3df(0,0,0), irr::core::vector3df(0,0,0),irr::core::vector3df(5,5,5));
        meshnode[meshnode.size()-1]->setMaterialTexture(0, driver->getTexture("red.png"));
    }
    return 1;
}

int main(int argc, char** argv){
    lua_State* L;
    L = luaL_newstate();
    luaL_openlibs(L);

    std::cout << "CreateIrrBase() " << (CreateIrrBase() ? "successful" : "FAILED") << std::endl;

    std::cout << "ReadLuaScript() " << (ReadLuaScript(L, argc, argv) ? "successful" : "FAILED") << std::endl;

    std::cout << "CreateForms() " << (CreateForms() ? "successful" : "FAILED") << std::endl;

    //------------------------

    char str[STR_SIZE]; //lua: create input-string

    timeval time;   //lua: allt select()/read()
    time.tv_usec = 1000000/60;
    time.tv_sec = 0;
    fd_set readset;
    int result = 0;

    //------------------------

    std::cout << "CreateLuaFunctions() " << (CreateLuaFunctions(L) ? "successful" : "FAILED") << std::endl;

    //------------------------

    std::cout << "GameLoop start" << std::endl;

    fflush(stdout);
    printf(">> ");
    fflush(stdout);

    while(irrDevice->run()){
        //Lua
        FD_ZERO(&readset);
        FD_SET(0, &readset);
        result = select(0+1, &readset, NULL, NULL, &time);

        if(result > 0){
            fflush(stdout);
            memset(&str[0], 0, sizeof(str));
            read(0, str, STR_SIZE);
            printf("L: ");

            if(luaL_dostring(L, str)){
                printf("input error");
            }
            memset(&str[0], 0, sizeof(str));
            printf("\n>> ");
            fflush(stdout);
        }

        //------------------------

        //Irrlicht
		driver->beginScene(true, true, irr::video::SColor(255,100,101,140));

        smgr->drawAll();
        irrGUIEnv->drawAll();

        driver->endScene();
    }

    irrDevice->drop();
    return 0;
}
#include <irrlicht.h>

#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>

#include <iostream>
#include <array>
#include <cstring>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <sys/time.h>
#include <unistd.h>

#include "luaFunctions.cpp"
#include "globals.h"
#include "CSampleSceneNode.cpp"

#define STR_SIZE 128

int main(int argc, char** argv){
    lua_State* L;
    L = luaL_newstate();
    luaL_openlibs(L);

    std::cout << "CreateIrrBase() " << (CreateIrrBase() ? "successful" : "FAILED") << std::endl;

    std::cout << "CreateBaseForms() " << (CreateBaseForms() ? "successful" : "FAILED") << std::endl;

    //------------------------

    char str[STR_SIZE]; //lua: create input-string

    timeval time;   //lua: allt select()/read()
    time.tv_usec = 1000000/60;
    time.tv_sec = 0;
    fd_set readset;
    int result = 0;

    //------------------------

    std::cout << "CreateLuaFunctions() " << (CreateLuaFunctions(L) ? "successful" : "FAILED") << std::endl;

    std::cout << "ReadLuaScript() " << (ReadLuaScript(L, argc, argv) ? "successful" : "FAILED") << std::endl;

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
            //printf("L: ");

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

//----- startup:

int CreateIrrBase(){
    irrDevice = irr::createDevice( irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(800, 600),
            16, false, false, false, 0);    //EDT_OPENGL / EDT_BURNINGSVIDEO

    driver = irrDevice->getVideoDriver();
    smgr = irrDevice->getSceneManager();
    irrGUIEnv = irrDevice->getGUIEnvironment();

    irrDevice->setWindowCaption(L"Project");

    //-----

    NewLight(100.0f,-20.0f,30.0f);
    NewLight(-100.0f,-20.0f,30.0f);
    NewLight(0.0f,100.0f,0.0f);
    NewLight(50.0f,20.0f,-50.0f);

    //-----

    camera = smgr->addCameraSceneNodeFPS(0, 1.0f, 0.5f, -1, 0, 0, false, 0.f, false, true); //parent, rotSpeed, moveSpeed,...
    camera->setPosition(irr::core::vector3df(60,60,10));
    camera->setTarget(irr::core::vector3df(0,0,0));

    idTop = 0;

    return 1;
}

int CreateBaseForms(){
    /*int p1[3] = {0,0,0}; int s1[3] = {5,5,5};
    NewBox(5, p1, s1, "project/tex/red.png", "Box1");

    int p2[3] = {0,30,0}; int s2[3] = {2,2,2};
    NewBall(5, p2, s2, "project/tex/mars.jpg", "Ball1");

    int a[3] = {0, 0, 0}; int b[3] = {2, 1, 1}; int c[3] = {0, 1, 3};
    NewTriangle(a, b, c, "", "");
    */

    CSampleSceneNode *myNode =
        new CSampleSceneNode(smgr->getRootSceneNode(), smgr, 666);

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

    lua_pushcfunction(L, AddTexture);
    lua_setglobal(L, "AddTexture");

    return 1;
}

int ReadLuaScript(lua_State* L, int argc, char** argv){
    std::cout << "Lua startup script detected" << std::endl;
    if(argc > 1){   //main-parameter
        if(luaL_dofile(L, argv[1])){
            printf("error executing lua file \n");
            return 0;
        }
        else{
            printf("lua file executed \n");
            return 1;
        }
    }
    return 1;
}

//----- runtime:

int NewLight(float x, float y, float z){
    light.resize(light.size()+1);
    light[light.size()-1] = smgr->addLightSceneNode( 0, irr::core::vector3df(x,y,z), irr::video::SColorf(1.0f,1.0f,1.0f,1.0f), 250.0f );
    return 1;
}

int NewTriangle(int point1[3], int point2[3], int point3[3], irr::io::path texPath, std::string objectName){  //EJ KLAR
    if(objectName == ""){
        objectName = "Triangle" + std::to_string(meshnode.size());  //<-- OBS! kanske inte är "meshnode" som ska användas
    }

    irr::core::aabbox3d<irr::f32> Box;

    irr::video::S3DVertex Vertices[3];
    Vertices[0] = irr::video::S3DVertex(point1[0],point1[1],point1[2], 1,1,0, irr::video::SColor(255,0  ,0  ,255), 1, 0);
    Vertices[1] = irr::video::S3DVertex(point2[0],point2[1],point2[2], 1,0,0, irr::video::SColor(0  ,255,0  ,255), 0, 1);
    Vertices[2] = irr::video::S3DVertex(point3[0],point3[1],point3[2], 0,1,1, irr::video::SColor(0  ,0  ,255,255), 1, 1);

    Box.reset(Vertices[0].Pos);
    for (irr::s32 i=1; i<3; ++i)
        Box.addInternalPoint(Vertices[i].Pos);
}

int NewBox(float size, int pos[3], int scale[3], irr::io::path texPath, std::string objectName){
    if(objectName == ""){
        objectName = "Box" + std::to_string(meshnode.size());
    }
    
    name.push_back(objectName);  //name
    meshnode.resize(meshnode.size()+1); //increase vector size
    meshnode[meshnode.size()-1] = smgr->addCubeSceneNode(
        size,0,(idFreed.size() == 0 ? idTop++ : GetUsedID()),irr::core::vector3df(pos[0], pos[1], pos[2]),irr::core::vector3df(0,0,0),
        irr::core::vector3df(scale[0], scale[1], scale[2]));    //add object

    if(texPath != ""){
        meshnode[meshnode.size()-1]->setMaterialTexture(0, driver->getTexture(texPath));  //add texture to object
    }

    meshnode[meshnode.size()-1]->getMaterial(0).BackfaceCulling = false;    //disable backface culling

    return 1;
}

int NewBall(float size, int pos[3], int scale[3], irr::io::path texPath, std::string objectName){
    if(objectName == ""){
        objectName = "Ball" + std::to_string(meshnode.size());
    }
    
    name.push_back(objectName);  //name
    meshnode.resize(meshnode.size()+1); //increase vector size
    meshnode[meshnode.size()-1] = smgr->addSphereSceneNode(
            size,64,0,(idFreed.size() == 0 ? idTop++ : GetUsedID()),irr::core::vector3df(pos[0],pos[1],pos[2]),
            irr::core::vector3df(0,0,0),irr::core::vector3df(scale[0],scale[1],scale[2]));    //add object

    if(texPath != ""){
        meshnode[meshnode.size()-1]->setMaterialTexture(0, driver->getTexture(texPath));  //add texture to object
    }

    meshnode[meshnode.size()-1]->getMaterial(0).BackfaceCulling = false;    //disable backface culling

    return 1;
}

int NewTexture(float** colors, int size, std::string name){    //EJ KLAR

    return 1;
}

int GetUsedID(){    //KANSKE KLAR
    int returnValue = idFreed.front();
    idFreed.erase(idFreed.begin());
    return returnValue;
}
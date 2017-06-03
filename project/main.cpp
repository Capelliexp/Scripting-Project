#include <irrlicht.h>

#include <lua.hpp>
#include <lua.h>
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
#include "TriangleNode.cpp"

#define STR_SIZE 128

int main(int argc, char** argv){
    lua_State* L;
    L = luaL_newstate();
    luaL_openlibs(L);

    //------------------------

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
        if(captureScene != "" && captureSceneCount == 0)
            ScreenShot(captureScene);
        else
            captureSceneCount = 0;

        //Terminal
        FD_ZERO(&readset);
        FD_SET(0, &readset);
        result = select(0+1, &readset, NULL, NULL, &time);

        if(result > 0){
            fflush(stdout);
            memset(&str[0], 0, sizeof(str));
            read(0, str, STR_SIZE);
            
            //Lua
            if(luaL_dostring(L, str)){
                printf("   INPUT ERROR: ");
                std::cout << lua_tostring(L, 1) << std::endl;
            }
            memset(&str[0], 0, sizeof(str));
            printf("\n>> ");
            fflush(stdout);
        }

        //------------------------

        //Irrlicht
		driver->beginScene(true, true, irr::video::SColor(255,70,70,110));

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

    captureScene = "";
    captureSceneCount = 0;
    idTop = 0;

    return 1;
}

int CreateBaseForms(){
    float p1[3] = {0,0,0};
    NewBox(20, p1, "project/tex/red.png", "BigRedBox");

    int p2[3] = {0,30,0}; int s2[3] = {2,2,2};
    NewBall(5, p2, s2, "project/tex/mars.jpg", "Mars");

    float a[3] = {20, 20, 20}; float b[3] = {50, 20, 20}; float c[3] = {35, 50, 20};
    float uv1[2] = {0,0}; float uv2[2] = {1,0}; float uv3[2] = {0.5, 1};
    NewTriangle(a, b, c, uv1, uv2, uv3, "", "");

    float p3[3] = {0,15,0};
    NewBox(10, p3, "project/tex/blue.png", "");

    /*for(int i = 0; i < name.size(); i++){
        if(name[i] != ""){
            std::cout << "spot: " << i << ", name: " << name[i] << ", type: " << 
                (trianglenode[i] != NULL ? "triangle" : (meshnode[i]->getType() == irr::scene::ESNT_CUBE ? "cube" : "sphere"))
                << std::endl;
        }
    }*/

    return 1;
}

int CreateLuaFunctions(lua_State* L){
    lua_pushcfunction(L, AddMesh);
    lua_setglobal(L, "addMesh");

    lua_pushcfunction(L, AddBox);
    lua_setglobal(L, "addBox");

    lua_pushcfunction(L, GetNodes);
    lua_setglobal(L, "getNodes");

    lua_pushcfunction(L, Camera);
    lua_setglobal(L, "camera");

    lua_pushcfunction(L, Snapshot);
    lua_setglobal(L, "snapshot");

    lua_pushcfunction(L, AddTexture);
    lua_setglobal(L, "addTexture");

    return 1;
}

int ReadLuaScript(lua_State* L, int argc, char** argv){
    std::cout << "Lua startup script detected" << std::endl;
    if(argc > 1){   //main-parameter
        if(luaL_dofile(L, argv[1])){
            printf("error executing lua file \n");
            std::cout << lua_tostring(L, 1) << std::endl;
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

int NewTriangle(float point1[3], float point2[3], float point3[3], float uv1[2], float uv2[2], float uv3[2], irr::io::path texPath, std::string objectName){
    if(objectName == ""){
        objectName = "Triangle" + std::to_string(meshnode.size());  //<-- OBS! kanske inte är "meshnode" som ska användas
    }

    name.push_back(objectName);  //name
    meshnode.resize(meshnode.size()+1); //increase vector size
    trianglenode.resize(trianglenode.size()+1); //increase vector size

    trianglenode[trianglenode.size()-1] = new TriangleNode(point1, point2, point3, uv1, uv2, uv3, smgr->getRootSceneNode(), smgr, (idFreed.size() == 0 ? idTop++ : GetUsedID()));
    
    if(texPath != ""){  //broken
        trianglenode[trianglenode.size()-1]->setMaterialTexture(0, driver->getTexture(texPath));  //add texture to object
    }
}

int NewBox(float size, float pos[3], irr::io::path texPath, std::string objectName){
    if(objectName == ""){
        objectName = "Box" + std::to_string(meshnode.size());
    }
    
    name.push_back(objectName);  //name
    meshnode.resize(meshnode.size()+1); //increase vector size
    trianglenode.resize(trianglenode.size()+1); //increase vector size
    
    meshnode[meshnode.size()-1] = smgr->addCubeSceneNode(
        size,0,(idFreed.size() == 0 ? idTop++ : GetUsedID()),irr::core::vector3df(pos[0], pos[1], pos[2]),irr::core::vector3df(0,0,0),
        irr::core::vector3df(1, 1, 1));    //add object

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
    trianglenode.resize(trianglenode.size()+1); //increase vector size
    
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

int GetID(int i){
    int id = -1;
    if(meshnode[i] != NULL){
        id = meshnode[i]->getID();
    }
    else if(trianglenode[i] != NULL){
        id = trianglenode[i]->GetID();
    }

    return id;
}

int ScreenShot(std::string fileName){
    const char * c = fileName.c_str();

    irr::video::IImage* const image = driver->createScreenShot();
    irr::c8 filename[64];

    snprintf(filename, 64, c);

    driver->writeImageToFile(image, filename);
 
    image->drop();
    captureScene = "";
}
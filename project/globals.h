#ifndef GLOBALS_H
#define GLOBALS_H

#include "TriangleNode.cpp"

//Functions
int CreateIrrBase();
int ReadLuaScript(lua_State* L, int argc, char** argv);
int CreateLuaFunctions(lua_State* L);
int CreateBaseForms();
int NewLight(float x, float y, float z);
int NewTriangle(float point1[3], float point2[3], float point3[3], float uv1[2], float uv2[2], float uv3[2], irr::io::path texPath, std::string name);
int NewBox(float size, float pos[3], irr::io::path texPath, std::string objectName);
int NewBall(float size, int pos[3], int scale[3], irr::io::path texPath, std::string objectName);
int NewTexture(float** colors, int size, std::string name);
int GetUsedID();
int GetID(int i);
int ScreenShot(std::string fileName);

//Irrlicht Handlers
irr::IrrlichtDevice *irrDevice;
irr::video::IVideoDriver* driver;
irr::scene::ISceneManager* smgr;
irr::gui::IGUIEnvironment* irrGUIEnv;

//Irrlicht Base/Scene
irr::scene::ICameraSceneNode* camera;
std::vector<irr::scene::ILightSceneNode*> light;

//Objects
std::vector<std::string> name;
std::vector<irr::scene::IMeshSceneNode*> meshnode;
std::vector<TriangleNode*> trianglenode;

int idTop;
std::vector<int> idFreed;

std::string captureScene;
int captureSceneCount;

#endif
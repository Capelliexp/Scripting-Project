#ifndef GLOBALS_H
#define GLOBALS_H

//Functions
int CreateIrrBase();
int ReadLuaScript(lua_State* L, int argc, char** argv);
int CreateLuaFunctions(lua_State* L);
int CreateForms();
int NewLight(float x, float y, float z);
int NewTriangle(int point1[3], int point2[3], int point3[3], std::string name);
int NewBox(float size, int pos[3], int scale[3], std::string name);
int NewTexture(float** colors, int size, std::string name);
int GetUsedID();

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

int idTop;
std::vector<int> idFreed;

#endif
#ifndef GLOBALS_H
#define GLOBALS_H

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

#endif
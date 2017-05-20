#ifndef CSAMPLESCENENODE_CPP
#define CSAMPLESCENENODE_CPP

#include <irrlicht.h>

using namespace irr;    //ugly, but its 02:00 and im lazy

class CSampleSceneNode : public scene::ISceneNode {
private:
	core::aabbox3d<f32> Box;
    video::S3DVertex Vertices[3];
    video::SMaterial Material;

public:
    CSampleSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
    virtual void OnRegisterSceneNode();
    virtual void render();
	virtual core::aabbox3d<f32>& getBoundingBox();
    virtual u32 getMaterialCount();
    virtual video::SMaterial& getMaterial(u32 i);
};

CSampleSceneNode::CSampleSceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) : scene::ISceneNode(parent, mgr, id){
    Material.Wireframe = false;
    Material.Lighting = false;

    Vertices[0] = video::S3DVertex(0,0,10, 1,1,0,
            video::SColor(255,0,255,255), 0, 1);
    Vertices[1] = video::S3DVertex(10,0,-10, 1,0,0,
            video::SColor(255,255,0,255), 1, 1);
    Vertices[2] = video::S3DVertex(0,20,0, 0,1,1,
            video::SColor(255,255,255,0), 1, 0);
    Box.reset(Vertices[0].Pos);
    for (s32 i=1; i<3; ++i)
        Box.addInternalPoint(Vertices[i].Pos);
}

void CSampleSceneNode::OnRegisterSceneNode(){
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);

    ISceneNode::OnRegisterSceneNode();
}

void CSampleSceneNode::render(){
    u16 indices[] = {   0,2,3, 2,1,3, 1,0,3, 2,0,1  };
    video::IVideoDriver* driver = SceneManager->getVideoDriver();

    driver->setMaterial(Material);
    driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
    driver->drawVertexPrimitiveList(&Vertices[0], 4, &indices[0], 4, video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_16BIT);
}

core::aabbox3d<f32>& CSampleSceneNode::getBoundingBox(){
    return Box;
}

u32 CSampleSceneNode::getMaterialCount(){
    return 1;
}

video::SMaterial& CSampleSceneNode::getMaterial(u32 i){
    return Material;
}

#endif
#ifndef CSAMPLESCENENODE_CPP
#define CSAMPLESCENENODE_CPP

#include <irrlicht.h>

using namespace irr;    //ugly, but its 02:00 and im lazy

class TriangleNode : public scene::ISceneNode {
private:
	core::aabbox3d<f32> Box;
    video::S3DVertex Vertices[4];
    video::SMaterial Material;

public:
    TriangleNode(float point1[3], float point2[3], float point3[3], float uv1[2], float uv2[2], float uv3[2], scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
    virtual void OnRegisterSceneNode();
    virtual void render();
	virtual const core::aabbox3d<f32>& getBoundingBox() const;
    virtual u32 getMaterialCount();
    virtual video::SMaterial& getMaterial(u32 i);
};

TriangleNode::TriangleNode(float point1[3], float point2[3], float point3[3], float uv1[2], float uv2[2], float uv3[2], scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) : scene::ISceneNode(parent, mgr, id){
    Material.Wireframe = false;
    Material.Lighting = false;

    Vertices[0] = video::S3DVertex(point1[0],point1[1],point1[2], 0,0,0, video::SColor(255, 255,0,0), uv1[0], uv1[1]);
    Vertices[1] = video::S3DVertex(point2[0],point2[1],point2[2], 0,0,0, video::SColor(255, 0,255,0), uv2[0], uv2[1]);
    Vertices[2] = video::S3DVertex(point3[0],point3[1],point3[2], 0,0,0, video::SColor(255, 0,0,255), uv3[0], uv3[1]);

    float xValue = point1[0] + (point2[0] - point1[0])/2;
    float yValue = point1[1] + (point2[1] - point1[1])/2;
    float zValue = point1[2] + (point2[2] - point1[2])/2;
    float uValue = uv1[0] + (uv2[0] - uv1[0])/2;
    float vValue = uv1[1] + (uv2[1] - uv1[1])/2;
    Vertices[3] = video::S3DVertex(xValue,yValue,zValue, 0,0,0, video::SColor(255, 127.5,127.5,0), uValue,vValue);

    Box.reset(Vertices[0].Pos);
    for (s32 i=1; i<3; ++i)
        Box.addInternalPoint(Vertices[i].Pos);
}

void TriangleNode::OnRegisterSceneNode(){
    if (IsVisible)
        SceneManager->registerNodeForRendering(this);

    ISceneNode::OnRegisterSceneNode();
}

void TriangleNode::render(){
    u16 indices[] = {   0,2,3, 2,1,3, 1,0,3, 2,0,1  };
    video::IVideoDriver* driver = SceneManager->getVideoDriver();

    driver->setMaterial(Material);
    driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);
    driver->drawVertexPrimitiveList(&Vertices[0], 4, &indices[0], 4, video::EVT_STANDARD, scene::EPT_TRIANGLES, video::EIT_16BIT);
}

const core::aabbox3d<f32>& TriangleNode::getBoundingBox() const{
    return Box;
}

u32 TriangleNode::getMaterialCount(){
    return 1;
}

video::SMaterial& TriangleNode::getMaterial(u32 i){
    return Material;
}

#endif
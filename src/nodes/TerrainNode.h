/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * TerrainNode class definition
 *
 *****************************************************/
 #pragma once
#include <BaseNode.h>
#include <Camera.h>
#include <ofMesh.h>
#include <string>


class TerrainNode : public BaseNode {


private:

    ofMesh m_meshTerrain;
    ofVec3f m_boundingBox;

public:
    explicit TerrainNode(const std::string& p_name);
    int draw(bool p_objectPicking, Camera* p_camera) override;
    ofVec3f getBoundingBox() const override;

};


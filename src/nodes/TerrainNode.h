/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
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
    std::string m_terrainName = "default";
    std::vector<std::string> m_terrainNames;

public:
    explicit TerrainNode(const std::string& p_name);
    std::string getClassName() override { return "TerrainNode"; }
    int draw(bool p_objectPicking, Camera* p_camera) override;
    ofVec3f getBoundingBox() const override;
    void loadTerrain();
    void setTerrainName(const std::string& p_name);
    std::string getTerrainName() const;
    std::vector<NodeProperty> getProperties() const override;
    void setProperty(const std::string &p_name, std::any p_value) override;
    ofMesh* getMesh() override;
};


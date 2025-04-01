/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * PlaneNode class definition
 *
 *****************************************************/
#pragma once
#include <of3dPrimitives.h>

#include "BaseNode.h"

class PlaneNode : public BaseNode {

private:
    ofPlanePrimitive m_primitive;
public:
    explicit PlaneNode(const std::string& p_name);
    std::string getClassName() override { return "PlaneNode"; }
    int draw(bool p_objectPicking, Camera* p_camera) override;
    ofVec3f getBoundingBox() const override;
    void setWidth(float p_width);
    void setHeight(float p_height);
    void setDepth(float p_depth);
    std::vector<NodeProperty> getProperties() const override;
    void setProperty(const std::string &p_name, std::any p_value) override;
    void setResolution(int p_resolution);
    ofMesh* getMesh() override;

};


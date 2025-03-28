/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * ConeNode class definition
 *
 *****************************************************/
#pragma once
#include <of3dPrimitives.h>
#include "BaseNode.h"


class ConeNode : public BaseNode {

private:

    ofConePrimitive m_primitive;


public:
    explicit ConeNode(const std::string& p_name);
    std::string getClassName() override { return "ConeNode"; }
    int draw(bool p_objectPicking, Camera* p_camera) override;
    ofVec3f getBoundingBox() const override;
    void setRadius(float p_radius);
    void setHeight(float p_radius);
    void setResolutionRadius(int p_resolution);
    void setResolutionHeight(int p_resolution);
    std::vector<NodeProperty> getProperties() const override;
    void setProperty(const std::string &p_name, std::any p_value) override;
};

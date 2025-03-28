/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * LightNode class definition
 *
 *****************************************************/
#pragma once
#include <BaseNode.h>
#include <of3dPrimitives.h>


class LightNode : public BaseNode {

private:
    int m_lightIndex;
    ofSpherePrimitive m_sphere;
    ofCylinderPrimitive m_cylinder;
    ofConePrimitive m_cone;

public:
    LightNode(const std::string &p_name, int p_Lightindex);
    std::string getClassName() override { return "LightNode"; }
    int getLightIndex();

    int draw(bool p_objectPicking, Camera *p_camera) override;

    ofVec3f getBoundingBox() const override;

    std::vector<NodeProperty> getProperties() const override;

    void setProperty(const std::string &p_name, std::any p_value) override;
};

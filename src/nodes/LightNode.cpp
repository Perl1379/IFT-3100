/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * LightNode class implementation
 *
 *****************************************************/
#include "LightNode.h"

#include <Global.h>
#include <LightSource.h>


/**
 * Constructor
 */
LightNode::LightNode(const std::string &p_name, int p_Lightindex) : BaseNode(p_name) {
    m_lightIndex = p_Lightindex;

    m_sphere.setRadius(125);
    m_sphere.setResolution(16.0);
    m_sphere.setPosition(0, 0, 0);

    m_cone.setRadius(100);
    m_cone.setHeight(250);
    m_cone.setResolution(16,8,8);
    m_cone.setPosition(0, 0, 0);
    m_cone.setOrientation(glm::vec3(-90, 0, 0.0));

    m_cylinder.setRadius(100);
    m_cylinder.setHeight(250);
    m_cylinder.setResolution(16, 8, 8);
    m_cylinder.setPosition(0, 0, 0);
    m_cylinder.setOrientation(glm::vec3(-90, 0, 0));

}


/**
 * draw nothing
 */
int LightNode::draw(bool p_objectPicking, Camera *p_camera) {

    // sync light and node attributes
    m_transform.setPosition(Global::m_lights[m_lightIndex].getPosition());
    m_transform.setOrientation(Global::m_lights[m_lightIndex].getOrientation());
    m_transform.setScale(Global::m_lights[m_lightIndex].getScale());

    if (!m_displayBoundingBox) return 0;

    if (p_camera->getLightModel() != OPENGL_LIGHTS) {
        p_camera->getLightShader()->end();
    }

    if (Global::m_lights[m_lightIndex].getEnabled()) {
        ofSetColor(255, 255, 255);
    } else {
        ofSetColor(32,32,32);
    }

    m_transform.transformGL();
    switch(Global::m_lights[m_lightIndex].getLightType()) {
        case SPOT_LIGHT:
            m_cone.draw();
        break;
        case DIRECTIONAL_LIGHT:
            m_cylinder.draw();
        break;
        default:
            m_sphere.draw();
        break;
    }


    m_transform.restoreTransformGL();

    if (p_camera->getLightModel() != OPENGL_LIGHTS) {
        p_camera->getLightShader()->begin();
    }

    return 1;

}


/**
 * Default bounding box
 */
ofVec3f LightNode::getBoundingBox() const {
    return ofVec3f(500, 500, 500);
}


/**
 * Return light index
 */
int LightNode::getLightIndex() {
    return m_lightIndex;
}


/**
 * Get properties
 */
std::vector<NodeProperty> LightNode::getProperties() const {

    vector<NodeProperty> properties;

    LightSource* light = &Global::m_lights[m_lightIndex];
    properties.emplace_back("Transform", PROPERTY_TYPE::LABEL, nullptr);
    properties.emplace_back("Position", PROPERTY_TYPE::VECTOR3, m_transform.getPosition());
    properties.emplace_back("Orientation", PROPERTY_TYPE::VECTOR3, m_transform.getOrientationEulerDeg());
    properties.emplace_back("Scale", PROPERTY_TYPE::VECTOR3, m_transform.getScale());

    properties.emplace_back("Light parameters", PROPERTY_TYPE::LABEL, nullptr);
    properties.emplace_back("Enabled", PROPERTY_TYPE::BOOLEAN_FIELD, light->getEnabled());

    std::vector<std::string> lightTypes;
    lightTypes.push_back("Spotlight");
    lightTypes.push_back("Point");
    lightTypes.push_back("Directional");
    lightTypes.push_back(std::to_string(Global::m_lights[m_lightIndex].getLightType()));

    properties.emplace_back("Light Type", PROPERTY_TYPE::ITEM_LIST, lightTypes);

    properties.emplace_back("Ambient Color", COLOR_PICKER, light->getColorAmbient());
    properties.emplace_back("Diffuse Color", COLOR_PICKER, light->getColorDiffuse());
    properties.emplace_back("Specular Color", COLOR_PICKER, light->getColorSpecular());
    properties.emplace_back("Attenuation", PRECISE_FLOAT_FIELD, light->getAttenuation());

    std::vector<std::string> cameras;
    cameras.push_back("No"); // -1
    cameras.push_back("Camera #1"); // 0
    cameras.push_back("Camera #2"); // 1
    cameras.push_back("Camera #3"); // 2
    cameras.push_back(std::to_string(Global::m_lights[m_lightIndex].getCameraBind()+1));
    properties.emplace_back("Bind to Camera", ITEM_LIST, cameras);
    return properties;
}


/**
 * Set property
 */
void LightNode::setProperty(const std::string &p_name, std::any p_value) {
    LightSource *light = &Global::m_lights[m_lightIndex];

    if (p_name == "Bind to Camera") {
        light->setCameraBind(static_cast<int>(std::any_cast<int>(p_value)-1));
        return;
    }

    if (p_name == "Light Type") {
        light->setLightType(static_cast<LIGHT_TYPE>(std::any_cast<int>(p_value)));
        return;
    }

    if (p_name == "Enabled") {
        light->setEnabled(std::any_cast<bool>(p_value));
        return;
    }

    if (p_name == "Position") {
        m_transform.setPosition(std::any_cast<glm::vec3>(p_value));
        light->setPosition(std::any_cast<glm::vec3>(p_value));
        return;
    }

    if (p_name == "Orientation") {
        m_transform.setOrientation(std::any_cast<glm::vec3>(p_value));
        light->setOrientation(std::any_cast<glm::vec3>(p_value));
        return;
    }

    if (p_name == "Scale") {
        m_transform.setScale(std::any_cast<glm::vec3>(p_value));
        light->setScale(std::any_cast<glm::vec3>(p_value));
        return;
    }

    if (p_name == "Attenuation") {
        light->setAttenuation(std::any_cast<float>(p_value));
        return;
    }

    if (p_name == "Ambient Color") {
        light->setColorAmbient(std::any_cast<ofFloatColor>(p_value));
        return;
    }

    if (p_name == "Diffuse Color") {
        light->setColorDiffuse(std::any_cast<ofFloatColor>(p_value));
        return;
    }

    if (p_name == "Specular Color") {
        light->setColorSpecular(std::any_cast<ofFloatColor>(p_value));
    }

}

/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * ConeNode class implementation
 *
 *****************************************************/
#include "ConeNode.h"
#include <Global.h>
#include <of3dGraphics.h>
#include <ofLight.h>


/**
 * Constructor
 */
ConeNode::ConeNode(const std::string& p_name) : BaseNode(p_name) {
    m_primitive.setRadius(50.0);
    m_primitive.setHeight(200.0);
    m_primitive.setPosition(0, 0, 0);
    m_primitive.setResolutionRadius(24);
    m_primitive.setResolutionHeight(3);
}


/**
 * Draw node content
 */
int ConeNode::draw(bool p_objectPicking, Camera* p_camera) {
    if (!m_displayNode) return 0;
    int count = 0;

    beginDraw(p_objectPicking, p_camera);
    if (p_camera->testVisibility(m_transform.getGlobalPosition(),
        getBoundingBox() * m_transform.getGlobalScale())) {
        m_transform.transformGL();
        m_primitive.draw();
        m_transform.restoreTransformGL();
        count++;
    }

    count += endDraw(p_objectPicking, p_camera);
    return count;
}


/**
 * Set cone radius
 */
void ConeNode::setRadius(float p_radius) {
    m_primitive.setRadius(p_radius);
}


/**
 * Set cone height
 */
void ConeNode::setHeight(float p_height) {
    m_primitive.setHeight(p_height);
}


/**
 * Get bounding box
 */
ofVec3f ConeNode::getBoundingBox() const {
    return {m_primitive.getRadius() * 2.0f, m_primitive.getHeight(), m_primitive.getRadius() * 2.0f};
}


/**
 * Get properties
 */
std::vector<NodeProperty> ConeNode::getProperties() const {
    auto properties = BaseNode::getProperties();
    properties.emplace_back("Cone parameters", PROPERTY_TYPE::LABEL, nullptr);
    properties.emplace_back("Radius", PROPERTY_TYPE::FLOAT_FIELD, m_primitive.getRadius());
    properties.emplace_back("Height", PROPERTY_TYPE::FLOAT_FIELD, m_primitive.getHeight());
    properties.emplace_back("Resolution R", PROPERTY_TYPE::INT_FIELD, m_primitive.getResolutionRadius());
    properties.emplace_back("Resolution H", PROPERTY_TYPE::INT_FIELD, m_primitive.getResolutionHeight());
    return properties;
}


/**
 * Set property
 */
void ConeNode::setProperty(const std::string &p_name, std::any p_value) {
    if (p_name == "Radius") {
        m_primitive.setRadius(std::any_cast<float>(p_value));
        return;
    }

    if (p_name == "Height") {
        m_primitive.setHeight(std::any_cast<float>(p_value));
        return;
    }

    if (p_name == "Resolution R") {
        m_primitive.setResolutionRadius(std::any_cast<int>(p_value));
        return;
    }

    if (p_name == "Resolution H") {
        m_primitive.setResolutionHeight(std::any_cast<int>(p_value));
        return;
    }

    BaseNode::setProperty(p_name, std::any(p_value));
}


/**
 * Set resolution (radius)
 */
void ConeNode::setResolutionRadius(int p_resolution) {
    m_primitive.setResolutionRadius(p_resolution);
}


/**
 * Set resolution (height)
 */
void ConeNode::setResolutionHeight(int p_resolution) {
    m_primitive.setResolutionHeight(p_resolution);
}


/**
 * Get mesh
 */
ofMesh* ConeNode::getMesh() {
    return &m_primitive.getMesh();
}
/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * BoxNode class implementation
 *
 *****************************************************/
#include "BoxNode.h"

#include <Global.h>
#include <of3dGraphics.h>
#include <ofLight.h>


/**
 * Constructor
 */
BoxNode::BoxNode(const std::string &p_name) : BaseNode(p_name) {
    m_primitive.setWidth(10.0f);
    m_primitive.setHeight(10.0f);
    m_primitive.setDepth(10.0f);
    m_primitive.setPosition(0, 0, 0);
}


/**
 * Draw node content
 */
void BoxNode::draw(bool p_objectPicking) {
    beginDraw(p_objectPicking);
    m_transform.transformGL();
    m_primitive.draw();
    m_transform.restoreTransformGL();
    endDraw(p_objectPicking);
}


/**
 * Set box width
 */
void BoxNode::setWidth(float p_width) {
    m_primitive.setWidth(p_width);
}


/**
 * Set box height
 */
void BoxNode::setHeight(float p_height) {
    m_primitive.setWidth(p_height);
}


/**
 * Set box depth
 */
void BoxNode::setDepth(float p_depth) {
    m_primitive.setWidth(p_depth);
}


/**
 * Get bounding box
 */
ofVec3f BoxNode::getBoundingBox() const {
    return {
        m_primitive.getWidth(), m_primitive.getHeight(), m_primitive.getDepth()
    };
}

/**
 * Get properties
 */
std::vector<NodeProperty> BoxNode::getProperties() const {
    auto properties = BaseNode::getProperties();
    properties.emplace_back("Width", PROPERTY_TYPE::FLOAT_TYPE, m_primitive.getWidth());
    properties.emplace_back("Height", PROPERTY_TYPE::FLOAT_TYPE, m_primitive.getHeight());
    properties.emplace_back("Depth", PROPERTY_TYPE::FLOAT_TYPE, m_primitive.getDepth());
    properties.emplace_back("Resolution", PROPERTY_TYPE::INTEGER, static_cast<int>(m_primitive.getResolution().x));
    return properties;
}

/**
 * Set property
 */
void BoxNode::setProperty(const std::string &p_name, std::any p_value) {

    if (p_name == "Width") {
        m_primitive.setWidth(std::any_cast<float>(p_value));
        return;
    }

    if (p_name == "Height") {
        m_primitive.setHeight(std::any_cast<float>(p_value));
        return;
    }

    if (p_name == "Depth") {
        m_primitive.setDepth(std::any_cast<float>(p_value));
        return;
    }

    if (p_name == "Resolution") {
        m_primitive.setResolutionWidth(std::any_cast<int>(p_value));
        m_primitive.setResolutionHeight(std::any_cast<int>(p_value));
        m_primitive.setResolutionDepth(std::any_cast<int>(p_value));
    }

    BaseNode::setProperty(p_name, std::any(p_value));
}


/**
 * Set resolution
 */
void BoxNode::setResolution(int p_resolution) {
    m_primitive.setResolution(p_resolution);
}

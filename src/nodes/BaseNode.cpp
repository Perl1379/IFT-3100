/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * BaseNode class implementation
 *
 *****************************************************/
#include "BaseNode.h"
#include <of3dGraphics.h>


/**
 * Constructor
 */
BaseNode::BaseNode() {
    m_primitive.setRadius(10.0);
    m_primitive.setResolution(16.0);
    m_primitive.setPosition(0, 0, 0);
}


/**
 * Draw node content
 */
void BaseNode::draw() {

    m_transform.transformGL();
    m_primitive.draw();

    for (BaseNode* child : m_children) {
        child->draw();
    }

    m_transform.restoreTransformGL();

}


/**
 * Add child node
 */
void BaseNode::addChild(BaseNode *child) {

    child->m_transform.setParent(m_transform);
    m_children.push_back(child);
}

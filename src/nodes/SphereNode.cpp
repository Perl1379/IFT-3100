/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * SphereNode class implementation
 *
 *****************************************************/
#include "SphereNode.h"

#include <Global.h>
#include <of3dGraphics.h>
#include <ofGraphics.h>
#include <ofLight.h>


/**
 * Constructor
 */
SphereNode::SphereNode(const std::string& p_name) : BaseNode(p_name) {
 m_primitive.setRadius(10.0);
 m_primitive.setResolution(16.0);
 m_primitive.setPosition(0, 0, 0);
}


/**
 * Draw node content
 */
void SphereNode::draw(bool objectPicking) {

 m_transform.transformGL();

 if (!objectPicking) {
  m_materialNode.begin();
 } else {
  ofSetColor(Global::idToColor(m_id));
 }

 m_primitive.draw();

 if (!objectPicking) {
  m_materialNode.end();

  if (m_displayBoundingBox) {
   float size = m_primitive.getRadius() * 2.0f;
   m_materialBoundingBox.begin();
   ofNoFill();

   ofDrawBox(m_primitive.getGlobalPosition(), size, size, size);
   m_materialBoundingBox.end();
  }
 }

 for (BaseNode* child : m_children) {
  child->draw(objectPicking);
 }

 m_transform.restoreTransformGL();

}


/**
* Set sphere radius
*/
void SphereNode::setRadius(float radius) {
  m_primitive.setRadius(radius);
}


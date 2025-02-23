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
void SphereNode::draw(bool p_objectPicking) {

	beginDraw(p_objectPicking);
	m_transform.transformGL();
	m_primitive.draw();
	m_transform.restoreTransformGL();
	endDraw(p_objectPicking);

}


/**
 * Set sphere radius
 */
void SphereNode::setRadius(float p_radius) {
	m_primitive.setRadius(p_radius);
}


/**
 * Get bounding box
 */
ofVec3f SphereNode::getBoundingBox() {
	const float size = m_primitive.getRadius() * 2.0f;
	return {size, size, size};
}
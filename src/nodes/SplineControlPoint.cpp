/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * SplineControlPoint class implementation
 *
 *****************************************************/
#include "SplineControlPoint.h"
#include "Global.h"
#include <sstream>

SplineControlPoint::SplineControlPoint(const std::string& p_name, const glm::vec3& p_pos)
	: SphereNode(p_name, 50.0f)
{
	m_displayNode = false;
	setPosition(p_pos);
	m_transformScale = false;
	m_transformRotation = false;
}

SplineControlPoint::~SplineControlPoint() 
{
	getParent()->nodeChanged("Deleted", m_index);
}


std::vector<NodeProperty> SplineControlPoint::getProperties() const 
{
	std::stringstream axisTransfoData;
	std::stringstream otherTransfoData;
	otherTransfoData << "Translation: " << getTransfoAllowed(m_transformTranslation) << std::endl << "Rotation: " << getTransfoAllowed(m_transformRotation) << std::endl << "Scale: " << getTransfoAllowed(m_transformScale);
	axisTransfoData << "X: " << getTransfoAllowed(m_axisTransformX) << std::endl << "Y: " << getTransfoAllowed(m_axisTransformY) << std::endl << "Z: " << getTransfoAllowed(m_axisTransformZ);

	std::vector<NodeProperty> properties;
	properties.emplace_back("Name", PROPERTY_TYPE::TEXT_FIELD, m_name);
	properties.emplace_back("Display", PROPERTY_TYPE::BOOLEAN_FIELD, m_displayNode, Global::m_tooltipMessages.node_display);
	properties.emplace_back("Index", PROPERTY_TYPE::TEXT_INFO, std::to_string(m_index), Global::m_tooltipMessages.spline_pointIndex);
	properties.emplace_back("Transform", PROPERTY_TYPE::LABEL, nullptr);
	properties.emplace_back("Axis transf.", PROPERTY_TYPE::TEXT_INFO, otherTransfoData.str(), "Shows which transformations are allowed.");
	properties.emplace_back("Axis transl.", PROPERTY_TYPE::TEXT_INFO, axisTransfoData.str(), "Shows which transformations are allowed.");
	properties.emplace_back("Position", PROPERTY_TYPE::VECTOR3, m_transform.getPosition());

	return properties;
}

std::string SplineControlPoint::getTransfoAllowed(bool p_value) const {
	return p_value ? "allowed" : "blocked";
}

/**
* Set property from editor
*/
void SplineControlPoint::setProperty(const std::string& p_name, std::any p_value) 
{
	if (p_name == "Position") {
		m_transform.setPosition(std::any_cast<glm::vec3>(p_value));
		getParent()->nodeChanged(p_name, p_value);
		return;
	}
	BaseNode::setProperty(p_name, p_value);
}

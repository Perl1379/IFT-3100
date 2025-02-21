/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * BaseNode class implementation
 *
 *****************************************************/
#include "BaseNode.h"


 /**
  * Constructor
  */
BaseNode::BaseNode(const std::string& p_name) : m_name(p_name) {

	static int id_next = 1;
	m_id = id_next++;
	m_materialBoundingBox.setEmissiveColor(ofFloatColor(1.0, 0.0, 0.0)); // Full red emission
	m_materialBoundingBox.setAmbientColor(ofFloatColor(1.0, 0.0, 0.0));  // Red base color
	m_materialBoundingBox.setDiffuseColor(ofFloatColor(0.0));            // No diffuse
	m_materialBoundingBox.setSpecularColor(ofFloatColor(0.0));           // No specular
	m_materialNode.setShininess(100);  // Controls specular reflection
	m_materialNode.setSpecularColor(ofColor(255, 255, 255));  // Highlights

}


/**
 * Draw node content
 */
void BaseNode::draw(bool objectPicking) {

	m_transform.transformGL();

	for (BaseNode* child : m_children) {
		child->draw(objectPicking);
	}

	m_transform.restoreTransformGL();

}


/**
* Retrieve unique ID associated to the node
*/
int BaseNode::getId() const {
	return m_id;
}


/**
* Toggle display of a red bounding box, drawing is honored in draw function
*/
void BaseNode::displayBoundingBox(bool display) {
	m_displayBoundingBox = display;
}


/**
 * Add child node
 */
void BaseNode::addChild(BaseNode* p_child) {

	m_children.push_back(p_child);
}


/**
 * Reveal properties to the editor
 */
std::vector<NodeProperty> BaseNode::getProperties() const {

	std::vector<NodeProperty> properties;
	properties.emplace_back("Name", PROPERTY_TYPE::TEXT_FIELD, m_name);
	properties.emplace_back("Transform", PROPERTY_TYPE::LABEL, nullptr);
	properties.emplace_back("Position", PROPERTY_TYPE::VECTOR3, m_transform.getPosition());
	properties.emplace_back("Orientation", PROPERTY_TYPE::VECTOR3, m_transform.getOrientationEulerDeg());
	properties.emplace_back("Scale", PROPERTY_TYPE::VECTOR3, m_transform.getScale());
	properties.emplace_back("Material", PROPERTY_TYPE::LABEL, nullptr);
	properties.emplace_back("Diffuse Color", PROPERTY_TYPE::COLOR_PICKER, m_materialNode.getDiffuseColor());
	properties.emplace_back("Ambient Color", PROPERTY_TYPE::COLOR_PICKER, m_materialNode.getAmbientColor());
	properties.emplace_back("Emissive Color", PROPERTY_TYPE::COLOR_PICKER, m_materialNode.getEmissiveColor());
	properties.emplace_back("Specular Color", PROPERTY_TYPE::COLOR_PICKER, m_materialNode.getSpecularColor());

	return properties;

}


/**
* Set property from editor
*/
void BaseNode::setProperty(const std::string& p_name, std::any p_value) {
	if (p_name == "Name") {
		m_name = std::any_cast<std::string>(p_value);
	}

	if (p_name == "Position") {
		m_transform.setPosition(std::any_cast<glm::vec3>(p_value));
	}

	if (p_name == "Orientation") {
		m_transform.setOrientation(std::any_cast<glm::vec3>(p_value));
	}

	if (p_name == "Scale") {
		ofLog() << "Scale:" << std::any_cast<glm::vec3>(p_value).x;
		m_transform.setScale(std::any_cast<glm::vec3>(p_value));
	}

	if (p_name == "Diffuse Color") {
		m_materialNode.setDiffuseColor(std::any_cast<ofFloatColor>(p_value));
	}

	if (p_name == "Ambient Color") {
		m_materialNode.setAmbientColor(std::any_cast<ofFloatColor>(p_value));
	}

	if (p_name == "Emissive Color") {
		m_materialNode.setEmissiveColor(std::any_cast<ofFloatColor>(p_value));
	}

	if (p_name == "Specular Color") {
		m_materialNode.setSpecularColor(std::any_cast<ofFloatColor>(p_value));
	}
}



/**
* Find node (recursive search) by ID
*/
BaseNode* BaseNode::findNode(int p_id) {
	if (p_id == m_id) return this;
	for (BaseNode* child : m_children) {
		BaseNode* result = child->findNode(p_id);
		if (result != nullptr) return result;
	}

	return nullptr;
}


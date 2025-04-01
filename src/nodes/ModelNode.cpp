/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * ModelNode class implementation
 *
 *****************************************************/

#include "ModelNode.h"

 /**
  * Constructor
  * in:
  * p_nodeName: the name of the node, for example "Barbarian"
  * p_fileBaseName: the base name of the model's file, for example "Barbarian".
  * The path will be constructed by the ModelManager from p_fileBaseName
  */
ModelNode::ModelNode(const std::string& p_nodeName, const std::string& p_fileBaseName, MODEL_TYPE p_modelType)
	: BaseNode(p_nodeName), m_modelType(p_modelType)
{
	updateModel(p_fileBaseName);
}


/**
 * Update data on initialization or after a user changed a property
 */
void ModelNode::updateModel(int p_modelNo) {
	m_modelNo = p_modelNo;
	m_fileBaseName = Global::m_modelManager.getModelName(p_modelNo, m_modelType);
	loadModel(Global::m_modelManager.getModelPath(p_modelNo, m_modelType));
}


void ModelNode::updateModel(const std::string& p_modelName) {
	m_modelNo = Global::m_modelManager.getModelNo(p_modelName, m_modelType);
	m_fileBaseName = p_modelName;
	loadModel(Global::m_modelManager.getModelPath(p_modelName, m_modelType));
}


void ModelNode::loadModel(const std::string& p_filePath) {
	//m_filePath = p_filePath;
	m_model.load(p_filePath);
	m_model.setRotation(0, 180, 1, 0, 0);
}


/**
 * Get ModelNode's properties list
 */
std::vector<NodeProperty> ModelNode::getProperties() const
{
	std::vector<NodeProperty> properties;
	//base properties
	properties.emplace_back("Name", PROPERTY_TYPE::TEXT_FIELD, m_name);
	properties.emplace_back("Display", PROPERTY_TYPE::BOOLEAN_FIELD, m_displayNode, Global::m_tooltipMessages.node_display);
	properties.emplace_back("Transform", PROPERTY_TYPE::LABEL, nullptr);
	properties.emplace_back("Position", PROPERTY_TYPE::VECTOR3, m_transform.getPosition());
	properties.emplace_back("Orientation", PROPERTY_TYPE::VECTOR3, m_transform.getOrientationEulerDeg());
	properties.emplace_back("Scale", PROPERTY_TYPE::VECTOR3, m_transform.getScale());

	//no material property for models

	//model property
	properties.emplace_back("Model parameters", PROPERTY_TYPE::LABEL, nullptr);
	properties.emplace_back("Model", PROPERTY_TYPE::ITEM_CLIST, std::make_pair(m_modelNo, Global::m_modelManager.getCNames(m_modelType)), Global::m_tooltipMessages.node_model);

	return properties;
}


/**
 * A user changed a property
 */
void ModelNode::setProperty(const std::string& p_name, std::any p_value)
{
	if (p_name == "Model") {
		m_model.clear();
		updateModel(std::any_cast<int>(p_value));
		return;
	}
	BaseNode::setProperty(p_name, p_value);
}


/**
 * Set the position without going through the model
 */
void ModelNode::setPosition(ofVec3f p_pos)
{
	m_transform.setPosition(p_pos.x, p_pos.y, p_pos.z);
	//m_model.setPosition(p_pos.x, p_pos.y, p_pos.z);
}
void ModelNode::setPosition(float p_x, float p_y, float p_z)
{
	m_transform.setPosition(p_x, p_y, p_z);
	//m_model.setPosition(p_x, p_y, p_z);
}


/**
 * Draw the thing
 */
int ModelNode::draw(bool p_objectPicking, Camera* p_camera)
{
	if (!getDisplayNode()) return 0; //nothing to draw if the user hid the node

	int count = 0;
	beginDraw(p_objectPicking);
	updateBoundingBox();

	if (p_camera->testVisibility(m_transform.getGlobalPosition(), getBoundingBox() * m_transform.getGlobalScale())) {
		m_transform.transformGL();
		if (p_objectPicking) {
			m_model.disableMaterials();
			m_model.disableNormals();
			m_model.disableTextures();
		}

		m_model.drawFaces();

		if (p_objectPicking) {
			m_model.enableMaterials();
			m_model.enableNormals();
			m_model.enableTextures();
		}

		m_transform.restoreTransformGL();
		count++;
	}

	count += endDraw(p_objectPicking, p_camera);
	return count;
}


/**
 * End draw context
 */
int ModelNode::endDraw(bool p_objectPicking, Camera* p_camera)
{
	int count = 0;
	if (!p_objectPicking) {
		m_materialNode.end();

		if (m_displayBoundingBox) {
			m_materialUnlit.begin();
			drawBoundingBox();
			m_materialUnlit.end();
		}
	}

	for (BaseNode* child : m_children) {
		count += child->draw(p_objectPicking, p_camera);
	}
	return count;
}


/**
 * Get bounding box for current node
 * m_model's getters cannot be used in a const function, hence the private version
 */
ofVec3f ModelNode::getBoundingBox() const
{
	return m_bounds;
}
void ModelNode::updateBoundingBox()
{
	m_bounds = m_model.getSceneMaxModelSpace() - m_model.getSceneMinModelSpace();
}


/**
 * Draw bounding box
 */
void ModelNode::drawBoundingBox() {
	ofVec3f boundingBox = getBoundingBox();
	ofNoFill();
	m_transform.transformGL();
	ofDrawBox(m_model.getSceneCenterModelSpace(), boundingBox.x, boundingBox.y, boundingBox.z);
	m_transform.restoreTransformGL();
}


/**
 * Get the model
 */
ofxCustomAssimpModelLoader& ModelNode::getModel()
{
	return m_model;
}


/**
 * Remove some characters from string names
 */
std::string ModelNode::makePlayerFacingName(const std::string& p_name)
{
	std::string playerFacingName = p_name;
	if (playerFacingName.size() != 0)
	{
		std::replace(playerFacingName.begin(), playerFacingName.end(), '_', ' ');
	}
	return playerFacingName;
}


/**
 * Destructor
 */
ModelNode::~ModelNode()
{
	//todo
}



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
  */
ModelNode::ModelNode(const std::string& p_name, const std::string& p_filePath) : BaseNode(p_name) {
	// 1 - load the model
	m_model.loadModel(p_filePath);
	m_model.setRotation(0, 180, 1, 0, 0);

	// 2- setup animations
	initHardcodedList();
	initAnimationsList();
	setLoopingState(true);
	m_previousAnimID = 0;
	setCurrentAnimation(getCurrentAnimationID());

	//debugPrintNames();
	
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
	int count = 0;
	beginDraw(p_objectPicking);
	updateBoundingBox();

	if (p_camera->testVisibility(m_transform.getGlobalPosition(), getBoundingBox())) {
		m_transform.transformGL();
		if (m_playAnimation)
		{
			m_model.update();
		}
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
 * Get ModelNode's properties list
 */
std::vector<NodeProperty> ModelNode::getProperties() const
{

	std::vector<NodeProperty> properties;
	properties.emplace_back("Name", PROPERTY_TYPE::TEXT_FIELD, m_name);
	properties.emplace_back("Display", PROPERTY_TYPE::BOOLEAN_FIELD, m_displayNode, Global::m_tooltipMessages.node_display);
	properties.emplace_back("Transform", PROPERTY_TYPE::LABEL, nullptr);
	properties.emplace_back("Position", PROPERTY_TYPE::VECTOR3, m_transform.getPosition());
	properties.emplace_back("Orientation", PROPERTY_TYPE::VECTOR3, m_transform.getOrientationEulerDeg());
	properties.emplace_back("Scale", PROPERTY_TYPE::VECTOR3, m_transform.getScale());
	//no material property

	properties.emplace_back("Animation parameters", PROPERTY_TYPE::LABEL, nullptr);
	properties.emplace_back("Play", PROPERTY_TYPE::BOOLEAN_FIELD, m_playAnimation, Global::m_tooltipMessages.node_playAnimation);
	properties.emplace_back("Loop", PROPERTY_TYPE::BOOLEAN_FIELD, m_loopAnimation, Global::m_tooltipMessages.node_loopAnimation);
	properties.emplace_back("Animation", PROPERTY_TYPE::ITEM_LIST, (m_showAllAnimations) ? m_animNamesFull : m_animNamesRestricted);
	properties.emplace_back("Show all", PROPERTY_TYPE::BOOLEAN_FIELD, m_showAllAnimations, Global::m_tooltipMessages.node_showAllAnimation);

	//TODO dropdown list for animations and a tick box for the loop param

	return properties;
}


/**
 * A user changed a property
 */
void ModelNode::setProperty(const std::string& p_name, std::any p_value)
{
	if (p_name == "Play") {
		m_playAnimation = std::any_cast<bool>(p_value);
		return;
	}
	if (p_name == "Loop") {
		m_loopAnimation = std::any_cast<bool>(p_value);
		return;

	}
	if (p_name == "Animation") {
		if (m_showAllAnimations)
		{
			setCurrentAnimation(std::any_cast<int>(p_value));
		}
		else
		{
			setCurrentAnimation(getAnimFromRestricted(std::any_cast<int>(p_value)));
		}
		return;
	}
	if (p_name == "Show all") {
		m_showAllAnimations = std::any_cast<bool>(p_value);
		return;
	}

	BaseNode::setProperty(p_name, p_value);
}


/**
 * Get the animation's name
 */
std::string ModelNode::getCurrentAnimationName() const
{
	return getCurrentAnimation()->m_playerFacingName;
}


/**
 * Get the model
 */
ofxAssimpModelLoader& ModelNode::getModel()
{
	return m_model;
}


/**
 * Destructor
 */
ModelNode::~ModelNode()
{
}


/**
 * Prepare animations for use
 */
void ModelNode::initAnimationsList()
{
	bool addAnimation = true;
	std::string animName;
	for (unsigned int i = 0; i < m_model.getAnimationCount(); i++, addAnimation = true)
	{
		for (auto anim : m_animations)
		{
			if (anim->m_devName == m_model.getAnimation(i).getAnimation()->mName.data)
			{
				addAnimation = false;
				break;
			}
		}
		if (addAnimation)
		{
			animName = m_model.getAnimation(i).getAnimation()->mName.data;
			ModelNodeAnimationData* animData = new ModelNodeAnimationData(i, animName, makePlayerFacingName(animName));
			m_animations.push_back(animData);
		}
	}
	m_currentAnimID = getAnimFromRestricted(stoi(m_animNamesRestricted.back()));

}


/**
 * I hate this so much (hardcoded names)
 */
void ModelNode::initHardcodedList()
{
	// Partial list
	m_animNamesRestricted.push_back(makePlayerFacingName("2H_Melee_Idle"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Cheer"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Death_A_Pose"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Death_B_Pose"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Idle"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Lie_Idle"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Lie_Pose"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Running_A"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Running_B"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Sit_Chair_Idle"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Sit_Chair_Pose"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Sit_Floor_Idle"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Sit_Floor_Pose"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Spellcasting"));
	m_animNamesRestricted.push_back(makePlayerFacingName("T-Pose"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Unarmed_Idle"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Unarmed_Pose"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Walking_A"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Walking_B"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Walking_Backwards"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Walking_C"));
	m_animNamesRestricted.push_back(m_DEFAULT_RESTRICTED_ANIM);
	//Recording the position at the back makes it easier to deal with this list everywhere

	// Full list
	m_animNamesFull.push_back(makePlayerFacingName("1H_Melee_Attack_Chop"));
	m_animNamesFull.push_back(makePlayerFacingName("1H_Melee_Attack_Slice_Diagonal"));
	m_animNamesFull.push_back(makePlayerFacingName("1H_Melee_Attack_Slice_Horizontal"));
	m_animNamesFull.push_back(makePlayerFacingName("1H_Melee_Attack_Stab"));
	m_animNamesFull.push_back(makePlayerFacingName("1H_Ranged_Aiming"));
	m_animNamesFull.push_back(makePlayerFacingName("1H_Ranged_Reload"));
	m_animNamesFull.push_back(makePlayerFacingName("1H_Ranged_Shoot"));
	m_animNamesFull.push_back(makePlayerFacingName("1H_Ranged_Shooting"));
	m_animNamesFull.push_back(makePlayerFacingName("2H_Melee_Attack_Chop"));
	m_animNamesFull.push_back(makePlayerFacingName("2H_Melee_Attack_Slice"));
	m_animNamesFull.push_back(makePlayerFacingName("2H_Melee_Attack_Spin"));
	m_animNamesFull.push_back(makePlayerFacingName("2H_Melee_Attack_Spinning"));
	m_animNamesFull.push_back(makePlayerFacingName("2H_Melee_Attack_Stab"));
	m_animNamesFull.push_back(makePlayerFacingName("2H_Melee_Idle"));
	m_animNamesFull.push_back(makePlayerFacingName("2H_Ranged_Aiming"));
	m_animNamesFull.push_back(makePlayerFacingName("2H_Ranged_Reload"));
	m_animNamesFull.push_back(makePlayerFacingName("2H_Ranged_Shoot"));
	m_animNamesFull.push_back(makePlayerFacingName("2H_Ranged_Shooting"));
	m_animNamesFull.push_back(makePlayerFacingName("Block"));
	m_animNamesFull.push_back(makePlayerFacingName("Block_Attack"));
	m_animNamesFull.push_back(makePlayerFacingName("Block_Hit"));
	m_animNamesFull.push_back(makePlayerFacingName("Blocking"));
	m_animNamesFull.push_back(makePlayerFacingName("Cheer"));
	m_animNamesFull.push_back(makePlayerFacingName("Death_A"));
	m_animNamesFull.push_back(makePlayerFacingName("Death_A_Pose"));
	m_animNamesFull.push_back(makePlayerFacingName("Death_B"));
	m_animNamesFull.push_back(makePlayerFacingName("Death_B_Pose"));
	m_animNamesFull.push_back(makePlayerFacingName("Dodge_Backward"));
	m_animNamesFull.push_back(makePlayerFacingName("Dodge_Forward"));
	m_animNamesFull.push_back(makePlayerFacingName("Dodge_Left"));
	m_animNamesFull.push_back(makePlayerFacingName("Dodge_Right"));
	m_animNamesFull.push_back(makePlayerFacingName("Dualwield_Melee_Attack_Chop"));
	m_animNamesFull.push_back(makePlayerFacingName("Dualwield_Melee_Attack_Slice"));
	m_animNamesFull.push_back(makePlayerFacingName("Dualwield_Melee_Attack_Stab"));
	m_animNamesFull.push_back(makePlayerFacingName("Hit_A"));
	m_animNamesFull.push_back(makePlayerFacingName("Hit_B"));
	m_animNamesFull.push_back(makePlayerFacingName("Idle"));
	m_animNamesFull.push_back(makePlayerFacingName("Interact"));
	m_animNamesFull.push_back(makePlayerFacingName("Jump_Full_Long"));
	m_animNamesFull.push_back(makePlayerFacingName("Jump_Full_Short"));
	m_animNamesFull.push_back(makePlayerFacingName("Jump_Idle"));
	m_animNamesFull.push_back(makePlayerFacingName("Jump_Land"));
	m_animNamesFull.push_back(makePlayerFacingName("Jump_Start"));
	m_animNamesFull.push_back(makePlayerFacingName("Lie_Down"));
	m_animNamesFull.push_back(makePlayerFacingName("Lie_Idle"));
	m_animNamesFull.push_back(makePlayerFacingName("Lie_Pose"));
	m_animNamesFull.push_back(makePlayerFacingName("Lie_StandUp"));
	m_animNamesFull.push_back(makePlayerFacingName("PickUp"));
	m_animNamesFull.push_back(makePlayerFacingName("Running_A"));
	m_animNamesFull.push_back(makePlayerFacingName("Running_B"));
	m_animNamesFull.push_back(makePlayerFacingName("Running_Strafe_Left"));
	m_animNamesFull.push_back(makePlayerFacingName("Running_Strafe_Right"));
	m_animNamesFull.push_back(makePlayerFacingName("Sit_Chair_Down"));
	m_animNamesFull.push_back(makePlayerFacingName("Sit_Chair_Idle"));
	m_animNamesFull.push_back(makePlayerFacingName("Sit_Chair_Pose"));
	m_animNamesFull.push_back(makePlayerFacingName("Sit_Chair_StandUp"));
	m_animNamesFull.push_back(makePlayerFacingName("Sit_Floor_Down"));
	m_animNamesFull.push_back(makePlayerFacingName("Sit_Floor_Idle"));
	m_animNamesFull.push_back(makePlayerFacingName("Sit_Floor_Pose"));
	m_animNamesFull.push_back(makePlayerFacingName("Sit_Floor_StandUp"));
	m_animNamesFull.push_back(makePlayerFacingName("Spellcast_Long"));
	m_animNamesFull.push_back(makePlayerFacingName("Spellcast_Raise"));
	m_animNamesFull.push_back(makePlayerFacingName("Spellcast_Shoot"));
	m_animNamesFull.push_back(makePlayerFacingName("Spellcasting"));
	m_animNamesFull.push_back(makePlayerFacingName("T-Pose"));
	m_animNamesFull.push_back(makePlayerFacingName("Throw"));
	m_animNamesFull.push_back(makePlayerFacingName("Unarmed_Idle"));
	m_animNamesFull.push_back(makePlayerFacingName("Unarmed_Melee_Attack_Kick"));
	m_animNamesFull.push_back(makePlayerFacingName("Unarmed_Melee_Attack_Punch_A"));
	m_animNamesFull.push_back(makePlayerFacingName("Unarmed_Melee_Attack_Punch_B"));
	m_animNamesFull.push_back(makePlayerFacingName("Unarmed_Pose"));
	m_animNamesFull.push_back(makePlayerFacingName("Use_Item"));
	m_animNamesFull.push_back(makePlayerFacingName("Walking_A"));
	m_animNamesFull.push_back(makePlayerFacingName("Walking_B"));
	m_animNamesFull.push_back(makePlayerFacingName("Walking_Backwards"));
	m_animNamesFull.push_back(makePlayerFacingName("Walking_C"));
	m_animNamesFull.push_back(makePlayerFacingName(m_DEFAULT_FULL_ANIM));

}


/**
 * Get pointer to the current animation
 */
ModelNodeAnimationData* ModelNode::getCurrentAnimation() const
{
	return m_animations.at(m_currentAnimID);
}


/**
 * Get the current animation ID
 */
int ModelNode::getCurrentAnimationID() const
{
	return m_currentAnimID;
}


/**
 * Update the current animation
 */
void ModelNode::setCurrentAnimation(int p_ID)
{
	if (!(p_ID == m_previousAnimID))
	{
		m_model.getAnimation(m_animations.at(m_previousAnimID)->m_animationID).stop();
		m_previousAnimID = m_currentAnimID;
		m_currentAnimID = p_ID;
		m_animNamesFull.back() = std::to_string(p_ID);
		setAnimInRestricted(p_ID);
		m_model.getAnimation(m_animations.at(getCurrentAnimationID())->m_animationID).play();
	}
}


/**
 * Set looping or play once
 */
void ModelNode::setLoopingState(bool p_isLooping)
{
	m_loopAnimation = p_isLooping;

	m_model.getAnimation(m_animations.at(getCurrentAnimationID())->m_animationID).stop();
	(m_loopAnimation) ? m_model.setLoopStateForAllAnimations(OF_LOOP_NORMAL) : m_model.setLoopStateForAllAnimations(OF_LOOP_NONE);
	m_model.getAnimation(m_animations.at(getCurrentAnimationID())->m_animationID).play();

}


/**
 * From an index in the restricted list, find the actual animation in the full list
 */
int ModelNode::getAnimFromRestricted(int p_index)
{
	std::string nameToFind = m_animNamesRestricted.at(p_index);
	for (auto anim : m_animations)
	{
		if (anim->m_playerFacingName == nameToFind)
		{
			return anim->m_animationID;
		}
	}
	return -1;
}


/**
 * From a name, find the anim's index in the limited list and record it
 */
void ModelNode::setAnimInRestricted(int p_index)
{
	std::string nameToFind = m_animations.at(p_index)->m_playerFacingName;
	bool isFound = false;
	for (size_t i = 0; i < m_animNamesRestricted.size(); i++)
	{
		if (m_animNamesRestricted.at(i) == nameToFind)
		{
			m_animNamesRestricted.back() = std::to_string(i);
			isFound = true;
			break;
		}
	}
	if (!isFound) {
		m_animNamesRestricted.back() = m_DEFAULT_RESTRICTED_ANIM;
	}

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

void ModelNode::debugPrintNames() const
{
	ofLog() << "----------------------------";
	ofLog() << "- Printing names for [" << m_name << "]";
	for (auto anim : m_animations)
	{
		ofLog() << " --- Anim: " << anim->m_animationID << " : " << anim->m_devName << " (Player facing name: " << anim->m_playerFacingName << ")" ;
	}
}

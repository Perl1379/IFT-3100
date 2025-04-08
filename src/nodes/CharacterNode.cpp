/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * CharacterNode class implementation
 *
 *****************************************************/
#include "CharacterNode.h"

CharacterNode::CharacterNode(const std::string& p_name, const std::string& p_fileBaseName) 
	: ModelNode(p_name,
		((p_fileBaseName != "") ? p_fileBaseName : Global::m_modelManager.getRandom(MODEL_TYPE::CHARACTER)),
		MODEL_TYPE::CHARACTER
	)
{
	initHardcodedList();
	initAnimationsList();
	getModel().setLoopStateForAllAnimations(OF_LOOP_NORMAL);
	setCurrentAnimation(getCurrentAnimationID());

	//debugPrintNames();
}


int CharacterNode::draw(bool p_objectPicking, Camera* p_camera)
{
	if (!getDisplayNode()) return 0; //nothing to draw if the user hid the node

	int count = 0;
	beginDraw(p_objectPicking, p_camera);
	updateBoundingBox();

	if (p_camera->testVisibility(m_transform.getGlobalPosition(), getBoundingBox() * m_transform.getGlobalScale())) {
		m_transform.transformGL();
		if (p_objectPicking) {
			// p_objectPicking == true means we are drawing the object picking FBO
			getModel().disableMaterials();
			getModel().disableNormals();
			getModel().disableTextures();
		}
		else {

			// p_objectPicking == false means we are drawing the actual thing in the viewport
			if (m_playAnimation)
			{
				getModel().update();
			}
			getModel().disableTextures(); //if it's not disabled constantly, openFrameworks resets it to the default a few seconds after boot
			Global::m_modelManager.getTexture(m_modelNo, m_textureNo).bind();
		}
		getModel().drawFaces();

		if (p_objectPicking) {
			getModel().enableMaterials();
			getModel().enableNormals();
			getModel().enableTextures();
		}
		else {
			Global::m_modelManager.getTexture(m_modelNo, m_textureNo).unbind();
		}

		m_transform.restoreTransformGL();
		count++;
	}

	count += endDraw(p_objectPicking, p_camera);
	return count;
}


/**
 * Get ModelNode's properties list
 */
std::vector<NodeProperty> CharacterNode::getProperties() const
{
	std::vector<NodeProperty> properties = ModelNode::getProperties();

	//model property
	properties.emplace_back("Texture", PROPERTY_TYPE::ITEM_CLIST, std::make_pair(m_textureNo, Global::m_modelManager.getCTexNames(m_modelNo)), Global::m_tooltipMessages.node_modelTexture);

	//character specific animation parameters
	properties.emplace_back("Animation", PROPERTY_TYPE::LABEL, nullptr);
	properties.emplace_back("Play", PROPERTY_TYPE::BOOLEAN_FIELD, m_playAnimation, Global::m_tooltipMessages.node_playAnimation);
	properties.emplace_back("Animation", PROPERTY_TYPE::ITEM_LIST, (m_showAllAnimations) ? m_animNamesFull : m_animNamesRestricted);
	properties.emplace_back("Show all", PROPERTY_TYPE::BOOLEAN_FIELD, m_showAllAnimations, Global::m_tooltipMessages.node_showAllAnimation);

	return properties;
}


/**
 * A user changed a property
 */
void CharacterNode::setProperty(const std::string& p_name, std::any p_value)
{
	if (p_name == "Play") {
		m_playAnimation = std::any_cast<bool>(p_value);
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
	if (p_name == "Texture")
	{
		m_textureNo = std::any_cast<int>(p_value);
		return;
	}



	// first, udate stuff in the ModelNode or BaseNode
	// then reset the animation if the model changed
	ModelNode::setProperty(p_name, p_value);
	if (p_name == "Model") {
		resetAnimation();
		return;
	}
}


/**
 * Prepare animations for use
 */
void CharacterNode::initAnimationsList()
{
	bool addAnimation = true;
	std::string animName;
	for (unsigned int i = 0; i < getModel().getAnimationCount(); i++, addAnimation = true)
	{
		for (auto anim : m_animations)
		{
			if (anim->m_devName == getModel().getAnimation(i).getAnimation()->mName.data)
			{
				addAnimation = false;
				break;
			}
		}
		if (addAnimation)
		{
			animName = getModel().getAnimation(i).getAnimation()->mName.data;
			AnimationData* animData = new AnimationData(i, animName, makePlayerFacingName(animName));
			m_animations.push_back(animData);
		}
	}
	m_currentAnimID = getAnimFromRestricted(stoi(m_animNamesRestricted.back()));

}


/**
 * I hate this so much (hardcoded names)
 */
void CharacterNode::initHardcodedList()
{
	// Partial list
	m_animNamesRestricted.push_back(makePlayerFacingName("2H_Melee_Idle"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Death_A_Pose"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Idle"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Jump_Idle"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Lie_Idle"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Running_A"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Sit_Floor_Idle"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Spellcasting"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Unarmed_Idle"));
	m_animNamesRestricted.push_back(makePlayerFacingName("Walking_Backwards"));
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
	m_animNamesFull.push_back(m_DEFAULT_FULL_ANIM);

}


/**
 * From an index in the restricted list, find the actual animation in the full list
 */
int CharacterNode::getAnimFromRestricted(int p_index)
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
void CharacterNode::setAnimInRestricted(int p_index)
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
 * Get pointer to the current animation
 */
AnimationData* CharacterNode::getCurrentAnimation() const
{
	return m_animations.at(m_currentAnimID);
}


/**
 * Get the current animation ID
 */
int CharacterNode::getCurrentAnimationID() const
{
	return m_currentAnimID;
}


/**
 * Update the current animation
 */
void CharacterNode::setCurrentAnimation(int p_ID)
{
		stopCurrentAnimation();
		m_currentAnimID = p_ID;
		m_animNamesFull.back() = std::to_string(p_ID);
		setAnimInRestricted(p_ID);
		getModel().getAnimation(m_animations.at(getCurrentAnimationID())->m_animationID).play();
}


void CharacterNode::stopCurrentAnimation()
{
	getModel().getAnimation(m_animations.at(m_currentAnimID)->m_animationID).stop();
}


void CharacterNode::resetAnimation()
{
	stopCurrentAnimation();
	getModel().setLoopStateForAllAnimations(OF_LOOP_NORMAL);
	setCurrentAnimation(m_currentAnimID);
}


/**
 * Get the animation's name
 */
std::string CharacterNode::getCurrentAnimationName() const
{
	return getCurrentAnimation()->m_playerFacingName;
}


void CharacterNode::debugPrintNames() const
{
	ofLog() << "----------------------------";
	ofLog() << "- Printing names for [" << m_name << "]";
	for (auto anim : m_animations)
	{
		ofLog() << " --- Anim: " << anim->m_animationID << " : " << anim->m_devName << " (Player facing name: " << anim->m_playerFacingName << ")";
	}
}


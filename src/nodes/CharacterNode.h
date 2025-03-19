/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * ModelNode class implementation
 *
 *****************************************************/
#pragma once
#include "ModelNode.h"
#include "ofMain.h"
#include "ofxCustomAssimpModelLoader.h"
#include "Global.h"
#include <vector>

struct AnimationData
{
	AnimationData(int p_id, const std::string& p_dName, const std::string& p_pName) 
		: m_animationID(p_id), m_devName(p_dName), m_playerFacingName(p_pName) {}
	int m_animationID;
	std::string m_devName;
	std::string m_playerFacingName;
};

class CharacterNode : public ModelNode
{
private:
	bool m_playAnimation = true;
	bool m_showAllAnimations = false;
	const std::string m_DEFAULT_RESTRICTED_ANIM = "2";  // the number here means "Idle", which is 36 in the full list
	const std::string m_DEFAULT_FULL_ANIM = "36";
	std::vector<AnimationData*> m_animations;
	std::vector<std::string> m_animNamesRestricted; // used for showing them to the user
	std::vector<std::string> m_animNamesFull;
	int m_currentAnimID;
	int m_textureNo = 0;
	
public:
	CharacterNode(const std::string& p_name = "New Character", const std::string& p_fileBaseName = "");
	int draw(bool p_objectPicking, Camera* p_camera) override;

	std::vector<NodeProperty> getProperties() const override;
	void setProperty(const std::string& p_name, std::any p_value) override;

	void setCurrentAnimation(int p_ID);
	std::string getCurrentAnimationName() const;

private:
	void initHardcodedList();
	void initAnimationsList();
	AnimationData* getCurrentAnimation() const;
	void stopCurrentAnimation();
	void resetAnimation();
	int getCurrentAnimationID() const;
	int getAnimFromRestricted(int p_index);
	void setAnimInRestricted(int p_index);
	void debugPrintNames() const;
};


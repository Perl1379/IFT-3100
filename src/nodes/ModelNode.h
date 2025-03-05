/*****************************************************
 * TP IFT3100H25 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * ModelNode class definition
 *
 *****************************************************/
#pragma once

#include "BaseNode.h"
#include "ofMain.h"
#include "ofxCustomAssimpModelLoader.h"
#include "Global.h"
#include <vector>


struct ModelNodeAnimationData
{
	ModelNodeAnimationData(int p_id, const std::string& p_dName, const std::string& p_pName) : m_animationID(p_id), m_devName(p_dName), m_playerFacingName(p_pName)	{}
	int m_animationID;
	std::string m_devName;
	std::string m_playerFacingName;
};


class ModelNode : public BaseNode {

private:
	ofxCustomAssimpModelLoader m_model;
	ofVec3f m_bounds;
	bool m_playAnimation = true;
	bool m_loopAnimation = false;
	bool m_showAllAnimations = false;
	const std::string m_DEFAULT_RESTRICTED_ANIM = "4";  // the number here means "Idle", which is ID 36 in the full list
	const std::string m_DEFAULT_FULL_ANIM = "36";
	std::vector<ModelNodeAnimationData*> m_animations;
	std::vector<std::string> m_animNamesRestricted; // used for showing them to the user
	std::vector<std::string> m_animNamesFull;
	int m_previousAnimID;
	int m_currentAnimID;

public:
	explicit ModelNode(const std::string& p_name, const std::string& p_filePath);
	void setPosition(ofVec3f p_pos);
	void setPosition(float p_x, float p_y, float p_z);
	int draw(bool p_objectPicking, Camera* p_camera) override;
	int endDraw(bool p_objectPicking, Camera* p_camera);
	ofVec3f getBoundingBox() const override;
	std::vector<NodeProperty> getProperties() const override;
	void setProperty(const std::string& p_name, std::any p_value) override;
	void setCurrentAnimation(int p_ID);
	void setLoopingState(bool p_isLooping);
	std::string getCurrentAnimationName() const;
	ofxAssimpModelLoader& getModel();
	~ModelNode();

private:
	void initHardcodedList();
	void initAnimationsList();
	ModelNodeAnimationData* getCurrentAnimation() const;
	int getCurrentAnimationID() const;
	int getAnimFromRestricted(int p_index);
	void setAnimInRestricted(int p_index);

	void updateBoundingBox();
	void drawBoundingBox();

	std::string makePlayerFacingName(const std::string& p_name);
	void debugPrintNames() const;

};

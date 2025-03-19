/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
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
#include "ModelManager.h"
#include <vector>


class ModelNode : public BaseNode {

private:
	ofxCustomAssimpModelLoader m_model;
	std::string m_fileBaseName;
	ofVec3f m_bounds;
protected:
	int m_modelNo = 0;
	const MODEL_TYPE m_modelType;

public:
	explicit ModelNode(const std::string& p_nodeName, const std::string& p_fileBaseName, MODEL_TYPE p_modelType);

protected:
	void updateModel(int p_modelNo);
	void updateModel(const std::string& p_modelName);

public:
	std::vector<NodeProperty> getProperties() const override;
	void setProperty(const std::string& p_name, std::any p_value) override;
	void setPosition(ofVec3f p_pos);
	void setPosition(float p_x, float p_y, float p_z);
	int draw(bool p_objectPicking, Camera* p_camera) override;
	int endDraw(bool p_objectPicking, Camera* p_camera);
	ofVec3f getBoundingBox() const override;
	ofxCustomAssimpModelLoader& getModel();

protected:
	std::string makePlayerFacingName(const std::string& p_name);
	void updateBoundingBox();
	~ModelNode();

private:
	void loadModel(const std::string& p_filePath);
	void drawBoundingBox();

};

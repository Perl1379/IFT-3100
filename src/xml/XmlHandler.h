#pragma once

#include "ofxXmlSettings.h"
#include "iostream"
#include "mutex"
#include <BaseNode.h>
#include <Global.h>

class XmlHandler
{
private:
	static XmlHandler* instancePtr;
	static mutex mtx;
	XmlHandler() {};

	string filePath;
	void setFilePath(string path);

	void addChild(BaseNode* child);

	void addNodeProperties(BaseNode* child);

	void setNodePropertyValue(NodeProperty property);

public:
	XmlHandler(const XmlHandler& obj) = delete;
	static XmlHandler* getInstance();

	ofxXmlSettings XML;

	void setup();
	void save();
	void load(string path);
	void createNewFile(string path);

	// D�but des fonctions lie au attribut cam�ra avec XML

	void setFirstCameraPosition(float x, float y, float z);
	void setFirstCameraOrientation(float x, float y, float z);
	void setFirstCameraOrtho(bool isOrtho);

	void setSecondCameraPosition(float x, float y, float z);
	void setSecondCameraOrientation(float x, float y, float z);
	void setSecondCameraOrtho(bool isOrtho);

	void setThirdCameraPosition(float x, float y, float z);
	void setThirdCameraOrientation(float x, float y, float z);
	void setThirdCameraOrtho(bool isOrtho);

	ofVec3f getFirstCameraPosition();
	ofVec3f getFirstCameraOrientation();
	bool getFirstCameraOrtho();

	ofVec3f getSecondCameraPosition();
	ofVec3f getSecondCameraOrientation();
	bool getSecondCameraOrtho();

	ofVec3f getThirdCameraPosition();
	ofVec3f getThirdCameraOrientation();
	bool getThirdCameraOrtho();

	// Fin des fonctions lie au cam�ra

	// D�but des fonctions lie au Node

	void setNodesProperties();

	// Fin des fonctions lie au Node
};


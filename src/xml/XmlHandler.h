#pragma once

#include "ofxXmlSettings.h"
#include "iostream"
#include "mutex"

class XmlHandler
{
private:
	static XmlHandler* instancePtr;
	static mutex mtx;
	XmlHandler() {};

	string filePath;
	void setFilePath(string path);

public:
	static XmlHandler* getInstance();

	ofxXmlSettings XML;

	void setup();
	void save();
	void load(string path);
	void createNewFile(string path);

	// Fonction lié au attribut caméra avec XML

	void setFirstCameraPosition(int x, int y, int z);
	void setFirstCameraOrientation(int x, int y, int z);

	void setSecondCameraPosition(int x, int y, int z);
	void setSecondCameraOrientation(int x, int y, int z);

	void setThirdCameraPosition(int x, int y, int z);
	void setThirdCameraOrientation(int x, int y, int z);

	ofVec3f getFirstCameraPosition();
	ofVec3f getFirstCameraOrientation();

	ofVec3f getSecondCameraPosition();
	ofVec3f getSecondCameraOrientation();

	ofVec3f getThirdCameraPosition();
	ofVec3f getThirdCameraOrientation();


	XmlHandler(const XmlHandler& obj) = delete;

};

XmlHandler* XmlHandler::instancePtr = nullptr;
mutex XmlHandler::mtx;


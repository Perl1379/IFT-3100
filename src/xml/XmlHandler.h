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
	XmlHandler(const XmlHandler& obj) = delete;
	static XmlHandler* getInstance();

	ofxXmlSettings XML;

	void setup();
	void save();
	void load(string path);
	void createNewFile(string path);

	// Fonction lié au attribut caméra avec XML

	void setFirstCameraPosition(int x, int y, int z);
	void setFirstCameraOrientation(int x, int y, int z);
	void setFirstCameraOrtho(bool isOrtho);

	void setSecondCameraPosition(int x, int y, int z);
	void setSecondCameraOrientation(int x, int y, int z);
	void setSecondCameraOrtho(bool isOrtho);

	void setThirdCameraPosition(int x, int y, int z);
	void setThirdCameraOrientation(int x, int y, int z);
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

	// Fin des fonctions lié au caméra

};

XmlHandler* XmlHandler::instancePtr = nullptr;
mutex XmlHandler::mtx;


/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * ModelManager class definition
 *
 *****************************************************/
#pragma once
#include <vector>
#include <string>
#include <ofxXmlSettings.h>
//#include <memory>
//#include <sstream>
#include "ofMain.h"
#include "ofxCustomAssimpModelLoader.h"


enum class MODEL_TYPE {
	ASSET,
	CHARACTER
};


/**
* In this application, the word "model" is the broadest term.
* We have two types of models:
* - characters: these are the rogue, knight, etc. They have animations;
* - assets: decoration items. They are detached from characters and do not have animations in this application.
*/
class ModelManager
{
	//variables
private:
	const std::string m_charactersPath = "KayKit/Characters/gltf";
	const std::string m_assetsPath = "KayKit/Assets/gltf";
	const std::string m_animPath = "KayKit/Characters/gltf/Animations.xml";
	const std::string m_charactersExtension = "glb";
	const std::string m_assetsExtension = "gltf";
	std::vector<std::string> m_characterStrNames;
	std::vector<std::string> m_assetStrNames;
	std::vector<char*> m_characterCNames;
	std::vector<char*> m_assetCNames;
	
	//functions
public: 
	void init();
private:
	void listNames(std::vector<std::string>& p_list, const std::string& p_directoryPath, const std::string& p_fileExtension);
	void listCNames(std::vector<std::string>& p_list, std::vector<char*>& p_cList);
public:
	const std::vector<char*> getCNames(MODEL_TYPE p_type);
	std::string getModelPath(const std::string& p_name, MODEL_TYPE p_type);
	std::string getModelPath(int p_cIndex, MODEL_TYPE p_type);
	std::string getModelName(int p_index, MODEL_TYPE p_type);
	std::string getRandom(MODEL_TYPE p_type);
	int getModelNo(const std::string& p_name, MODEL_TYPE p_type);
};


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
#include <map>
#include <string>
#include "ofMain.h"


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
	const std::string m_CHARACTERS_PATH = "KayKit/Characters/gltf";
	const std::string m_ASSETS_PATH = "KayKit/Assets/gltf";
	const std::string m_CHARACTERS_EXTENSION = "glb";
	const std::string m_ASSETS_EXTENSION = "gltf";
	
	// Model names
	std::vector<std::string> m_characterStrNames;
	std::vector<std::string> m_assetStrNames;
	std::vector<char*> m_characterCNames;
	std::vector<char*> m_assetCNames;

	// Character textures
	const std::string m_CHARACTER_TEXTURE_PATH = "KayKit/Textures";
	const std::vector<std::string> m_CHARACTER_TEXTURE_FILE_NAMES{ "texture.png", "texture_alt_A.png", "texture_alt_B.png", "texture_alt_C.png" };
	std::map<int, std::array<ofTexture, 4>> m_characterTextures;
	const std::map<std::string, std::vector<char*>> m_CHARACTER_TEXTURE_NAMES{
		{"Barbarian", {
			"Ice moose",
			"Clover fox",
			"Sun wolf",
			"Dirt bear"}},
		{"Druid", {
			"Forest strider",
			"Tundra dweller",
			"Ash walker",
			"Desert drifter" }},
		{"Engineer", {
			"Copper mechanic",
			"Steel plumber",
			"Cobalt wireman",
			"Pyrite mason"}},
		{"Knight", {
			"Steely heart",
			"Pale fir",
			"Golden stone",
			"Crimson snow"}},
		{"Mage", {
			"Emerald necromancer",
			"Aquamarine brewmaster",
			"Topaz herbalist",
			"Amethyst transmuter"}},
		{"Rogue", {
			"Green poisoner",
			"Silver swindler",
			"Motley arsonist",
			"Pink assassin"}},
		{"Rogue_Hooded", {
			"Green poisoner",
			"Silver arsonist",
			"Motley robber",
			"Pink assassin"}},
	};
	
	//functions
public: 
	void init();
private:
	void listNames(std::vector<std::string>& p_list, const std::string& p_directoryPath, const std::string& p_fileExtension);
	void listCNames(std::vector<std::string>& p_list, std::vector<char*>& p_cList);
	void loadCharacterTextures();
public:
	const std::vector<char*> getCNames(MODEL_TYPE p_type);
	const std::vector<char*> getCTexNames(int p_index, MODEL_TYPE p_type = MODEL_TYPE::CHARACTER);
	std::string getModelPath(const std::string& p_name, MODEL_TYPE p_type);
	std::string getModelPath(int p_cIndex, MODEL_TYPE p_type);
	std::string getModelName(int p_index, MODEL_TYPE p_type);
	std::string getRandom(MODEL_TYPE p_type);
	int getModelNo(const std::string& p_name, MODEL_TYPE p_type);
	const ofTexture& getTexture(int p_characterIndex, int p_textureIndex, MODEL_TYPE p_type = MODEL_TYPE::CHARACTER);
};


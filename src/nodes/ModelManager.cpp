/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * ModelManager class definition
 *
 *****************************************************/
#include "ModelManager.h"

/**
* Call this to load the models and list their names
*/
void ModelManager::init()
{
	listNames(m_characterStrNames, m_CHARACTERS_PATH, m_CHARACTERS_EXTENSION);
	listNames(m_assetStrNames, m_ASSETS_PATH, m_ASSETS_EXTENSION);
	listCNames(m_characterStrNames, m_characterCNames);
	listCNames(m_assetStrNames, m_assetCNames);
	loadCharacterTextures();
}


/**
* Lists file names with a given extension from a given folder
*/
//std::vector<char*>& p_cList
void ModelManager::listNames(std::vector<std::string>& p_list, const std::string& p_directoryPath, const std::string& p_fileExtension)
{
	if( ! ofDirectory::doesDirectoryExist(p_directoryPath)) {
		ofLog(OF_LOG_FATAL_ERROR) << "This directory does not exist: " << p_directoryPath;
	}

	ofDirectory directory;
	directory.open(p_directoryPath);
	std::vector<ofFile> files = directory.getFiles();
	std::string fileBaseName;
	for (ofFile file : files) {
		if (file.getExtension() == p_fileExtension) {
			fileBaseName = file.getBaseName();
			p_list.push_back(fileBaseName.c_str());
		}
	}
	directory.close();
}


/**
* List the keys in a vector; needed for NodeProperties and ImGui
*/
void ModelManager::listCNames(std::vector<std::string>& p_list, std::vector<char*>& p_cList)
{
	p_cList.reserve(p_list.size());
	for (const auto& item : p_list) {
		p_cList.push_back(const_cast<char*>(item.c_str()));
	}

}


/**
* Preload all textures, then all character models can reuse the same
*/
void ModelManager::loadCharacterTextures()
{
	for(int i = 0; i < m_characterStrNames.size(); i++)
	{
		std::array<ofTexture, 4> textureVariant;
		for (int j = 0; j < m_CHARACTER_TEXTURE_FILE_NAMES.size(); j++)
		{
			// "Rogue" and its variant model "Rogue_Hooded" share the same "Rogue" texture files
			std::string characterName = m_characterStrNames.at(i) == "Rogue_Hooded" ? "Rogue" : m_characterStrNames.at(i);

			// Construct the path
			std::string path = m_CHARACTER_TEXTURE_PATH + "/" + ofToLower(characterName) + "_" + m_CHARACTER_TEXTURE_FILE_NAMES.at(j);
			//ofLog() << "Loading path: " << path;
			ofImage texturePNG;
			texturePNG.load(path);
			textureVariant.at(j) = texturePNG.getTexture();
		}
		m_characterTextures.emplace(i, textureVariant);
	}
}


/**
* Gets the names list. Use with ImGui Combo
*/
const std::vector<char*> ModelManager::getCNames(MODEL_TYPE p_type)
{
	if (p_type == MODEL_TYPE::ASSET) {
		return m_assetCNames;
	}
	// MODEL_TYPE::CHARACTER
	return m_characterCNames;
}


/**
* Gets the texture names list. Use with ImGui Combo
*/
const std::vector<char*> ModelManager::getCTexNames(int p_index, MODEL_TYPE p_type)
{
	if (p_type != MODEL_TYPE::CHARACTER) {
		ofLog(OF_LOG_FATAL_ERROR) << "getCTexNames is only available for our characters (we use the KayKit textures which have a shared naming convention).";
	}
	return m_CHARACTER_TEXTURE_NAMES.at(getModelName(p_index, p_type));
}


/**
* Constructs and returns the model's file path
* in: model's file base name (i.e.: "barbarian")
*/
std::string ModelManager::getModelPath(const std::string& p_name, MODEL_TYPE p_type)
{
	if (p_type == MODEL_TYPE::ASSET) {
		return 	m_ASSETS_PATH + "/" + p_name + "." + m_ASSETS_EXTENSION;
	}
	// MODEL_TYPE::CHARACTER
	return m_CHARACTERS_PATH + "/" + p_name + "." + m_CHARACTERS_EXTENSION;
}


/**
* Constructs and returns the model's file path.
* Typically use this one after the user changed the model's type via the NodeProperty
* in: model's index in the c names list (i.e.: 0)
*/
std::string ModelManager::getModelPath(int p_cIndex, MODEL_TYPE p_type)
{
	if (p_type == MODEL_TYPE::ASSET) {
		std::string sName(m_assetCNames.at(p_cIndex));
		return getModelPath(sName, p_type);
	}
	// MODEL_TYPE::CHARACTER
	std::string sName(m_characterCNames.at(p_cIndex));
	return getModelPath(sName, p_type);
}


/**
* p_index is an index in the cnames list
*/
std::string ModelManager::getModelName(int p_index, MODEL_TYPE p_type)
{
	if (p_type == MODEL_TYPE::ASSET) {
		return std::string(m_assetCNames[p_index]);
	}
	// MODEL_TYPE::CHARACTER
	return std::string(m_characterCNames[p_index]);
}


/**
* Gets a random model of type
*/
std::string ModelManager::getRandom(MODEL_TYPE p_type)
{
	if (p_type == MODEL_TYPE::ASSET) {
		return std::string(m_assetCNames[(rand() % m_assetCNames.size())]);
	}
	// MODEL_TYPE::CHARACTER
	return std::string(m_characterCNames[(rand() % m_characterCNames.size())]);
}


/**
* Gets the model's index in the C names list (necessary for NodeProperty and ImGui's combo)
*/
int ModelManager::getModelNo(const std::string& p_name, MODEL_TYPE p_type)
{
	if (p_type == MODEL_TYPE::ASSET) {
		for (int i = 0; i < m_assetCNames.size(); i++) {
			std::string name(m_assetCNames[i]);
			if (name == p_name) {
				return i;
			}
		};
	}
	// MODEL_TYPE::CHARACTER
	int i = 0;
	for (; i < m_characterCNames.size(); i++) {
		std::string name(m_characterCNames[i]);
		if (name == p_name) {
			break;
		}
	};
	return i;
}


/**
* Returns a reference to a texture. Typically used by CharacterNode instances to bind the texture to their model
*/
const ofTexture& ModelManager::getTexture(int p_characterIndex, int p_textureIndex, MODEL_TYPE p_type)
{
	if (p_type != MODEL_TYPE::CHARACTER) {
		ofLog(OF_LOG_FATAL_ERROR) << "getCTexNames is only available for our characters (we use the KayKit textures which have a shared naming convention).";
	}
	return m_characterTextures.at(p_characterIndex).at(p_textureIndex);
}

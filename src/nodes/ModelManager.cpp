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
	listNames(m_characterStrNames, m_charactersPath, m_charactersExtension);
	listNames(m_assetStrNames, m_assetsPath, m_assetsExtension);
	listCNames(m_characterStrNames, m_characterCNames);
	listCNames(m_assetStrNames, m_assetCNames);
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
* Gets the names list. Use with ImGui Combo
*/
const std::vector<char*> ModelManager::getCNames(MODEL_TYPE p_type)
{
	if (p_type == MODEL_TYPE::ASSET) {
		return m_assetCNames;
	}
	if (p_type == MODEL_TYPE::CHARACTER) {
		return m_characterCNames;
	}
	ofLog(OF_LOG_FATAL_ERROR) << "Unrecognised MODEL_TYPE.";
}


/**
* Constructs and returns the model's file path
* in: model's file base name (i.e.: "barbarian")
*/
std::string ModelManager::getModelPath(const std::string& p_name, MODEL_TYPE p_type)
{
	if (p_type == MODEL_TYPE::ASSET) {
		return 	m_assetsPath + "/" + p_name + "." + m_assetsExtension;
	}
	else if (p_type == MODEL_TYPE::CHARACTER) {
		return m_charactersPath + "/" + p_name + "." + m_charactersExtension;
	}
	else {
		ofLog(OF_LOG_FATAL_ERROR) << "Unrecognised MODEL_TYPE.";
	}
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
	else if (p_type == MODEL_TYPE::CHARACTER) {
		std::string sName(m_characterCNames.at(p_cIndex));
		return getModelPath(sName, p_type);
	}
	else {
		ofLog(OF_LOG_FATAL_ERROR) << "Unrecognised MODEL_TYPE.";
	}
}


/**
* p_index is an index in the cnames list
*/
std::string ModelManager::getModelName(int p_index, MODEL_TYPE p_type)
{
	if (p_type == MODEL_TYPE::ASSET) {
		return std::string(m_assetCNames[p_index]);
	}
	else if (p_type == MODEL_TYPE::CHARACTER) {
		return std::string(m_characterCNames[p_index]);
	}
	else {
		ofLog(OF_LOG_FATAL_ERROR) << "Unrecognised MODEL_TYPE.";
	}
}


/**
* Gets a random model of type
*/
std::string ModelManager::getRandom(MODEL_TYPE p_type)
{
	if (p_type == MODEL_TYPE::ASSET) {
		return std::string(m_assetCNames[(rand() % m_assetCNames.size())]);
	}
	else if (p_type == MODEL_TYPE::CHARACTER) {
		return std::string(m_characterCNames[(rand() % m_characterCNames.size())]);
	}
	else {
		ofLog(OF_LOG_FATAL_ERROR) << "Unrecognised MODEL_TYPE.";
	}
}


/**
* Gets the model's index in the C names list (necessary for NodeProperty and ImGui's combo)
*/
int ModelManager::getModelNo(const std::string& p_name, MODEL_TYPE p_type)
{
	//std::string name;
	if (p_type == MODEL_TYPE::ASSET) {
		for (int i = 0; i < m_assetCNames.size(); i++) {
			std::string name(m_assetCNames[i]);
			if (name == p_name) {
				return i;
			}
		};
	}
	else if (p_type == MODEL_TYPE::CHARACTER) {
		for (int i = 0; i < m_characterCNames.size(); i++) {
			std::string name(m_characterCNames[i]);
			if (name == p_name) {
				return i;
			}
		};
	}
	else {
		ofLog(OF_LOG_FATAL_ERROR) << "Unrecognised MODEL_TYPE.";
	}
}
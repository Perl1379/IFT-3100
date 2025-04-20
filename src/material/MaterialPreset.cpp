/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * MaterialPreset class implementation
 *
 *****************************************************/

#include "MaterialPreset.h"

/**
* Define presets here in this function.
* Display names must be unique since they are keys in the map
*/
void MaterialPreset::init()
{
	//--- Define material presets here
	MaterialPBR preset0("Default", ""); // Default / no texture
	m_presetNames.push_back(preset0.m_displayName.data());
	m_presetValues.emplace(preset0.m_displayName, preset0);

	MaterialPBR preset1("Grassy coastal ground", "coast_sand_rocks_02");
	m_presetNames.push_back(preset1.m_displayName.data());
	m_presetValues.emplace(preset1.m_displayName, preset1);
	loadTextures(preset1);

	MaterialPBR preset2("Sandstone cracks ground", "sandstone_cracks");
	m_presetNames.push_back(preset2.m_displayName.data());
	m_presetValues.emplace(preset2.m_displayName, preset2);
	loadTextures(preset2);

	MaterialPBR preset3("Rock face", "rock_face");
	m_presetNames.push_back(preset3.m_displayName.data());
	m_presetValues.emplace(preset3.m_displayName, preset3);
	loadTextures(preset3);



	//--- This last call creates the list for imgui.
	listCValues();
}

MaterialPreset::~MaterialPreset()
{
	m_presetCNames.clear();
}


/**
* Retrieves the material associated with the selected preset's name
*/
const MaterialPBR& MaterialPreset::getMaterial(int p_index)
{
	std::string key = m_presetCNames[p_index];
	return m_presetValues.find(key)->second;
}


/**
* Makes the char* vector that is necessary for imgui
*/
void MaterialPreset::listCValues()
{
	m_presetNames.reserve(m_presetCNames.size());
	for (const auto& item : m_presetNames) {
		m_presetCNames.push_back(const_cast<char*>(item.c_str()));
	}
}


/**
* Loads all existing textures into the material
*/
void MaterialPreset::loadTextures(MaterialPBR& p_mat)
{
	std::string name = p_mat.m_baseFileName;
	std::string folder = "images/textures/" + name;

	if (!ofDirectory::doesDirectoryExist(folder)) {
		ofLog(OF_LOG_FATAL_ERROR) << "This directory does not exist: " << folder;
	}

	ofDirectory directory;
	directory.open(folder);
	std::vector<ofFile> files = directory.getFiles();
	std::string fileBaseName;

	// Find all existing textures (names must match perfectly to be found)
	for (size_t texIndex = 0; texIndex < m_TEXTURE_TYPES.size(); texIndex++) {
		for (ofFile file : files) {
			if ((file.getExtension() == "png") && (file.getFileName().find(name) != std::string::npos)) {
				if (file.getFileName().find(m_TEXTURE_TYPES[texIndex]) != std::string::npos) {
					ofImage texturePNG;
					texturePNG.load(file.path());
					p_mat.m_textures[texIndex] = texturePNG.getTexture();
					//if (p_mat.m_textures[texIndex].isAllocated()) {
					//	ofLog() << "Texture loaded: " << file.path(); //DEBUG PRINT
					//}
					break;
				}
			}
		}
	}

	directory.close();

	p_mat.loadTextures();
}
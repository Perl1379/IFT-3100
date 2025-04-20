/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * MaterialPreset class definition
 *
 *****************************************************/

#pragma once
#include <string>
#include <map>
#include <vector>
#include <ofColor.h>
#include <ofMain.h>
#include "Material.h"

enum class textureTypes { ao, arm, diff, disp, nor, rough, spec };

class MaterialPreset
{
private:
	// PRIVATE VARIABLES
	std::vector<std::string> m_presetNames;
	std::vector<const char*> m_presetCNames;
	const std::vector<std::string> m_TEXTURE_TYPES{ "ao", "arm", "diff", "disp", "nor", "rough", "spec"};
	std::map<std::string, MaterialPBR> m_presetValues;
public: 
	void init();
	~MaterialPreset();

	//accessors
	const std::vector<const char*> getPresetList() { return m_presetCNames; };
	const MaterialPBR& getMaterial(int p_index);

private:
	void listCValues();
	void loadTextures(MaterialPBR& p_mat);
};
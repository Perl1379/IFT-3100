/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * MaterialPBR class definition
 *
 *****************************************************/
#pragma once
#include <string>
#include <ofColor.h>
#include "ofMain.h"
#include "TextureInfo.h"

class MaterialPBR
{
public:
	MaterialPBR(const std::string& p_displayName, const std::string& p_baseFileName);
	std::string m_displayName = "Default";
	std::string m_baseFileName = "";

	ofMaterial m_material;
	std::array<ofTexture, 7> m_textures; //"ao", "arm", "diff", "disp", "nor", "rough", "spec"

	ofFloatColor m_ambiantColor = ofFloatColor(0.0f, 0.0f, 0.0f);
	ofFloatColor m_diffuseColor = ofFloatColor(1.0f, 1.0f, 0.0f);
	ofFloatColor m_emissiveColor = ofFloatColor(1.0f, 1.0f, 0.0f);
	ofColor m_specularColor = ofColor(0, 0, 0);

	ofFloatColor m_textureAlbedoColor = ofFloatColor(1.0f, 1.0f, 1.0f);
	ofFloatColor m_textureNormal = ofFloatColor(0.50196f, 0.50196f, 1.0f);

	float m_shininess = 0.0f;
	float m_metallicity = 0.0f;

	// functions
	void loadTextures();

private:

};


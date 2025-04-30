/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * MaterialPreset struct definition
 *
 *****************************************************/
#pragma once
#include <iostream>
#include <ofColor.h>
using namespace std;


struct MaterialPreset {

    string m_name;

    // Only used by Phong
    ofFloatColor m_colorAmbient;
    ofFloatColor m_colorSpecular;
    float m_shininess = 1.0f;

    // Used by both phong and PBR
    ofFloatColor m_colorDiffuse;
    ofFloatColor m_colorEmissive;
    float m_roughness = 0.5f;
    std::string m_textureAlbedo;
    std::string m_textureNormal;

    // PBR Only
    float m_metallicity = 0.0f;
    float m_ior = 0.5f;

    std::string m_textureAO;
    std::string m_textureMetallic;
    std::string m_textureRoughness;
};

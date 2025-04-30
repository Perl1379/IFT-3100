/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * MaterialPresetManager class implementation
 *
 *****************************************************/
#include "MaterialPresetManager.h"

#include <LevelPersistence.h>
#include <ofFileUtils.h>
#include <ofXml.h>



/**
 * Constructor
 */
MaterialPresetManager::MaterialPresetManager() {

}


/**
 * Retrieve assets
 */
std::vector<MaterialPreset>* MaterialPresetManager::getPresets() {
    return &m_presets;
}


/**
 * Read all materials
 */
void MaterialPresetManager::init() {

    ofDirectory dirMaterials;
    dirMaterials.listDir("materials/");

    vector<string> materialNames;

    for (size_t i=0;i<dirMaterials.size();i++) {
        std::string name = dirMaterials.getFile(i).getFileName();
        materialNames.push_back(name);
    }

    sort(materialNames.begin(), materialNames.end());
    m_presets.clear();

    for (size_t i=0;i<materialNames.size();i++) {

        ofXml xml;
        if (!xml.load("materials/" + materialNames[i])) {
            ofLogError() << "Failed to load level xml file: " << "materials/" + materialNames[i];
            return;
        }

        ofXml xmlMaterial = xml.getFirstChild();
        MaterialPreset preset;

        preset.m_name = xmlMaterial.getAttribute("name").getValue();
        for (ofXml child : xmlMaterial.getChildren()) {
            auto propertyName = child.getAttribute("name").getValue();

            if (propertyName == "Diffuse Color") {
                preset.m_colorDiffuse = LevelPersistence::stringToColor(child.getAttribute("value").getValue());

            } else if (propertyName == "Ambient Color") {
                preset.m_colorAmbient = LevelPersistence::stringToColor(child.getAttribute("value").getValue());

            } else if (propertyName == "Emissive Color") {
                preset.m_colorEmissive = LevelPersistence::stringToColor(child.getAttribute("value").getValue());

            } else if (propertyName == "Specular Color") {
                preset.m_colorSpecular = LevelPersistence::stringToColor(child.getAttribute("value").getValue());

            } else if (propertyName == "Shininess") {
                preset.m_shininess = child.getAttribute("value").getFloatValue();

            } else if (propertyName == "Reflectance") {
                preset.m_ior = child.getAttribute("value").getFloatValue();

            } else if (propertyName == "Metallicity") {
                preset.m_metallicity = child.getAttribute("value").getFloatValue();

            } else if (propertyName == "Albedo Texture") {
                preset.m_textureAlbedo = child.getAttribute("value").getValue();

            } else if (propertyName == "Normal Texture") {
                preset.m_textureNormal = child.getAttribute("value").getValue();

            } else if (propertyName == "Metallic Texture") {
                preset.m_textureMetallic = child.getAttribute("value").getValue();

            } else if (propertyName == "Roughness Texture") {
                preset.m_textureRoughness = child.getAttribute("value").getValue();

            } else if (propertyName == "AO Texture") {
                preset.m_textureAO = child.getAttribute("value").getValue();
            }

        }

        m_presets.push_back(preset);
        std::string origName = preset.m_name;
        std::string origTextureAlbedo = preset.m_textureAlbedo;
        std::string origTextureNormal = preset.m_textureNormal;
        std::string origTextureMetallic = preset.m_textureMetallic;
        std::string origTextureRoughness = preset.m_textureRoughness;
        std::string origTextureAO = preset.m_textureAO;

        preset.m_name = origName + " (2x)";
        preset.m_textureAlbedo = origTextureAlbedo;
        preset.m_textureNormal = origTextureNormal;
        preset.m_textureMetallic = origTextureMetallic;
        preset.m_textureRoughness = origTextureRoughness;
        preset.m_textureAO = origTextureAO;
        ofStringReplace(preset.m_textureAlbedo, ";10497;1.000000",";10497;2.000000");
        ofStringReplace(preset.m_textureNormal, ";10497;1.000000",";10497;2.000000");
        ofStringReplace(preset.m_textureMetallic, ";10497;1.000000",";10497;2.000000");
        ofStringReplace(preset.m_textureRoughness, ";10497;1.000000",";10497;2.000000");
        ofStringReplace(preset.m_textureAO, ";10497;1.000000",";10497;2.000000");
        m_presets.push_back(preset);

        preset.m_name = origName + " (4x)";
        preset.m_textureAlbedo = origTextureAlbedo;
        preset.m_textureNormal = origTextureNormal;
        preset.m_textureMetallic = origTextureMetallic;
        preset.m_textureRoughness = origTextureRoughness;
        preset.m_textureAO = origTextureAO;
        ofStringReplace(preset.m_textureAlbedo, ";10497;1.000000",";10497;4.000000");
        ofStringReplace(preset.m_textureNormal, ";10497;1.000000",";10497;4.000000");
        ofStringReplace(preset.m_textureMetallic, ";10497;1.000000",";10497;4.000000");
        ofStringReplace(preset.m_textureRoughness, ";10497;1.000000",";10497;4.000000");
        ofStringReplace(preset.m_textureAO, ";10497;1.000000",";10497;4.000000");
        m_presets.push_back(preset);

    }


}
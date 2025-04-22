/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * MaterialPBR class implementation
 *
 *****************************************************/
#include "Material.h"

 /**
 * p_displayName: what the user will see (ie.: "Wooden floor")
 * p_folderName: base name of the textures on disk  (ie.: "laminate_wood_tiled_floor_04")
 */
MaterialPBR::MaterialPBR(const std::string& p_displayName, const std::string& p_folderName)
	: m_displayName(p_displayName), m_baseFileName(p_folderName)
{
}


/**
* Sets the textures that exists
* "ao", "arm", "diff", "disp", "nor", "rough", "spec"
*/
void MaterialPBR::loadTextures()
{
	for (size_t i = 0; i < m_textures.size(); i++) {
		if (m_textures[i].isAllocated()) {
			switch (i)
			{
			case 0: //ao
				m_material.setAoRoughnessMetallicTexture(m_textures[i]);
				m_material.setRoughnessMetallicTexture(m_textures[i]);
				break;
			case 1: //arm (Albedo Rougness Metallic)
				// albedo?
				m_material.setRoughnessTexture(m_textures[i]);
				m_material.setMetallicTexture(m_textures[i]);
				break;
			case 2: //diff
				m_material.setDiffuseTexture(m_textures[i]);
				break;
			case 3: //disp
				m_material.setDisplacementTexture(m_textures[i]);
				break;
			case 4: //nor
				m_material.setNormalTexture(m_textures[i]);
				break;
			case 5: //rough
				m_material.setRoughnessTexture(m_textures[i]);
				break;
			case 6: //spec
				m_material.setSpecularTexture(m_textures[i]);
				break;
			}
		}
	}
}



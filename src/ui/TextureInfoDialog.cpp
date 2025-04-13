/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * TextureInfoDialog class implementation
 *
 *****************************************************/
#include "TextureInfoDialog.h"

#include <Global.h>
#include <imgui.h>


 /**
  * Constructor
  */
TextureInfoDialog::TextureInfoDialog() : ModalDialog() {
}


/**
 * Set attribute to modify
 */
void TextureInfoDialog::useProperty(BaseNode* p_node, const std::string& p_name,  TextureInfo* p_textureInfo) {

	m_node = p_node;
	m_name = p_name;
	m_value = p_textureInfo->getPropertyValue();
	m_Origvalue = m_value;
	m_textureInfo = *p_textureInfo;


}

/**
 * Draw dialog content
 */
void TextureInfoDialog::draw() {


	if (ImGui::BeginPopupModal(m_title.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		int width = m_textureInfo.getTexture()->getWidth();
		int height = m_textureInfo.getTexture()->getHeight();
		float aspectRatio = (float)height / (float) width;;

		width = 500.0f;
		height = width * aspectRatio;

		ImGui::Image(reinterpret_cast<ImTextureID>(m_textureInfo.getTexture()->getTextureData().textureID), ImVec2(width,height));
		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		vector<string> optionsMin = {"Nearest", "Linear", "Nearest (Mipmap nearest)", "Linear (Mipmap nearest)","Nearest (Mipmap linear)", "Linear (Mipmap linear)"};
		vector<int> valuesMin = { GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR };

		vector<string> optionsMax = {"Nearest", "Linear"};
		vector<int> valuesMax = { GL_NEAREST, GL_LINEAR };

		int selectedIndexMin = 0;
		switch (m_textureInfo.getFilterMinimum()) {
		case GL_NEAREST: selectedIndexMin = 0; break;
		case GL_LINEAR: selectedIndexMin = 1; break;
		case GL_NEAREST_MIPMAP_NEAREST: selectedIndexMin = 2; break;
		case GL_LINEAR_MIPMAP_NEAREST: selectedIndexMin = 3; break;
		case GL_NEAREST_MIPMAP_LINEAR: selectedIndexMin = 4; break;
		case GL_LINEAR_MIPMAP_LINEAR: selectedIndexMin = 5; break;
		}

		const char* itemsMin[6] = { optionsMin[0].c_str(), optionsMin[1].c_str(), optionsMin[2].c_str(), optionsMin[3].c_str(), optionsMin[4].c_str(), optionsMin[5].c_str() };

		int selectedIndexMax = 0;
		switch(m_textureInfo.getFilterMaximum()) {
			case GL_NEAREST: selectedIndexMax = 0; break;
			case GL_LINEAR: selectedIndexMax = 1; break;
		}

		const char* itemsMax[2] = { optionsMax[0].c_str(), optionsMax[1].c_str() };


		ImGui::Text("Filters (Min/Max):");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(180);
		if (ImGui::Combo("##filter_min", &selectedIndexMin, itemsMin, IM_ARRAYSIZE(itemsMin))) {
			int minFilter = GL_NEAREST;
			switch(selectedIndexMin) {
				case 0: minFilter = GL_NEAREST; break;
				case 1: minFilter = GL_LINEAR; break;
				case 2: minFilter = GL_NEAREST_MIPMAP_NEAREST; break;
				case 3: minFilter = GL_LINEAR_MIPMAP_NEAREST; break;
				case 4: minFilter = GL_NEAREST_MIPMAP_LINEAR; break;
				case 5: minFilter = GL_LINEAR_MIPMAP_LINEAR; break;
			}
			m_textureInfo.setMinMaxFilters(minFilter, m_textureInfo.getFilterMaximum());
		}
		ImGui::SameLine();

		ImGui::SetNextItemWidth(180);
		if (ImGui::Combo("##filter_max", &selectedIndexMax, itemsMax, IM_ARRAYSIZE(itemsMax))) {
			int maxFilter = GL_NEAREST;
			if (selectedIndexMax == 1) {
				maxFilter = GL_LINEAR;
			}
			m_textureInfo.setMinMaxFilters(m_textureInfo.getFilterMinimum(), maxFilter);
		}

		ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::Separator();
		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		if (ImGui::Button("Load file")) {

			ofFileDialogResult result = ofSystemLoadDialog("Select a texture file", false, "images/textures/");
			if (result.bSuccess) {
				string path = result.getPath();
				m_textureInfo.loadTexture(TEXTURE_FILE, path);
			}
		}

		ImGui::SameLine();

		if (ImGui::Button("Color")) {

		}

		ImGui::SameLine();
		if (ImGui::Button("Perlin Noise")) {

			m_textureInfo.loadTexture(TEXTURE_PROCGEN, "perlin");
		}

		ImGui::SameLine();
		ImGui::SetCursorPosX(360.0f);
		if (ImGui::Button("Apply Changes")) {

			std::string new_value = m_textureInfo.getPropertyValue();
			if (m_title == "Change Main Texture") {
				Global::m_actions.addAction(m_node, "Main Texture", m_Origvalue, new_value);
			} else {
				Global::m_actions.addAction(m_node, "Normal Texture", m_Origvalue, new_value);
			}

			ImGui::CloseCurrentPopup();
			m_isOpen = false;
		}

		ImGui::SameLine();

		if (ImGui::Button("Cancel"))
		{
			ImGui::CloseCurrentPopup();
			m_isOpen = false;
		}

		ImGui::EndPopup();
	}
}

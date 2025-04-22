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

		vector<string> optionsWrap = {"Repeat", "Mirrored Repeat", "Clamp to edge", "Clamp to border", "Mirror clamp to edge"};
		int selectedIndexWrap = 0;
		switch(m_textureInfo.getTextureWrapMode()) {
			case GL_REPEAT: selectedIndexWrap = 0; break;
			case GL_MIRRORED_REPEAT: selectedIndexWrap = 1; break;
			case GL_CLAMP_TO_EDGE: selectedIndexWrap = 2; break;
			case GL_CLAMP_TO_BORDER: selectedIndexWrap = 3; break;
			case GL_MIRROR_CLAMP_TO_EDGE: selectedIndexWrap = 4; break;
		}

		const char* itemsWrap[5] = { optionsWrap[0].c_str(), optionsWrap[1].c_str(), optionsWrap[2].c_str(), optionsWrap[3].c_str(), optionsWrap[4].c_str() };

		ImGui::Text("Texture Wrap:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(180);
		if (ImGui::Combo("##wrap_mode", &selectedIndexWrap, itemsWrap, IM_ARRAYSIZE(itemsWrap))) {
			int wrapMode = GL_NEAREST;
			switch(selectedIndexMin) {
				case 0: wrapMode = GL_NEAREST; break;
				case 1: wrapMode = GL_MIRRORED_REPEAT; break;
				case 2: wrapMode = GL_CLAMP_TO_EDGE; break;
				case 3: wrapMode = GL_CLAMP_TO_BORDER; break;
				case 4: wrapMode = GL_MIRROR_CLAMP_TO_EDGE; break;
			}
			m_textureInfo.setTextureWrap(wrapMode);
		}
		ImGui::SameLine();
		ImGui::Text("Scale:");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		float textureScale = m_textureInfo.getTextureScale();
		if (ImGui::InputFloat("##texture_scale", &textureScale, 1.0f, 10.0f, "%.3f")) {
			m_textureInfo.setTextureScale(textureScale);
		}

		ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::Separator();
		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		if (ImGui::Button("Load file")) {

#ifdef TARGET_WIN32
			ofFileDialogResult result = ofSystemLoadDialog("Select a texture file", false, "images\\textures\\");
#else
			ofFileDialogResult result = ofSystemLoadDialog("Select a texture file", false, "images/textures/");
#endif

			if (result.bSuccess) {
				std::filesystem::path selectedPath(result.getPath());
				std::filesystem::path basePath(ofToDataPath("", true)); // absolute path to bin/data

				std::filesystem::path relative = std::filesystem::relative(selectedPath, basePath);

				std::string full_path = "data/" + relative.string();
				std::replace(full_path.begin(), full_path.end(), '\\', '/');
				m_textureInfo.loadTexture(TEXTURE_FILE, full_path);
			}
		}

		ImGui::SameLine();

		static const char* itemsColor[] = { "Color", "White","Black","Red", "Green", "Blue", "Yellow" };
		static int currentItemColor = 0;

		ImGui::SetNextItemWidth(60);
		if (ImGui::Combo("##color", &currentItemColor,  itemsColor, IM_ARRAYSIZE(itemsColor)))
		{
			switch(currentItemColor) {
				case 1: m_textureInfo.loadTexture(TEXTURE_FLAT_COLOR, ofFloatColor(1,1,1)); break;
				case 2: m_textureInfo.loadTexture(TEXTURE_FLAT_COLOR, ofFloatColor(0,0,0)); break;
				case 3: m_textureInfo.loadTexture(TEXTURE_FLAT_COLOR, ofFloatColor(1,0,0)); break;
				case 4: m_textureInfo.loadTexture(TEXTURE_FLAT_COLOR, ofFloatColor(0,1,0)); break;
				case 5: m_textureInfo.loadTexture(TEXTURE_FLAT_COLOR, ofFloatColor(0,0,1)); break;
				case 6: m_textureInfo.loadTexture(TEXTURE_FLAT_COLOR, ofFloatColor(1,1,0)); break;
			}
			currentItemColor = 0;
		}

		ImGui::SameLine();

		const char* itemsProcGen[] = { "Proc. Gen.", "Perlin Noise", "Checkerboard","Radial Gradient" };
		int currentItemProcGen = 0;
		ImGui::SetNextItemWidth(100);
		if (ImGui::Combo("##procgen", &currentItemProcGen, itemsProcGen, IM_ARRAYSIZE(itemsProcGen))) {
			// Option changed
			std::cout << "Selected: " << currentItemProcGen << std::endl;
			switch(currentItemProcGen) {
				case 1: m_textureInfo.loadTexture(TEXTURE_PROCGEN, std::string("perlin"));break;
				case 2: m_textureInfo.loadTexture(TEXTURE_PROCGEN, std::string("checkerboard"));break;
				case 3: m_textureInfo.loadTexture(TEXTURE_PROCGEN, std::string("radial_gradient"));break;
			}
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

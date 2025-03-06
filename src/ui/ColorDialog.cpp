/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * ColorDialog class implementation
 *
 *****************************************************/
#include "ColorDialog.h"

#include <Global.h>
#include <imgui.h>


/**
 * Constructor
 */
ColorDialog::ColorDialog() : ModalDialog() {
}


/**
 * Set attribute to modify
 */
void ColorDialog::useProperty(BaseNode* p_node, const std::string& p_name, ofFloatColor p_value) {

	m_node = p_node;
	m_name = p_name;
	m_value = p_value;
	m_OrigValue = p_value;

	Color c = Color(m_value.r*255, m_value.g * 255, m_value.b * 255 ,0.00f, m_value.a * 255);
	m_currentColorRGB = m_converter->TransformToRGB(c);
	m_colorParameters.clear();
	m_colorParameters = m_converter->getParameters(c);

}


/**
 * Draw color picker dialog
 */
void ColorDialog::draw() {

	if (ImGui::BeginPopupModal(m_title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("Color Space");
		ImGui::SameLine(100);

		ImGui::BeginGroup();

		if (m_converter->getName() == "RGB") {
			ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);

			if (ImGui::Button("RGB")) {
				changeColorConverter(&m_converterRGB);
			}

			ImGui::PopStyleColor(2);
		} else {
			if (ImGui::Button("RGB")) {
				changeColorConverter(&m_converterRGB);
			}

		}

		ImGui::SameLine();


		if (m_converter->getName() == "HSV") {
			ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
			if (ImGui::Button("HSV")) {
				changeColorConverter(&m_converterHSV);
			}
			ImGui::PopStyleColor(2);
		} else {
			if (ImGui::Button("HSV")) {
				changeColorConverter(&m_converterHSV);
			}
		}

		ImGui::SameLine();

		if (m_converter->getName() == "CMYK") {
			ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
			if (ImGui::Button("CMYK")) {
				changeColorConverter(&m_converterCMYK);
			}
			ImGui::PopStyleColor(2);

		} else {
			if (ImGui::Button("CMYK")) {
				changeColorConverter(&m_converterCMYK);
			}
		}

		ImGui::EndGroup();
		for (auto& param : m_colorParameters) {
			int value = param.get();
			ImGui::Text(param.getName().c_str());
			ImGui::SameLine(100);
			ImGui::SliderInt(("##" + param.getName()).c_str(), &value, param.getMin(), param.getMax());
			param.set(value);
		}
		std::vector<int> colorValues = getColorParameterValues();
		Color c = Color(static_cast<float>(colorValues[0]),
						static_cast<float>(colorValues[1]),
						static_cast<float>(colorValues[2]),
						static_cast<float>(colorValues[3]),
						static_cast<float>(colorValues[4]));
		m_currentColorRGB = m_converter->TransformToRGB(c);

		float color[4] = {
			static_cast<float>(m_currentColorRGB.getRed()) / 255.0f,
			static_cast<float>(m_currentColorRGB.getGreen()) / 255.0f,
			static_cast<float>(m_currentColorRGB.getBlue()) / 255.0f,
			static_cast<float>(m_currentColorRGB.getAlpha()) / 255.0f };

		ImGui::Text("Color Value");
		ImGui::SameLine(100);
		ImGui::ColorButton("ColorSample",
							ImVec4(color[0], color[1], color[2], color[3]),
							ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaPreview, ImVec2(210, 48));

		ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::Separator();
		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		ImGui::SetCursorPosX(80.0f);

		if (ImGui::Button("Apply Changes"))
		{
			std::string parameterName = m_title;
			parameterName.erase(0,7);
			Global::m_actions.addAction(m_node, parameterName, m_OrigValue, ofFloatColor(color[0], color[1], color[2], color[3]));
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


/**
 *  Change current color converter
 */
void ColorDialog::changeColorConverter(ColorConverter* p_colorConverter) {
	m_converter = p_colorConverter;
	Color c = m_converter->TransformFromRGB(m_currentColorRGB);
	m_currentColorRGB = m_converter->TransformToRGB(c);
	m_colorParameters.clear();
	m_colorParameters = m_converter->getParameters(c);
}


/**
 * Get color parameters
 */
std::vector<int> ColorDialog::getColorParameterValues() const {
	std::vector<int> values;
	for (const auto& param : m_colorParameters) {
		values.push_back(param.get());
	}
	if (values.size() == 4) {
		values.push_back(values[3]);
	}
	return values;
}

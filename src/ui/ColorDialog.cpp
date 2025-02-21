#include "ColorDialog.h"
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
	converter = new ColorConverterRGB();
	Color c = Color(m_value.r*255, m_value.g * 255, m_value.b * 255 ,0.00f, m_value.a * 255);
	currentColorRGB = converter->TransformToRGB(c);
	colorParameters.clear();
	colorParameters = converter->getParameters(c);

}

void ColorDialog::draw() {

	if (ImGui::BeginPopupModal(m_title.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::BeginGroup();
		if (ImGui::Button("RGB")) {
			changeColorConverter(new ColorConverterRGB());
		}
		ImGui::SameLine();
		if (ImGui::Button("HSV")) {
			changeColorConverter(new ColorConverterHSV());
		}
		ImGui::SameLine();
		if (ImGui::Button("CMYK")) {
			changeColorConverter(new ColorConverterCMYK());
		}
		ImGui::EndGroup();
		for (auto& param : colorParameters) {
			int value = param.get();
			ImGui::SliderInt(param.getName().c_str(), &value, param.getMin(), param.getMax());
			param.set(value);
		}
		std::vector<int> colorValues = getColorParameterValues();
		Color c = Color(colorValues[0], colorValues[1], colorValues[2], colorValues[3], colorValues[4]);
		currentColorRGB = converter->TransformToRGB(c);

		float color[4] = { currentColorRGB.getRed() / 255.0f, currentColorRGB.getGreen() / 255.0f, currentColorRGB.getBlue() / 255.0f, currentColorRGB.getAlpha() / 255.0f };
		ImGui::ColorButton("ColorSample", ImVec4(color[0], color[1], color[2], color[3]), ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_AlphaPreview);
		ImGui::SameLine();


		
		if (ImGui::Button("Apply Changes"))
		{
			std::string parameterName = m_title.c_str();
			parameterName.erase(0,7);
			m_node->setProperty(parameterName,ofFloatColor(color[0], color[1], color[2], color[3]));
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

void ColorDialog::changeColorConverter(ColorConverter* colorConverter) {
	converter = colorConverter;
	Color c = converter->TransformFromRGB(currentColorRGB);
	currentColorRGB = converter->TransformToRGB(c);
	colorParameters.clear();
	colorParameters = converter->getParameters(c);
}

std::vector<int> ColorDialog::getColorParameterValues() const {
	std::vector<int> values;
	for (const auto& param : colorParameters) {
		values.push_back(param.get());
	}
	if (values.size() == 4) {
		values.push_back(values[3]);
	}
	return values;
}

#include "ColorConverterCYMK.h"

ColorConverterCYMK::ColorConverterCYMK() {
	m_name = "CYMK";
}

ColorRGB ColorConverterCYMK::TransformToRGB(Color p_currentColor) {
	float black = (1 - p_currentColor.getValue4() / 100);
	int r = (int)(255 * (1 - p_currentColor.getValue1() / 100) * black);
	int g = (int)(255 * (1 - p_currentColor.getValue2() / 100) * black);
	int b = (int)(255 * (1 - p_currentColor.getValue3() / 100) * black);
	ColorRGB arc(r, g, b, p_currentColor.getAlpha());
	return arc;
}

Color ColorConverterCYMK::TransformFromRGB(ColorRGB p_currentColor) {
	float black = 1 - (std::max(std::max(p_currentColor.getRed(), p_currentColor.getGreen()), 
		p_currentColor.getBlue()) / static_cast<float>(255));
	float cyan = (1 - p_currentColor.getRed() / static_cast<float>(255) - black) / (1 - black);
	float magenta = (1 - p_currentColor.getGreen() / static_cast<float>(255) - black) / (1 - black);
	float yellow = (1 - p_currentColor.getBlue() / static_cast<float>(255) - black) / (1 - black);
	black = round(black * 100);
	cyan = round(cyan * 100);
	magenta = round(magenta * 100);
	yellow = round(yellow * 100);
	Color ac(cyan, magenta, yellow, black, p_currentColor.getAlpha());
	return ac;
}

ofFloatColor ColorConverterCYMK::GetColor(Color p_currentColor) {
	ColorRGB rgb = TransformToRGB(p_currentColor);
	return ofFloatColor(rgb.getRed(), rgb.getGreen(), rgb.getBlue(), rgb.getAlpha());
}

std::vector<ofParameter<float>> ColorConverterCYMK::getParameters(Color currentKnightColor) {
	std::vector<ofParameter<float>> params;
	params.push_back(ofParameter<float>("Cyan", currentKnightColor.getValue1(), 0.0f, 100.0f));
	params.push_back(ofParameter<float>("Yellow", currentKnightColor.getValue2(), 0.0f, 100.0f));
	params.push_back(ofParameter<float>("Magenta", currentKnightColor.getValue3(), 0.0f, 100.0f));
	params.push_back(ofParameter<float>("Black", currentKnightColor.getValue3(), 0.0f, 100.0f));
	params.push_back(ofParameter<float>("Alpha", currentKnightColor.getAlpha(), 0.0f, 100.0f));
	return params;
}

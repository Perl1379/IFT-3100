#include "ColorConverterCMYK.h"

ColorConverterCMYK::ColorConverterCMYK() {
	m_name = "CMYK";
}

ColorRGB ColorConverterCMYK::TransformToRGB(Color p_currentColor) {
	float black = (1 - p_currentColor.getValue4() / 100);
	int r = (int)(255 * (1 - p_currentColor.getValue1() / 100) * black);
	int g = (int)(255 * (1 - p_currentColor.getValue2() / 100) * black);
	int b = (int)(255 * (1 - p_currentColor.getValue3() / 100) * black);
	ColorRGB arc(r, g, b, p_currentColor.getAlpha());
	return arc;
}

Color ColorConverterCMYK::TransformFromRGB(ColorRGB p_currentColor) {
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

ofFloatColor ColorConverterCMYK::GetColor(Color p_currentColor) {
	ColorRGB rgb = TransformToRGB(p_currentColor);
	return ofFloatColor(rgb.getRed(), rgb.getGreen(), rgb.getBlue(), rgb.getAlpha());
}

std::vector<ofParameter<int>> ColorConverterCMYK::getParameters(Color p_currentColor) {
	std::vector<ofParameter<int>> params;
	params.push_back(ofParameter<int>("Cyan", p_currentColor.getValue1(), 0, 100));
	params.push_back(ofParameter<int>("Magenta", p_currentColor.getValue2(), 0, 100));
	params.push_back(ofParameter<int>("Yellow", p_currentColor.getValue3(), 0, 100));
	params.push_back(ofParameter<int>("Black", p_currentColor.getValue4(), 0, 100));
	params.push_back(ofParameter<int>("Alpha", p_currentColor.getAlpha(), 0, 255));
	return params;
}

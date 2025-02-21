#include "ColorConverterRGB.h"

ColorConverterRGB::ColorConverterRGB() {
	m_name = "RGB";
}

ColorRGB ColorConverterRGB::TransformToRGB(Color p_currentColor) {
	ColorRGB arc(p_currentColor.getValue1(), p_currentColor.getValue2(), p_currentColor.getValue3(), p_currentColor.getAlpha());
	return arc;
}

Color ColorConverterRGB::TransformFromRGB(ColorRGB p_currentColor) {
	float red = p_currentColor.getRed();
	float green = p_currentColor.getGreen();
	float blue = p_currentColor.getBlue();
	Color ac(red, green, blue, 0.0f, p_currentColor.getAlpha());
	return ac;
}

ofFloatColor ColorConverterRGB::GetColor(Color p_currentColor) {
	return ofFloatColor(p_currentColor.getValue1(), p_currentColor.getValue2(), p_currentColor.getValue3(), p_currentColor.getAlpha());
}

std::vector<ofParameter<float>> ColorConverterRGB::getParameters(Color currentKnightColor) {
	std::vector<ofParameter<float>> params;
	params.push_back(ofParameter<float>("Red", currentKnightColor.getValue1(), 0.0f, 255.0f));
	params.push_back(ofParameter<float>("Green", currentKnightColor.getValue2(), 0.0f, 255.0f));
	params.push_back(ofParameter<float>("Blue", currentKnightColor.getValue3(), 0.0f, 255.0f));
	params.push_back(ofParameter<float>("Alpha", currentKnightColor.getAlpha(), 0.0f, 255.0f));
	return params;
}

/*****************************************************
* TP IFT3100H25 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * ColorConverterRGB class implementation
 *
 *****************************************************/
 #include "ColorConverterRGB.h"


/**
 * Constructor
 */
ColorConverterRGB::ColorConverterRGB() {
	m_name = "RGB";
}


/**
 * Transform a color object to RGB
 */
ColorRGB ColorConverterRGB::TransformToRGB(Color p_currentColor) {
	ColorRGB arc(p_currentColor.getValue1(), p_currentColor.getValue2(), p_currentColor.getValue3(), p_currentColor.getAlpha());
	return arc;
}


/**
 * Transform a RGB object to color
 */
Color ColorConverterRGB::TransformFromRGB(ColorRGB p_currentColor) {
	float red = p_currentColor.getRed();
	float green = p_currentColor.getGreen();
	float blue = p_currentColor.getBlue();
	Color ac(red, green, blue, 0.0f, p_currentColor.getAlpha());
	return ac;
}


/**
 * Set color object
 */
ofFloatColor ColorConverterRGB::GetColor(Color p_currentColor) {
	return ofFloatColor(p_currentColor.getValue1(), p_currentColor.getValue2(), p_currentColor.getValue3(), p_currentColor.getAlpha());
}


/**
 *  Get parameters
 */
std::vector<ofParameter<int>> ColorConverterRGB::getParameters(Color p_currentColor) {
	std::vector<ofParameter<int>> params;
	params.push_back(ofParameter<int>("Red", p_currentColor.getValue1(), 0,255));
	params.push_back(ofParameter<int>("Green", p_currentColor.getValue2(), 0, 255));
	params.push_back(ofParameter<int>("Blue", p_currentColor.getValue3(), 0, 255));
	params.push_back(ofParameter<int>("Alpha", p_currentColor.getAlpha(), 0, 255));
	return params;
}

/*****************************************************
* TP IFT3100H25 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * ColorConverterRGB class definition
 *
 *****************************************************/
 #pragma once
#include "ColorConverter.h"

class ColorConverterRGB : public ColorConverter {

public:
	ColorConverterRGB();
	ColorRGB TransformToRGB(Color p_currentColor) override;
	Color TransformFromRGB(ColorRGB p_currentColor) override;
	ofFloatColor GetColor(Color p_currentColor) override;
	std::vector<ofParameter<int>> getParameters(Color p_currentColor) override;

};


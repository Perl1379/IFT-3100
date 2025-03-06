/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * ColorConverterHSV class definition
 *
 *****************************************************/
#pragma once
#include "ColorConverter.h"

class ColorConverterHSV :
    public ColorConverter
{
public:
	ColorConverterHSV();
	ColorRGB TransformToRGB(Color p_currentColor) override;
	Color TransformFromRGB(ColorRGB p_currentColor) override;
	ofFloatColor GetColor(Color p_currentColor) override;
	std::vector<ofParameter<int>> getParameters(Color p_currentColor) override;
};


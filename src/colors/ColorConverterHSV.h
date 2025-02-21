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
	std::vector<ofParameter<float>> getParameters(Color p_currentColor) override;
};


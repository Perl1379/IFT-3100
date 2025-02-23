#pragma once
#include "ColorConverter.h"
class ColorConverterCMYK :
    public ColorConverter
{
public:
	ColorConverterCMYK();
	ColorRGB TransformToRGB(Color p_currentColor) override;
	Color TransformFromRGB(ColorRGB p_currentColor) override;
	ofFloatColor GetColor(Color p_currentColor) override;
	std::vector<ofParameter<int>> getParameters(Color p_currentColor) override;
};


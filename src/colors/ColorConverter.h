/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * ColorConverter class definition
 *
 *****************************************************/
#pragma once
#include "Color.h"
#include "ColorRGB.h"
#include <ofxImGui.h>
#include <ofColor.h>
#include <vector>

class ColorConverter
{
protected:
	std::string m_name;
public:
	ColorConverter();
	virtual ColorRGB TransformToRGB(Color p_currentColor) = 0;
	virtual Color TransformFromRGB(ColorRGB p_currentColor) = 0;
	virtual ofFloatColor GetColor(Color p_currentColor) = 0;
	virtual std::vector<ofParameter<int>> getParameters(Color p_currentColor) = 0;
	std::string getName() const;
};


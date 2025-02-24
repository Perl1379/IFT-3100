/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * ColorDialog class declaration
 *
 *****************************************************/
#pragma once

#include <BaseNode.h>
#include "colors/ColorConverterRGB.h"
#include "colors/ColorConverterCMYK.h"
#include "colors/ColorConverterHSV.h"
#include "ModalDialog.h"

class ColorDialog :	public ModalDialog
{
private:
	BaseNode* m_node;
	std::string m_name;
	ofFloatColor m_OrigValue;
	ofFloatColor m_value;

	ColorConverterRGB m_converterRGB;
	ColorConverterCMYK m_converterCMYK;
	ColorConverterHSV m_converterHSV;
	ColorConverter* m_converter = &m_converterRGB;

	ColorRGB m_currentColorRGB;
	std::vector<ofParameter<int>> m_colorParameters;

	void changeColorConverter(ColorConverter* p_colorConverter);
	std::vector<int> getColorParameterValues() const;

public:
	ColorDialog();
	void useProperty(BaseNode* p_node, const std::string& p_name, ofFloatColor p_value);
	void draw() override;
};


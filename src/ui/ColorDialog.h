#pragma once

#include <BaseNode.h>
#include "colors/ColorConverterRGB.h"
#include "colors/ColorConverterCMYK.h"
#include "colors/ColorConverterHSV.h"
#include "ModalDialog.h"

class ColorDialog :
	public ModalDialog
{
private:
	BaseNode* m_node;
	std::string m_name;
	ofFloatColor m_value;

	ColorConverter* converter = new ColorConverterRGB();
	ColorRGB currentColorRGB;
	std::vector<ofParameter<int>> colorParameters;

	void changeColorConverter(ColorConverter* colorConverter);
	std::vector<int> getColorParameterValues() const;
public:
	ColorDialog();
	void useProperty(BaseNode* p_node, const std::string& p_name, ofFloatColor p_value);
	void draw() override;
};


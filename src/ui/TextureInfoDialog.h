/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * TextureInfoDialog class definition
 *
 *****************************************************/
#pragma once

#include <BaseNode.h>

#include "ModalDialog.h"


class TextureInfoDialog : public ModalDialog {

private:

	BaseNode* m_node;
	std::string m_name;
	std::string m_value;
	std::string m_Origvalue;
	TextureInfo m_textureInfo;



public:
	TextureInfoDialog();
	void useProperty(BaseNode* p_node, const std::string& p_name, TextureInfo* p_textureInfo);
	void draw() override;

};


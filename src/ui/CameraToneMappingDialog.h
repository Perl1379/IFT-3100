/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * CameraToneMappingDialog class definition
 *
 *****************************************************/
#pragma once
#include "Camera.h"
#include "ModalDialog.h"

class CameraToneMappingDialog :
    public ModalDialog
{
private :
	Camera* m_camera;
	int m_currentType;
	std::map<std::string, float> m_uniforms;

public:
	CameraToneMappingDialog();
	void useProperty(Camera* p_camera);
	void draw() override;
};


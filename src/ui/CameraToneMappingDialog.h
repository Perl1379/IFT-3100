#pragma once
#include "Camera.h"
#include "ModalDialog.h"
class CameraToneMappingDialog :
    public ModalDialog
{
private :
	Camera* m_camera;
	float m_tone_mapping_exposure_current;
	float m_tone_mapping_gamma_current;
	bool m_tone_mapping_toggle_current;

public:
	CameraToneMappingDialog();
	void useProperty(Camera* p_camera);
	void draw() override;
};


#include "CameraToneMappingDialog.h"
#include <Global.h>
#include <imgui.h>


CameraToneMappingDialog::CameraToneMappingDialog()
{
}

void CameraToneMappingDialog::useProperty(Camera* p_camera)
{
	m_camera = p_camera;
	m_tone_mapping_exposure_current = m_camera->getToneMappingExposure();
	m_tone_mapping_gamma_current = m_camera->getToneMappingGamma();
	m_tone_mapping_toggle_current = m_camera->getToneMappingToggle();
	m_title = "Camera Tone Mapping";
}

void CameraToneMappingDialog::draw()
{
	if (ImGui::BeginPopupModal(m_title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		
		ImGui::Text("Parameters");
		ImGui::SameLine(100);
		
		float p_tone_mapping_exposure = m_camera->getToneMappingExposure();
		ImGui::Text("tone mapping exposure");
		ImGui::SameLine(100);
		std::string name = "tone mapping exposure";
		ImGui::SliderFloat(("##" + name).c_str(),&p_tone_mapping_exposure, 0.0f, 5.00f);
		m_camera->setToneMappingExposure(p_tone_mapping_exposure);

		
		float p_tone_mapping_gamma = m_camera->getToneMappingGamma();
		ImGui::Text("tone mapping gamma");
		ImGui::SameLine(100);
		name = "tone mapping gamma";
		ImGui::SliderFloat(("##" + name).c_str(), &p_tone_mapping_gamma, 0.0f, 5.00f);
		m_camera->setToneMappingGamma(p_tone_mapping_gamma);

		
		bool p_tone_mapping_toggle = m_camera->getToneMappingToggle();
		ImGui::Text("tone mapping toggle");
		ImGui::SameLine(100);
		name = "tone mapping toggle";
		ImGui::Checkbox(("##" + name).c_str(), &p_tone_mapping_toggle);
		m_camera->setToneMappingToggle(p_tone_mapping_toggle);

		if (ImGui::Button("Apply Changes"))
		{
			ImGui::CloseCurrentPopup();
			m_isOpen = false;
		}

		ImGui::SameLine();

		if (ImGui::Button("Cancel"))
		{
			m_camera->setToneMappingExposure(m_tone_mapping_exposure_current);
			m_camera->setToneMappingGamma(m_tone_mapping_gamma_current);
			m_camera->setToneMappingToggle(m_tone_mapping_toggle_current);
			ImGui::CloseCurrentPopup();
			m_isOpen = false;
		}

		ImGui::EndPopup();
	}
}

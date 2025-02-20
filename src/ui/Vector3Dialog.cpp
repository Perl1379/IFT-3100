/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * Vector3Dialog class implementation
 *
 *****************************************************/
#include "Vector3Dialog.h"
#include <imgui.h>


 /**
  * Constructor
  */
Vector3Dialog::Vector3Dialog() : ModalDialog() {
}


/**
 * Set attribute to modify
 */
void Vector3Dialog::useProperty(BaseNode* p_node, const std::string& p_name, glm::vec3 p_value) {

	m_node = p_node;
	m_name = p_name;
	m_value = p_value;

}

/**
 * Draw dialog content
 */
void Vector3Dialog::draw() {

	if (ImGui::BeginPopupModal(m_title.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("X:");
		ImGui::SameLine();
		ImGui::InputFloat("##X", &m_value.x);
		ImGui::Text("Y:");
		ImGui::SameLine();
		ImGui::InputFloat("##Y", &m_value.y);
		ImGui::Text("Z:");
		ImGui::SameLine();
		ImGui::InputFloat("##Z", &m_value.z);

		ImGui::Dummy(ImVec2(0.0f, 5.0f));
		ImGui::Separator();
		ImGui::Dummy(ImVec2(0.0f, 5.0f));

		if (ImGui::Button("Apply Changes"))
		{
			if (m_title == "Change Position") {
				m_node->setProperty("Position", m_value);
			}
			else if (m_title == "Change Orientation") {
				m_node->setProperty("Orientation", m_value);
			}
			else if (m_title == "Change Scale") {
				m_node->setProperty("Scale", m_value);
			}
			ImGui::CloseCurrentPopup();
			m_isOpen = false;
		}

		ImGui::SameLine();

		if (ImGui::Button("Cancel"))
		{
			ImGui::CloseCurrentPopup();
			m_isOpen = false;
		}

		ImGui::EndPopup();
	}
}

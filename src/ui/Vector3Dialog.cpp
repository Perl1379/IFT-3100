/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * Vector3Dialog class implementation
 *
 *****************************************************/
#include "Vector3Dialog.h"

#include <Global.h>
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
	m_Origvalue = m_value;

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
		ImGui::SetCursorPosX(80.0f);

		if (ImGui::Button("Apply Changes"))
		{
			if (m_title == "Change Position") {
				Global::m_actions.addAction(m_node, "Position", m_Origvalue, m_value);
			}
			else if (m_title == "Change Orientation") {
				Global::m_actions.addAction(m_node, "Orientation", m_Origvalue, m_value);
			}
			else if (m_title == "Change Scale") {
				Global::m_actions.addAction(m_node, "Scale", m_Origvalue, m_value);
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

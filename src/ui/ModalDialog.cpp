/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * ModelDialog class implementation
 *
 *****************************************************/
#include "ModalDialog.h"

#include <imgui.h>
#include <ofLog.h>

/**
  * Dialog constructor
  */
ModalDialog::ModalDialog() : m_isOpen(false) {

}

/**
* Set dialog title
*/
void ModalDialog::setTitle(const std::string& p_title) {

	m_title = p_title;

}


/**
 * Open dialog
 */
void ModalDialog::openDialog() {

	ImGui::OpenPopup(m_title.c_str());
	m_isOpen = true;
}


/**
 * Draw dialog content
 */
void ModalDialog::draw() {

	if (ImGui::BeginPopupModal(m_title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("This is a reusable modal dialog.");
		ImGui::Separator();

		if (ImGui::Button("OK"))
		{
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


/**
 *  Check if the dialog is already open
 */
bool ModalDialog::isOpen() {
	return m_isOpen;
}


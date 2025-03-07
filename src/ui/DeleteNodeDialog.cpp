/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * DeleteNodeDialog class implementation
 *
 *****************************************************/
#include "DeleteNodeDialog.h"

#include <Global.h>
#include <imgui.h>


/**
 * Constructor
 */
DeleteNodeDialog::DeleteNodeDialog() : ModalDialog() {

    setTitle("Delete Node");

}


/**
 * Draw callback function
 */
void DeleteNodeDialog::draw() {
    if (ImGui::BeginPopupModal(m_title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::TextColored(ImVec4(1, 0.5, 0.5, 1), "Warning: this action cannot be undone!");
        ImGui::Text("Are you sure you want to continue?");

        ImGui::Dummy(ImVec2(0.0f, 5.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 5.0f));
        ImGui::SetCursorPosX(100);
        if (ImGui::Button("Yes"))
        {
            ImGui::CloseCurrentPopup();
            m_isOpen = false;

           
            BaseNode* node = Global::m_level.getTree()->findNode(Global::m_selectedNode);
            BaseNode* parent = node->getParent();

           
            parent->removeChild(Global::m_selectedNode);
            Global::m_selectedNode = -1;

        }

        ImGui::SameLine();

        if (ImGui::Button("No"))
        {
            ImGui::CloseCurrentPopup();
            m_isOpen = false;
        }

        ImGui::EndPopup();
    }
}

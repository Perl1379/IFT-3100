/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * FileGeneratedDialog class implementation
 *
 *****************************************************/
#include "FileGeneratedDialog.h"

#include <imgui.h>
#include <ofFileUtils.h>
#include <ofUtils.h>


/**
 * Constructor
 */
FileGeneratedDialog::FileGeneratedDialog() : ModalDialog() {
    setTitle("File Generated");
}


/**
 * Set content
 */
void FileGeneratedDialog::setContent(const std::string &p_content, const std::string &p_filename) {
    m_content = p_content;
    m_filename = p_filename;
}


/**
 * Draw dialog content
 */
void FileGeneratedDialog::draw() {


    if (ImGui::BeginPopupModal(m_title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("%s", m_content.c_str());
        ImGui::Dummy(ImVec2(0.0f, 10.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 5.0f));
        ImGui::SetCursorPosX(64);
        if (ImGui::Button("Open"))
        {
            ImGui::CloseCurrentPopup();
            m_isOpen = false;

            std::string filePath = ofToDataPath("output/" + m_filename, true);

        #ifdef _WIN32
                    ofSystem("start \"\" \"" + filePath + "\"");
        #elif defined(__APPLE__)
                    ofSystem("open \"" + filePath + "\"");
        #else // Linux
                    ofSystem("xdg-open \"" + filePath + "\"");
        #endif

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

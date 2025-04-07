/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * CameraToneMappingDialog class implementation
 *
 *****************************************************/
#include "CameraToneMappingDialog.h"
#include <Global.h>
#include <imgui.h>

/**
 * Constructor
 */
CameraToneMappingDialog::CameraToneMappingDialog() {
}


/**
 * Use property (in this case, the Camera object)
 */
void CameraToneMappingDialog::useProperty(Camera *p_camera) {
    m_camera = p_camera;
    m_title = "Camera Tone Mapping";
    m_currentType = p_camera->getTonemapType();
    m_uniforms = p_camera->getTonemapUniforms();
}


/**
 * Draw dialog
 */
void CameraToneMappingDialog::draw() {
    if (ImGui::BeginPopupModal(m_title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Type");
        ImGui::SameLine(100);

        // Doing -1 to remove the index (the 'initialSelection')
        std::vector<const char *> cstrings{};
        cstrings.push_back("No tonemap");
        cstrings.push_back("Grayscale");

        ImGui::PushItemWidth(186.0f);
        if (ImGui::Combo("##Type", &m_currentType, cstrings.data(), cstrings.size())) {
            switch(m_currentType) {
                case TONEMAP_TYPE::NO_TONEMAP:
                {
                    m_uniforms.clear();
                }
                break;

                case TONEMAP_TYPE::GRAYSCALE:
                {
                    m_uniforms.clear();
                    m_uniforms["brightness"] = 1.0f;
                }
            }
        }

        for (auto& uniform : m_uniforms) {

            std::string label = uniform.first;
            label[0] = std::toupper(label[0]);
            ImGui::Text(label.c_str());
            ImGui::SameLine(100);
            ImGui::InputFloat(("##" + uniform.first).c_str(),&uniform.second);
        }

        ImGui::Dummy(ImVec2(0.0f, 5.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 5.0f));

        ImGui::SetCursorPosX(80.0f);


        if (ImGui::Button("Apply Changes")) {
            m_camera->setTonemapType((TONEMAP_TYPE) m_currentType);
            m_camera->setTonemapUniforms(m_uniforms);
            ImGui::CloseCurrentPopup();
            m_isOpen = false;
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
            m_isOpen = false;
        }

        ImGui::EndPopup();
    }
}

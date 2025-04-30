/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * NewLevelDialog class implementation
 *
 *****************************************************/
#include "NewLevelDialog.h"

#include <Global.h>
#include <imgui.h>

/**
 * Constructor
 */
NewLevelDialog::NewLevelDialog() : ModalDialog() {
    setTitle("New Level");
}


/**
 * Draw callback function
 */
void NewLevelDialog::draw() {
    if (ImGui::BeginPopupModal(m_title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::TextColored(ImVec4(1, 0.5, 0.5, 1), "Warning: this action cannot be undone!");
        ImGui::Text("Are you sure you want to continue?");

        ImGui::Dummy(ImVec2(0.0f, 5.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 5.0f));
        ImGui::SetCursorPosX(100);
        if (ImGui::Button("Yes")) {
            ImGui::CloseCurrentPopup();
            m_isOpen = false;

            Global::m_level.reset();

            // Init lights
            for (int i=0;i<8;i++) {
                Global::m_lights[i].setup();
                Global::m_lights[i].setAttenuation(0.0005);
                Global::m_lights[i].setLightType(POINT_LIGHT);
                Global::m_lights[i].setPosition(ofVec3f(0, 1000 - (i * 200), 2000));

                if (i > 0) {
                    Global::m_lights[i].setEnabled(false);
                } else {
                    Global::m_lights[i].setEnabled(true);

                }
            }

        }

        ImGui::SameLine();

        if (ImGui::Button("No")) {
            ImGui::CloseCurrentPopup();
            m_isOpen = false;
        }

        ImGui::EndPopup();
    }
}

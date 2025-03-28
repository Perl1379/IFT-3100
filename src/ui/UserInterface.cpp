/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * UserInterface class implementation
 *
 *****************************************************/
#include "UserInterface.h"

#include <imgui_internal.h>
#include <ofAppRunner.h>
#include <ofGraphics.h>

#ifdef _WIN32
	#include <direct.h>
	#define mkdir _mkdir
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

#include <LevelPersistence.h>
#include <LightNode.h>

#include "Global.h"

/**
 * Setup user interface
 */
void UserInterface::setup() {
    m_gui.setup();

    // Load images needed by the toolbar
    ofImage imgToolbarNewLevel;
    imgToolbarNewLevel.load("images/ui/toolbar_buttons/new_level.png");
    m_textureToolbarNewLevel = imgToolbarNewLevel.getTexture();

    ofImage imgToolbarLoadLevel;
    imgToolbarLoadLevel.load("images/ui/toolbar_buttons/load_level.png");
    m_textureToolbarLoadLevel = imgToolbarLoadLevel.getTexture();

    ofImage imgToolbarSaveLevel;
    imgToolbarSaveLevel.load("images/ui/toolbar_buttons/save_level.png");
    m_textureToolbarSaveLevel = imgToolbarSaveLevel.getTexture();

    ofImage imgToolbarGenerateAtlas;
    imgToolbarGenerateAtlas.load("images/ui/toolbar_buttons/generate.png");
    m_textureToolbarGenerateBigTexture = imgToolbarGenerateAtlas.getTexture();

    ofImage imgToolbarHistogram;
    imgToolbarHistogram.load("images/ui/toolbar_buttons/histogram.png");
    m_textureToolbarHistogram = imgToolbarHistogram.getTexture();

    ofImage imgToolbarToggleCameras;
    imgToolbarToggleCameras.load("images/ui/toolbar_buttons/toggle_cameras.png");
    m_textureToolbarToggleCameras = imgToolbarToggleCameras.getTexture();

    ofImage imgToolbarToggleCamerasPressed;
    imgToolbarToggleCamerasPressed.load("images/ui/toolbar_buttons/toggle_cameras_pressed.png");
    m_textureToolbarToggleCamerasPressed = imgToolbarToggleCamerasPressed.getTexture();

    ofImage imgToolbarSequence;
    imgToolbarSequence.load("images/ui/toolbar_buttons/sequence.png");
    m_textureToolbarSequence = imgToolbarSequence.getTexture();

    ofImage imgToolbarSequencePressed;
    imgToolbarSequencePressed.load("images/ui/toolbar_buttons/sequence_pressed.png");
    m_textureToolbarSequencePressed = imgToolbarSequencePressed.getTexture();

    ofImage imgNotVisible;
    imgNotVisible.load("images/ui/not_visible.png");
    m_textureNotVisible = imgNotVisible.getTexture();

    //changeCursor();
    ofHideCursor();

    // Load skybox names
    ofDirectory dirSkybox;
    dirSkybox.listDir("skybox/images/");

    for (int i = 0; i < dirSkybox.size(); i++) {
        m_availableSkyboxes.push_back(dirSkybox.getName(i));
    }

    std::sort(m_availableSkyboxes.begin(), m_availableSkyboxes.end());
    Global::m_skybox.setup(m_availableSkyboxes[4]);
}


/**
 * draw user interface
 */
void UserInterface::draw() {
    m_gui.begin();

    m_hoveredWindow = "";
    Global::m_cursorManager.change("cursor");
    drawMenu();
    drawToolbar();
    drawTree();
    drawTreeActions();
    drawProperties();
    drawViewports();
    drawStatus();


    if (m_initialDraw) {
        m_initialDraw = false;
        ImGui::SetWindowFocus("Main Camera");
    }
    Global::m_cursorManager.draw();

    m_gui.end();
}


/**
 * Draw the menu
 */
void UserInterface::drawMenu() {
    // Draw menu
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("New Level")) {
                onNewLevel();
            }
            if (ImGui::MenuItem("Load Level")) {
                onLoadLevel();
            }
            if (ImGui::MenuItem("Save Level")) {
                onSaveLevel();
            }

            if (ImGui::MenuItem("Generate Triptych")) {
                onGenerateTriptych();
            }

            if (ImGui::MenuItem("Exit")) {
                ofExit(0);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo")) {
                onHistoryUndo();
            }
            if (ImGui::MenuItem("Redo")) {
                onHistoryRedo();
            }
            ImGui::EndMenu();
        }


        if (ImGui::BeginMenu("Occlusion")) {
            bool noOcclusion = (Global::m_cameras[0].getOcclusion() == NO_OCCLUSION);

            if (ImGui::MenuItem("No Occlusion", nullptr, &noOcclusion)) {
                Global::m_cameras[0].setOcclusion(NO_OCCLUSION);
                Global::m_cameras[1].setOcclusion(NO_OCCLUSION);
                Global::m_cameras[2].setOcclusion(NO_OCCLUSION);
            }

            bool frustumCulling = (Global::m_cameras[0].getOcclusion() == FRUSTUM_CULLING);
            if (ImGui::MenuItem("Frustum Culling", nullptr, &frustumCulling)) {
                Global::m_cameras[0].setOcclusion(FRUSTUM_CULLING);
                Global::m_cameras[1].setOcclusion(FRUSTUM_CULLING);
                Global::m_cameras[2].setOcclusion(FRUSTUM_CULLING);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Skybox")) {
            for (int i = 0; i < m_availableSkyboxes.size(); i++) {
                bool selected = false;
                if (Global::m_skybox.getCurrentSkybox() == m_availableSkyboxes[i]) {
                    selected = true;
                }

                if (ImGui::MenuItem(m_availableSkyboxes[i].c_str(), nullptr, &selected)) {
                    Global::m_actions.addAction(nullptr, "skybox_change",
                                                Global::m_skybox.getCurrentSkybox(), m_availableSkyboxes[i]);
                }
            }
            ImGui::EndMenu();
        }

        // if (ImGui::BeginMenu("Help")) {
        //     if (ImGui::MenuItem("Key Bindings")) {
        //         onShowKeyBindings();
        //     }
        //
        //     if (ImGui::MenuItem("About Adventure Party Maker")) {
        //         onAboutProgram();
        //     }
        //     ImGui::EndMenu();
        // }


        ImGui::EndMainMenuBar(); // End the menu bar
    }
}


/**
 * Draw the toolbar_buttons
 */
void UserInterface::drawToolbar() {
    ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetFrameHeight()), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(ofGetWidth(), TOOLBAR_HEIGHT));

    ImGuiWindowFlags toolbarFlags = ImGuiWindowFlags_NoTitleBar |
                                    ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoCollapse |
                                    ImGuiWindowFlags_NoScrollbar;

    if (ImGui::Begin("Toolbar", nullptr, toolbarFlags)) {
        if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(m_textureToolbarNewLevel.getTextureData().textureID),
                               ImVec2(48, 48))) {
            onNewLevel();
        }
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip(
            Global::m_tooltipMessages.toolbar_new);
        ImGui::SameLine();

        if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(m_textureToolbarLoadLevel.getTextureData().textureID),
                               ImVec2(48, 48))) {
            onLoadLevel();
        }
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip(
            Global::m_tooltipMessages.toolbar_load);
        ImGui::SameLine();

        if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(m_textureToolbarSaveLevel.getTextureData().textureID),
                               ImVec2(48, 48))) {
            onSaveLevel();
        }
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip(
            Global::m_tooltipMessages.toolbar_save);
        ImGui::SameLine();

        if (ImGui::ImageButton(
            reinterpret_cast<ImTextureID>(m_textureToolbarGenerateBigTexture.getTextureData().textureID),
            ImVec2(48, 48))) {
            onGenerateTriptych();
        }

        if (m_fileGeneratedDialog.isOpen()) {
            m_fileGeneratedDialog.draw();
        }


        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip(
            Global::m_tooltipMessages.toolbar_generate);
        ImGui::SameLine();

        if (ImGui::ImageButton(reinterpret_cast<ImTextureID>(m_textureToolbarHistogram.getTextureData().textureID),
                               ImVec2(48, 48))) {
            m_histogramDialog.m_onlyOneCamera = m_onlyOneCamera;
            m_histogramDialog.openDialog();
        }

        if (m_histogramDialog.isOpen()) {
            m_histogramDialog.draw();
        }


        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip(
            Global::m_tooltipMessages.toolbar_histogram);
        ImGui::SameLine();

        auto sequence_tooltip = Global::m_sequenceCount == -1
                                    ? Global::m_tooltipMessages.toolbar_sequence_start
                                    : Global::m_tooltipMessages.toolbar_sequence_stop;

        if (ImGui::ImageButton(
            reinterpret_cast<ImTextureID>(Global::m_sequenceCount != -1
                                              ? m_textureToolbarSequencePressed.getTextureData().textureID
                                              : m_textureToolbarSequence.getTextureData().textureID),
            ImVec2(48, 48))) {
            if (Global::m_sequenceCount == -1) {
                Global::m_sequenceCount = 0;
                Global::m_sequenceName = "record_" + ofGetTimestampString("%y%m%d-%H%M%S-%i");
                std::string filePath = ofToDataPath("output/" + Global::m_sequenceName, true);
                mkdir(filePath.c_str()
#ifndef _WIN32
                      , 0777
#endif
                );

                Global::m_sequenceTotalDelta = 0.0f;
            } else {
                Global::m_sequenceCount = -1;
            }
        }

        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip(sequence_tooltip);
        ImGui::SameLine();


        if (ImGui::ImageButton(
            reinterpret_cast<ImTextureID>(m_onlyOneCamera
                                              ? m_textureToolbarToggleCamerasPressed.getTextureData().textureID
                                              : m_textureToolbarToggleCameras.getTextureData().textureID),
            ImVec2(48, 48))) {
            onToggleCameras();
        }
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip(
            Global::m_tooltipMessages.toolbar_toggleCam);
        ImGui::SameLine();


        ImGui::End();
    }
}


/**
 * Draw tree containing nodes
 */
void UserInterface::drawTree() {
    // Define position and size
    ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetFrameHeight() + TOOLBAR_HEIGHT + 6), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(LEFTPANEL_WIDTH, TREEVIEW_HEIGHT), ImGuiCond_Always);

    if (ImGui::Begin("Level", nullptr,
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse)) {
        ImGui::SetNextTreeNodeOpen(true, ImGuiCond_Always);

        for (BaseNode *child: Global::m_level.getTree()->getChildren()) {
            drawTreeElement(child);
        }


        ImGui::End();
    }
}


/**
 * Draw tree actions
 */
void UserInterface::drawTreeActions() {
    int posY = ImGui::GetFrameHeight() + TOOLBAR_HEIGHT + TREEVIEW_HEIGHT + 8;
    ImGui::SetNextWindowPos(ImVec2(0, posY));
    ImGui::SetNextWindowSize(ImVec2(LEFTPANEL_WIDTH, TREEVIEW_ACTIONS_HEIGHT));

    ImGuiWindowFlags toolbarFlags = ImGuiWindowFlags_NoTitleBar |
                                    ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoCollapse |
                                    ImGuiWindowFlags_NoScrollbar;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(LEFTPANEL_WIDTH, TREEVIEW_ACTIONS_HEIGHT));

    if (ImGui::Begin("TreeActions", nullptr, toolbarFlags)) {
        // Don't render actions empty selection or for light group and lights
        if ((Global::m_selectedNode == 3) || (Global::m_selectedNode == -1)) {
            ImGui::End();
            ImGui::PopStyleVar();
            return;
        }

        BaseNode *selectedNode = Global::m_level.getTree()->findNode(Global::m_selectedNode);
        if (selectedNode != nullptr) {
            LightNode *nodeLight = dynamic_cast<LightNode *>(selectedNode);
            if (nodeLight != nullptr) {
                ImGui::End();
                ImGui::PopStyleVar();
                return;
            }
        }


        if (ImGui::Button("Add Node")) {
            m_addNodeDialog.openDialog();
        }

        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip(
            Global::m_tooltipMessages.level_addNode);
        ImGui::SameLine();

        if (Global::m_selectedNode > 3) {
            if (ImGui::Button("Delete")) {
                m_deleteNodeDialog.openDialog();
            }
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip(
                Global::m_tooltipMessages.level_delete);

            ImGui::SameLine();

            if (ImGui::Button("Up")) {
                BaseNode *node = Global::m_level.getTree()->findNode(Global::m_selectedNode);
                BaseNode *prev = node->getPreviousNode();
                if (prev != nullptr) {
                    node->getParent()->swapChildOrder(node, prev);
                }
            }
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip(
                Global::m_tooltipMessages.level_up);

            ImGui::SameLine();

            if (ImGui::Button("Down")) {
                BaseNode *node = Global::m_level.getTree()->findNode(Global::m_selectedNode);
                BaseNode *next = node->getNextNode();
                if (next != nullptr) {
                    node->getParent()->swapChildOrder(node, next);
                }
            }
            if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) ImGui::SetTooltip(
                Global::m_tooltipMessages.level_down);
        }

        if (m_addNodeDialog.isOpen()) {
            m_addNodeDialog.draw();
        }

        if (m_deleteNodeDialog.isOpen()) {
            m_deleteNodeDialog.draw();
        }


        ImGui::End();
    }

    ImGui::PopStyleVar();
}


/**
* Draw one tree element (node)
*/
void UserInterface::drawTreeElement(BaseNode *node) {
    ImGui::SetNextTreeNodeOpen(true, ImGuiCond_Always);
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_Leaf;

    if (node->getChildren().size() > 0) {
        flags = ImGuiTreeNodeFlags_Leaf;
        bool isExpanded = node->isExpanded();
        std::string prefix = isExpanded ? "-" : "+";

        if (ImGui::Button((prefix + "##" + std::to_string(node->getId())).c_str())) {
            node->setExpanded(!node->isExpanded());
        }
        ImGui::SameLine(ImGui::GetCursorPosX(), 0);
    }

    if (Global::m_selectedNode == node->getId()) {
        flags |= ImGuiTreeNodeFlags_Selected;
    }

    if (ImGui::TreeNodeEx(node->getName().c_str(), flags)) {
        if (ImGui::IsItemClicked()) {
            if (Global::m_selectedNode != -1) {
                Global::m_level.getTree()->findNode(Global::m_selectedNode)->displayBoundingBox(false);
            }
            Global::m_selectedNode = node->getId();
            Global::m_selectedFromViewport = false;

            Global::m_level.getTree()->findNode(Global::m_selectedNode)->displayBoundingBox(true);
        }


        if (Global::m_selectedNode == node->getId()) {
            if ((Global::m_selectedNode != m_previousNodeSelection) && (Global::m_selectedFromViewport)) {
                ImGui::SetScrollHere();
                m_previousNodeSelection = Global::m_selectedNode;
            }
        }

        bool displayNode = true;
        if (!node->getDisplayNode()) {
            displayNode = false;
        }

        LightNode *nodeLight = dynamic_cast<LightNode *>(node);
        if (nodeLight != nullptr) {
            if (!Global::m_lights[nodeLight->getLightIndex()].getEnabled()) {
                displayNode = false;
            }
        }

        if (!displayNode) {
            ImGui::SameLine();
            ImGui::Image(ImTextureID(m_textureNotVisible.getTextureData().textureID), ImVec2(12, 12));
        }

        if (node->isExpanded()) {
            for (BaseNode *child: node->getChildren()) {
                drawTreeElement(child);
            }
        }

        ImGui::TreePop();
    }
}


/**
 * Draw properties for a selected node
 */
void UserInterface::drawProperties() {
    int posY = ImGui::GetFrameHeight() + TOOLBAR_HEIGHT + TREEVIEW_ACTIONS_HEIGHT + TREEVIEW_HEIGHT + 8;
    ImGui::SetNextWindowPos(ImVec2(0, posY));
    ImGui::SetNextWindowSize(ImVec2(LEFTPANEL_WIDTH, ofGetHeight() - STATUSBAR_HEIGHT - posY - 2));

    ImGui::Begin("Properties", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

    if (Global::m_selectedNode <= 3) {
        ImGui::End();
        return;
    }

    BaseNode *selectedNode = Global::m_level.getTree()->findNode(Global::m_selectedNode);
    if (selectedNode == nullptr) {
        ImGui::End();
        return;
    }

    std::vector<NodeProperty> properties = selectedNode->getProperties();
    int count = 0;
    for (auto property: properties) {
        switch (property.getType()) {
            case PROPERTY_TYPE::TEXT_FIELD: {
                ImGui::Text(property.getName().c_str());
                ImGui::SameLine(110);

                char buffer[255];
                auto value = std::any_cast<std::string>(property.getValue());
                std::strncpy(buffer, value.c_str(), sizeof(buffer) - 1); // Copy with limit
                buffer[sizeof(buffer) - 1] = '\0';

                if (ImGui::InputText(("##" + std::to_string(count)).c_str(), buffer, IM_ARRAYSIZE(buffer))) {
                    selectedNode->setProperty(property.getName(), std::string(buffer));
                }
                if (!property.getTooltip().empty()) {
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
                        ImGui::SetTooltip(property.getTooltip().c_str());
                    }
                }
            }
            break;

            case PROPERTY_TYPE::COLOR_PICKER: {
                ImGui::Text(property.getName().c_str());
                auto color = std::any_cast<ofFloatColor>(property.getValue());
                ImGui::SameLine(110);

                ImVec4 imColor = color;
                if (ImGui::ColorButton(("...##" + std::to_string(count)).c_str(), imColor,
                                       ImGuiColorEditFlags_AlphaPreview, ImVec2(272, 16))) {
                    m_colorDialog.setTitle("Change " + property.getName());
                    m_colorDialog.useProperty(selectedNode, property.getName(), color);
                    m_colorDialog.openDialog();
                }
                if (!property.getTooltip().empty()) {
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
                        ImGui::SetTooltip(property.getTooltip().c_str());
                    }
                }
            }
            break;

            case PROPERTY_TYPE::LABEL: {
                ImGui::Dummy(ImVec2(0, 5));
                ImGui::TextColored(ImVec4(1, 0.5, 0.5, 1), property.getName().c_str());
                if (!property.getTooltip().empty()) {
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
                        ImGui::SetTooltip(property.getTooltip().c_str());
                    }
                }
            }
            break;

            case PROPERTY_TYPE::VECTOR3: {
                ImGui::Text(property.getName().c_str());
                ImGui::SameLine(110);
                glm::vec3 value = std::any_cast<glm::vec3>(property.getValue());
                ImGui::Text("%.02f, %.02f, %.02f", value.x, value.y, value.z);
                ImGui::SameLine(272);

                if (ImGui::Button(("...##" + std::to_string(count)).c_str())) {
                    m_vec3Dialog.setTitle("Change " + property.getName());
                    m_vec3Dialog.useProperty(selectedNode, property.getName(), value);
                    m_vec3Dialog.openDialog();
                }
                if (!property.getTooltip().empty()) {
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
                        ImGui::SetTooltip(property.getTooltip().c_str());
                    }
                }
            }
            break;

            case PROPERTY_TYPE::FLOAT_FIELD: {
                ImGui::Text(property.getName().c_str());
                ImGui::SameLine(110);
                auto value = std::any_cast<float>(property.getValue());
                float initialValue = value;

                ImGui::PushItemWidth(186.0f);
                if (ImGui::InputFloat(("##Float_" + std::to_string(count)).c_str(), &value, 0.5f, 1.0f, "%.3f",
                                      ImGuiInputTextFlags_EnterReturnsTrue)) {
                    Global::m_actions.addAction(selectedNode, property.getName(), initialValue, value);
                }
                if (!property.getTooltip().empty()) {
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
                        ImGui::SetTooltip(property.getTooltip().c_str());
                    }
                }
                ImGui::PopItemWidth();
            }
            break;

            case PROPERTY_TYPE::PRECISE_FLOAT_FIELD: {
                ImGui::Text(property.getName().c_str());
                ImGui::SameLine(110);
                auto value = std::any_cast<float>(property.getValue());
                float initialValue = value;

                ImGui::PushItemWidth(186.0f);
                if (ImGui::InputFloat(("##Float_" + std::to_string(count)).c_str(), &value, 0.0001f, 0.0005f, "%.6f",
                                      ImGuiInputTextFlags_EnterReturnsTrue)) {
                    Global::m_actions.addAction(selectedNode, property.getName(), initialValue, value);
                }
                if (!property.getTooltip().empty()) {
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
                        ImGui::SetTooltip(property.getTooltip().c_str());
                    }
                }
                ImGui::PopItemWidth();
            }
            break;

            case PROPERTY_TYPE::INT_FIELD: {
                ImGui::Text(property.getName().c_str());
                ImGui::SameLine(110);
                auto value = std::any_cast<int>(property.getValue());
                int initialValue = value;

                ImGui::PushItemWidth(186.0f);
                if (ImGui::InputInt(("##Integer_" + std::to_string(count)).c_str(), &value, 1,
                                    ImGuiInputTextFlags_EnterReturnsTrue)) {
                    Global::m_actions.addAction(selectedNode, property.getName(), initialValue, value);
                }
                if (!property.getTooltip().empty()) {
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
                        ImGui::SetTooltip(property.getTooltip().c_str());
                    }
                }
                ImGui::PopItemWidth();
            }
            break;

            case PROPERTY_TYPE::BOOLEAN_FIELD: {
                ImGui::Text(property.getName().c_str());
                ImGui::SameLine(110);
                auto value = std::any_cast<bool>(property.getValue());
                int initialValue = value;

                ImGui::PushItemWidth(186.0f);
                if (ImGui::Checkbox(("##Boolean_" + std::to_string(count)).c_str(), &value)) {
                    Global::m_actions.addAction(selectedNode, property.getName(), initialValue, value);
                }
                if (!property.getTooltip().empty()) {
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
                        ImGui::SetTooltip(property.getTooltip().c_str());
                    }
                }
                ImGui::PopItemWidth();
            }
            break;

            case PROPERTY_TYPE::ITEM_LIST: {
                ImGui::Text(property.getName().c_str());
                ImGui::SameLine(110);
                std::vector<std::string> value = std::any_cast<std::vector<std::string> >(property.getValue());

                int initialSelection = stoi(value.back()); //get the index at the back of the vector
                int currentItem = initialSelection;

                // Doing -1 to remove the index (the 'initialSelection')
                std::vector<char *> cstrings{};
                cstrings.reserve(value.size() - 1);
                for (size_t i = 0; i < value.size() - 1; ++i) {
                    cstrings.push_back(const_cast<char *>(value[i].c_str()));
                }

                ImGui::PushItemWidth(186.0f);
                if (ImGui::Combo(("##List_" + std::to_string(count)).c_str(), &currentItem, cstrings.data(),
                                 cstrings.size())) {
                    Global::m_actions.addAction(selectedNode, property.getName(), initialSelection, currentItem);
                }
                if (!property.getTooltip().empty()) {
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
                        ImGui::SetTooltip(property.getTooltip().c_str());
                    }
                }
            }
            break;

            case PROPERTY_TYPE::ITEM_CLIST: {
                ImGui::Text(property.getName().c_str());
                ImGui::SameLine(110);
                std::pair<int, std::vector<char *> > value = std::any_cast<std::pair<int, std::vector<char *> > >(
                    property.getValue());
                int currentItem = value.first;

                ImGui::PushItemWidth(186.0f);
                if (ImGui::Combo(
                        ("##List_" + std::to_string(count)).c_str(),
                        &currentItem,
                        value.second.data(),
                        value.second.size())
                ) {
                    Global::m_actions.addAction(selectedNode, property.getName(), value.first, currentItem);
                }
                if (!property.getTooltip().empty()) {
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
                        ImGui::SetTooltip(property.getTooltip().c_str());
                    }
                }
            }
            break;

            case PROPERTY_TYPE::TEXT_INFO: {
                ImGui::Text(property.getName().c_str());
                ImGui::SameLine(110);
                ImGui::TextWrapped(std::any_cast<std::string>(property.getValue()).data());
                if (!property.getTooltip().empty()) {
                    if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled)) {
                        ImGui::SetTooltip(property.getTooltip().c_str());
                    }
                }
            }
            break;
        }

        count++;
    }


    // Render dialogs

    if (m_vec3Dialog.isOpen()) {
        m_vec3Dialog.draw();
    }

    if (m_colorDialog.isOpen()) {
        m_colorDialog.draw();
    }

    ImGui::End();
}


/**
* Draw the status bar
*/
void UserInterface::drawStatus() {
    ImGui::SetNextWindowPos(ImVec2(0, ofGetHeight() - STATUSBAR_HEIGHT)); // Position the status bar at the bottom
    ImGui::SetNextWindowSize(ImVec2(ofGetWidth(), STATUSBAR_HEIGHT)); // Set the height of the status bar

    ImGui::Begin("Status Bar", nullptr,
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    int countTotalRender = Global::m_countNodeRender[0] + Global::m_countNodeRender[1] + Global::m_countNodeRender[2];

    ImGui::Text("");
    std::string line = "Rendering " + std::to_string(countTotalRender) + " nodes, FPS: " + std::to_string(
                           static_cast<int>(ofGetFrameRate()));
    ImVec2 textSize = ImGui::CalcTextSize(line.c_str(), nullptr, true);

    ImGui::SameLine(ImGui::GetWindowWidth() - textSize.x - 10);
    ImGui::Text(line.c_str());


    ImGui::End();
}

/**
 * Draw viewports
 */
void UserInterface::drawViewports() {
    if (m_onlyOneCamera) {
        float cameraSizeFirstWidth = (float) (ofGetWidth() - LEFTPANEL_WIDTH - 4);
        float cameraSizeFirstHeight = (float) ofGetHeight() - ImGui::GetFrameHeight() - STATUSBAR_HEIGHT -
                                      TOOLBAR_HEIGHT - 8;
        drawViewport("Main Camera", 0, ImVec2(LEFTPANEL_WIDTH + 2, ImGui::GetFrameHeight() + TOOLBAR_HEIGHT + 6),
                     ImVec2(cameraSizeFirstWidth, cameraSizeFirstHeight));
    } else {
        float cameraSizeFirstHeight = (float) ofGetHeight() - ImGui::GetFrameHeight() - STATUSBAR_HEIGHT -
                                      TOOLBAR_HEIGHT - 8;
        float cameraSizeSecond = ((float) ofGetHeight() - ImGui::GetFrameHeight() - STATUSBAR_HEIGHT - TOOLBAR_HEIGHT -
                                  8) / 2.0;
        float cameraSizeThird = cameraSizeSecond;
        float cameraSizeFirstWidth = (float) (ofGetWidth() - cameraSizeSecond - LEFTPANEL_WIDTH - 4);

        drawViewport("Main Camera", 0, ImVec2(LEFTPANEL_WIDTH + 2, ImGui::GetFrameHeight() + TOOLBAR_HEIGHT + 6),
                     ImVec2(cameraSizeFirstWidth, cameraSizeFirstHeight));
        drawViewport("Second Camera", 1,
                     ImVec2(LEFTPANEL_WIDTH + 4 + cameraSizeFirstWidth, ImGui::GetFrameHeight() + TOOLBAR_HEIGHT + 6),
                     ImVec2(cameraSizeSecond, cameraSizeSecond));
        drawViewport("Third Camera", 2,
                     ImVec2(LEFTPANEL_WIDTH + 4 + cameraSizeFirstWidth,
                            ImGui::GetFrameHeight() + TOOLBAR_HEIGHT + 7 + cameraSizeSecond),
                     ImVec2(cameraSizeThird, cameraSizeThird));
    }
}


/**
 * Draw a specific viewport (each viewport have a camera associated with)
 */
void UserInterface::drawViewport(const std::string &name, int index, const ImVec2 &position, const ImVec2 &size) {
    // Convert from float to integers
    int size_x = static_cast<int>(size.x);
    int size_y = static_cast<int>(size.y);

    auto fbo = Global::m_cameras[index].getFbo();
    auto pickingFbo = Global::m_cameras[index].getPickingFbo();
    auto camera = Global::m_cameras[index].getCamera();

    Global::m_cameras[index].setViewportSize(size_x, size_y);

    ImGui::SetNextWindowPos(position);
    ImGui::SetNextWindowSize(size);

    ImGui::Begin(name.c_str(), nullptr,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing);

    ImVec2 windowSize = ImGui::GetContentRegionAvail();
    auto textureID = reinterpret_cast<ImTextureID>(fbo->getTexture().getTextureData().textureID);
    ImVec2 imagePos = ImGui::GetCursorScreenPos();
    ImGui::Image(textureID, windowSize);
    int overlayItemHeight = 21;


    if (ImGui::IsWindowHovered()) {
        m_hoveredWindow = name;

        ImVec2 mousePos = ImGui::GetMousePos();

        if (ImGui::IsMouseReleased(ImGuiMouseButton_Left)) {
            Global::m_transformTools.onMouseButtonReleased(mousePos);
        }
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            ImVec2 realSize = ImGui::GetItemRectSize();
            float localX = mousePos.x - imagePos.x;
            float localY = mousePos.y - imagePos.y;

            // Adjust for DPI scaling if needed
            float scaleFactor = ImGui::GetIO().DisplayFramebufferScale.x;
            localX /= scaleFactor;
            localY /= scaleFactor;

            // Also adjust if the image in the viewport is not the same size as the texture size
            float scaleX = realSize.x / size.x;
            float scaleY = realSize.y / size.y;
            localX /= scaleX;
            localY /= scaleY;

            auto pixelX = static_cast<int>(localX);
            auto pixelY = static_cast<int>(localY);

            // Ignore clicks on translate buttons area
            if (pixelY > overlayItemHeight) {
                ofPixels pixels;
                pickingFbo->readToPixels(pixels); // Read the entire FBO content to pixels

                // Get the color of the clicked pixel
                int pickedObjectId = Global::colorToId(pixels.getColor(pixelX, pixelY));
                //ofLog() << "picked:" << pixels.getColor(pixelX, pixelY) << " Object:" << pickedObjectId;
                if (pickedObjectId != 0) {
                    if (pickedObjectId >= TRANSLATE_X) {
                        Global::m_transformTools.onMouseButtonPressed(pickedObjectId, mousePos);
                    } else {
                        // Verify if the object exists (just in case)
                        if (Global::m_level.getTree()->findNode(pickedObjectId) != nullptr) {
                            if (Global::m_selectedNode != -1) {
                                Global::m_level.getTree()->findNode(Global::m_selectedNode)->displayBoundingBox(false);
                            }

                            Global::m_selectedNode = pickedObjectId;
                            Global::m_selectedFromViewport = true;
                            Global::m_level.getTree()->findNode(Global::m_selectedNode)->displayBoundingBox(true);
                        }
                    }
                } else {
                    if (Global::m_selectedNode != -1) {
                        Global::m_level.getTree()->findNode(Global::m_selectedNode)->displayBoundingBox(false);
                    }
                    Global::m_selectedNode = -1;
                    Global::m_selectedFromViewport = true;
                }
            }
        }

        if (Global::m_selectedNode == -1) {
            Global::m_cursorManager.change("hand");
        } else {
            if (Global::m_transformTools.getTransformMode() == TRANSFORM_MODE::TRANSLATE) {
                Global::m_cursorManager.change("move");
            } else if (Global::m_transformTools.getTransformMode() == TRANSFORM_MODE::ROTATE) {
                Global::m_cursorManager.change("rotate");
            } else if (Global::m_transformTools.getTransformMode() == TRANSFORM_MODE::SCALE) {
                Global::m_cursorManager.change("scale");
            }
        }


        // Check if an object is clicked
        if (ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
            Global::m_transformTools.onMouseDrag(mousePos);
        }

        // Draw axis arrows
        float axisLength = 40.0f;

        ofVec3f rightDirection = camera->getXAxis();
        ofVec3f upDirection = camera->getYAxis();
        ofVec3f forwardDirection = camera->getZAxis();

        rightDirection *= axisLength;
        upDirection *= axisLength;
        forwardDirection *= axisLength;

        ImVec2 startPos = position + ImVec2(50, 70);
        ImDrawList *drawList = ImGui::GetWindowDrawList();
        drawList->AddLine(startPos, startPos + ImVec2(rightDirection.x, rightDirection.y), IM_COL32(255, 0, 0, 255),
                          2.0f);
        drawList->AddLine(startPos, startPos + ImVec2(upDirection.x, upDirection.y), IM_COL32(0, 255, 0, 255), 2.0f);
        drawList->AddLine(startPos, startPos + ImVec2(forwardDirection.x, forwardDirection.y), IM_COL32(0, 0, 255, 255),
                          2.0f);
    }

    drawViewportOverlay(index, position, size_x, overlayItemHeight);


    ImGui::End();
}


void UserInterface::drawViewportOverlay(int index, const ImVec2 &position, int availableWidth, int verticalOffset) {
    // Hovering buttons and fields at the top of the camera viewport


    ofCustomCamera *camera = Global::m_cameras[index].getCamera();

    float overlayWidth = 378.0f;
    ImDrawList *drawList = ImGui::GetWindowDrawList();


    drawList->AddRectFilled(position + ImVec2(10, verticalOffset - 2.0f),
                            position + ImVec2(availableWidth - 10, verticalOffset + 21), IM_COL32(35, 35, 35, 255));


    // Draw recording message
    if ((index == 0) && (Global::m_sequenceCount != -1)) {
        std::string recordMessage = "Recording ... (" + std::to_string(Global::m_sequenceCount) + "/60)";
        drawList->AddRectFilled(position + ImVec2(10, 43), position + ImVec2(168, 64), IM_COL32(35, 35, 35, 255));
        drawList->AddText(position + ImVec2(17, 47), ImColor(255, 0, 0), recordMessage.c_str());
    }

    ImGui::SetCursorPos(ImVec2(availableWidth - overlayWidth, verticalOffset));
    ImGui::BeginGroup();

    if (camera->getOrtho()) {
        if (ImGui::Button("Camera: Ortho", ImVec2(140, 16))) {
            camera->disableOrtho();
        }
    } else {
        ImGui::SetNextItemWidth(200);
        if (ImGui::Button("Camera: Perspective", ImVec2(140, 16))) {
            camera->enableOrtho();
        }
    }
    ImGui::SameLine();

    if (camera->getOrtho()) {
        float zoomFactor = camera->getOrthoZoom();
        ImGui::SetNextItemWidth(50);
        if (ImGui::InputFloat("##CameraOrthoZoom", &zoomFactor, 0.0f, 0.0f, "%.2f",
                              ImGuiInputTextFlags_EnterReturnsTrue)) {
            camera->setOrthoZoom(zoomFactor);
        }
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(Global::m_tooltipMessages.camera_orthoZoom);
        }
    } else {
        float fov = camera->getFov();
        ImGui::SetNextItemWidth(50);
        if (ImGui::InputFloat("##CameraFOV", &fov, 0.0f, 0.0f, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue)) {
            ofLog() << "Camera FOV changed to: " << fov;
            camera->setFov(fov);
        }
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(Global::m_tooltipMessages.camera_FOVDeg);
        }
    }
    ImGui::SameLine();

    ImGui::SetNextItemWidth(50);
    float zNear = camera->getNearClip();
    if (ImGui::InputFloat("##CameraZNear", &zNear, 0.0f, 0.0f, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue)) {
        ofLog() << "Camera ZNear changed to: " << zNear;
        camera->setNearClip(zNear);
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(Global::m_tooltipMessages.camera_nearClip);
    }

    ImGui::SameLine();

    ImGui::SetNextItemWidth(60);
    float zFar = camera->getFarClip();
    if (ImGui::InputFloat("##CameraZFar", &zFar, 0.0f, 0.0f, "%.2f", ImGuiInputTextFlags_EnterReturnsTrue)) {
        ofLog() << "Camera ZFor changed to: " << zFar;
        camera->setFarClip(zFar);
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(Global::m_tooltipMessages.camera_farClip);
    }

    ImGui::SameLine();
    if (ImGui::Button("Reset")) {
        Global::m_cameras[index].reset();
    }
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(Global::m_tooltipMessages.camera_reset);
    }
    ImGui::SameLine();


    // Draw transform buttons
    if ((index == 0) && (Global::m_selectedNode != -1)) {
        ImGui::SetCursorPos(ImVec2(12, verticalOffset));
        ImGui::Text("Transform:");
        ImGui::SameLine();

        if (Global::m_transformTools.getTransformMode() == TRANSFORM_MODE::TRANSLATE) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
            if (ImGui::Button("Translate")) {
                Global::m_transformTools.setTransformMode(TRANSFORM_MODE::TRANSLATE);
            }
            ImGui::PopStyleColor(2);
        } else {
            if (ImGui::Button("Translate")) {
                Global::m_transformTools.setTransformMode(TRANSFORM_MODE::TRANSLATE);
            }
        }


        ImGui::SameLine();

        if (Global::m_transformTools.getTransformMode() == TRANSFORM_MODE::ROTATE) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);

            if (ImGui::Button("Rotate")) {
                Global::m_transformTools.setTransformMode(TRANSFORM_MODE::ROTATE);
            }
            ImGui::PopStyleColor(2);
        } else {
            if (ImGui::Button("Rotate")) {
                Global::m_transformTools.setTransformMode(TRANSFORM_MODE::ROTATE);
            }
        }
        ImGui::SameLine();

        if (Global::m_transformTools.getTransformMode() == TRANSFORM_MODE::SCALE) {
            ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImGui::GetStyle().Colors[ImGuiCol_ButtonActive]);

            if (ImGui::Button("Scale")) {
                Global::m_transformTools.setTransformMode(TRANSFORM_MODE::SCALE);
            }
            ImGui::PopStyleColor(2);
        } else {
            if (ImGui::Button("Scale")) {
                Global::m_transformTools.setTransformMode(TRANSFORM_MODE::SCALE);
            }
        }
    }

    ImGui::EndGroup();
}


/**
 * Capture frame buffer
 */
void UserInterface::captureFramebuffer(int index, ofPixels &pixels) {
    auto fbo = Global::m_cameras[index].getFbo();
    fbo->readToPixels(pixels);
}


/**
 * Callback function : Show about dialog
 */
void UserInterface::onAboutProgram() {
    // TODO
}


/**
 * Callback function : New level
 */
void UserInterface::onNewLevel() {
    // TODO
}


/**
 * Callback function : load level
 */
void UserInterface::onLoadLevel() {
    ofFileDialogResult result = ofSystemLoadDialog("Select level file to load", false, "levels/");

    if (result.bSuccess) {
        LevelPersistence lp;
        lp.loadFromFile(result.getPath());
    }
}


/**
 * Callback function : Save level
 */
void UserInterface::onSaveLevel() {
    ofFileDialogResult result = ofSystemSaveDialog("levels/NewLevel.xml", "Select file to save level");
    if (result.bSuccess) {
        LevelPersistence lp;
        lp.saveToFile(result.getPath());
    }
}


/**
 * Callback function : Generate triptych
 */
void UserInterface::onGenerateTriptych() {
    ofPixels pixels1, pixels2, pixels3;
    captureFramebuffer(0, pixels1);
    captureFramebuffer(1, pixels2);
    captureFramebuffer(2, pixels3);

    int width1 = pixels1.getWidth();
    int height1 = pixels1.getHeight();

    int width2 = pixels2.getWidth();
    int height2 = pixels2.getHeight();

    int width3 = pixels3.getWidth();
    int height3 = pixels3.getHeight();
    int maxWidth = width1 + max(width2, width3);
    int maxHeight = max(height1, height2 + height3);

    ofPixels combinedPixels;
    if (onlyOneCamera()) {
        combinedPixels.allocate(width1, height1, OF_IMAGE_COLOR);

        for (int y = 0; y < height1; ++y) {
            for (int x = 0; x < width1; ++x) {
                combinedPixels.setColor(x, y, pixels1.getColor(x, y));
            }
        }
    } else {
        combinedPixels.allocate(maxWidth, maxHeight, OF_IMAGE_COLOR);
        for (int y = 0; y < maxHeight; ++y) {
            for (int x = 0; x < maxWidth; ++x) {
                combinedPixels.setColor(x, y, ofColor::black);
            }
        }

        for (int y = 0; y < height1; ++y) {
            for (int x = 0; x < width1; ++x) {
                combinedPixels.setColor(x, y, pixels1.getColor(x, y));
            }
        }

        for (int y = 0; y < height2; ++y) {
            for (int x = 0; x < width2; ++x) {
                combinedPixels.setColor(static_cast<size_t>(x) + width1, static_cast<size_t>(y),
                                        pixels2.getColor(x, y));
            }
        }

        for (int y = 0; y < height3; ++y) {
            for (int x = 0; x < width3; ++x) {
                combinedPixels.setColor(static_cast<size_t>(x) + width1, static_cast<size_t>(y) + height2,
                                        pixels3.getColor(x, y));
            }
        }
    }
    // Save combined image
    ofImage combinedImage;
    combinedImage.setFromPixels(combinedPixels);
    string time_stamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");

    // Generate unique name
    string filename = "triptych" + time_stamp + ".png";
    combinedImage.save("output/" + filename);

    m_fileGeneratedDialog.setContent("Image successfully saved as:\n\n" + filename + "\n", filename);
    m_fileGeneratedDialog.openDialog();
}


/**
 * Display key bindings
 */
void UserInterface::onShowKeyBindings() {
}


/**
 * Callback function : History undo
 */
void UserInterface::onHistoryUndo() {
    Global::m_actions.undo();
}


/**
 * Callback function : History redo
 */
void UserInterface::onHistoryRedo() {
    Global::m_actions.redo();
}


/**
 * Toggle 3 or 1 camera
 */
void UserInterface::onToggleCameras() {
    m_onlyOneCamera = !m_onlyOneCamera;
}


/**
 * Get hovered window
 */
const std::string &UserInterface::getHoveredWindow() const {
    return m_hoveredWindow;
}


/**
 * Only one camera need to be shown
 */
bool UserInterface::onlyOneCamera() const {
    return m_onlyOneCamera;
}

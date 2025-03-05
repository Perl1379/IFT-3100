/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * AddNodeDialog class implementation
 *
 *****************************************************/
#include "AddNodeDialog.h"

#include <BaseNode.h>
#include <BoxNode.h>
#include <ConeNode.h>
#include <CylinderNode.h>
#include <Global.h>
#include <GroupNode.h>
#include <imgui.h>
#include <ModelNode.h>
#include <ofLog.h>
#include <PlaneNode.h>
#include <SphereNode.h>


/**
 * Constructor
 */
AddNodeDialog::AddNodeDialog() : ModalDialog() {

    setTitle("Add Node");
}


/**
 * Dialog draw
 */
void AddNodeDialog::draw() {

    if (ImGui::BeginPopupModal(m_title.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {

        // Add group
        if (ImGui::Button("Group Node", ImVec2(200,20))) {
            ImGui::CloseCurrentPopup();
            m_isOpen = false;

            BaseNode* parent;
            if (Global::m_selectedNode == -1) {
                parent = Global::m_level.getTree();
            } else {
                parent = Global::m_level.getTree()->findNode(Global::m_selectedNode);
            }
            GroupNode* childNode = new GroupNode("Group");
            parent->addChild(childNode);

            if (Global::m_selectedNode != -1) {
                Global::m_level.getTree()->findNode(Global::m_selectedNode)->displayBoundingBox(false);
            }
            childNode->displayBoundingBox(true);
            Global::m_selectedNode = childNode->getId();
            Global::m_selectedFromViewport = true;
        }

        // Primitives
        ImGui::Dummy(ImVec2(0, 5));
        ImGui::TextColored(ImVec4(1, 0.5, 0.5, 1), "Primitives");

        // Add Sphere
        if (ImGui::Button("Sphere", ImVec2(200,20))) {
            ImGui::CloseCurrentPopup();
            m_isOpen = false;

            BaseNode* parent;
            if (Global::m_selectedNode == -1) {
                parent = Global::m_level.getTree();
            } else {
                parent = Global::m_level.getTree()->findNode(Global::m_selectedNode);
            }
            SphereNode* childNode = new SphereNode("Sphere");
            parent->addChild(childNode);

            if (Global::m_selectedNode != -1) {
                Global::m_level.getTree()->findNode(Global::m_selectedNode)->displayBoundingBox(false);
            }
            childNode->displayBoundingBox(true);
            Global::m_selectedNode = childNode->getId();
            Global::m_selectedFromViewport = true;
        }

        // Add cube
        if (ImGui::Button("Box", ImVec2(200,20))) {
            ImGui::CloseCurrentPopup();
            m_isOpen = false;

            BaseNode* parent;
            if (Global::m_selectedNode == -1) {
                parent = Global::m_level.getTree();
            } else {
                parent = Global::m_level.getTree()->findNode(Global::m_selectedNode);
            }
            BoxNode* childNode = new BoxNode("Box");
            parent->addChild(childNode);

            if (Global::m_selectedNode != -1) {
                Global::m_level.getTree()->findNode(Global::m_selectedNode)->displayBoundingBox(false);
            }
            childNode->displayBoundingBox(true);
            Global::m_selectedNode = childNode->getId();
            Global::m_selectedFromViewport = true;

        }

        // Add cylinder
        if (ImGui::Button("Cylinder", ImVec2(200,20))) {
            ImGui::CloseCurrentPopup();
            m_isOpen = false;

            BaseNode* parent;
            if (Global::m_selectedNode == -1) {
                parent = Global::m_level.getTree();
            } else {
                parent = Global::m_level.getTree()->findNode(Global::m_selectedNode);
            }
            CylinderNode* childNode = new CylinderNode("Cylinder");
            parent->addChild(childNode);

            if (Global::m_selectedNode != -1) {
                Global::m_level.getTree()->findNode(Global::m_selectedNode)->displayBoundingBox(false);
            }
            childNode->displayBoundingBox(true);
            Global::m_selectedNode = childNode->getId();
            Global::m_selectedFromViewport = true;
        }

        // Add cone
        if (ImGui::Button("Cone", ImVec2(200,20))) {
            ImGui::CloseCurrentPopup();
            m_isOpen = false;

            BaseNode* parent;
            if (Global::m_selectedNode == -1) {
                parent = Global::m_level.getTree();
            } else {
                parent = Global::m_level.getTree()->findNode(Global::m_selectedNode);
            }
            ConeNode* childNode = new ConeNode("Cone");
            parent->addChild(childNode);

            if (Global::m_selectedNode != -1) {
                Global::m_level.getTree()->findNode(Global::m_selectedNode)->displayBoundingBox(false);
            }
            childNode->displayBoundingBox(true);
            Global::m_selectedNode = childNode->getId();
            Global::m_selectedFromViewport = true;
        }

        // Add plane
        if (ImGui::Button("Plane", ImVec2(200,20))) {
            ImGui::CloseCurrentPopup();
            m_isOpen = false;

            BaseNode* parent;
            if (Global::m_selectedNode == -1) {
                parent = Global::m_level.getTree();
            } else {
                parent = Global::m_level.getTree()->findNode(Global::m_selectedNode);
            }
            PlaneNode* childNode = new PlaneNode("Plane");
            parent->addChild(childNode);

            if (Global::m_selectedNode != -1) {
                Global::m_level.getTree()->findNode(Global::m_selectedNode)->displayBoundingBox(false);
            }
            childNode->displayBoundingBox(true);
            Global::m_selectedNode = childNode->getId();
            Global::m_selectedFromViewport = true;
        }

        // Primitives
        ImGui::Dummy(ImVec2(0, 5));
        ImGui::TextColored(ImVec4(1, 0.5, 0.5, 1), "Models");

        // Add model
        if (ImGui::Button("Model", ImVec2(200,20))) {
            ImGui::CloseCurrentPopup();
            m_isOpen = false;

            BaseNode* parent;
            if (Global::m_selectedNode == -1) {
                parent = Global::m_level.getTree();
            } else {
                parent = Global::m_level.getTree()->findNode(Global::m_selectedNode);
            }
            ModelNode* childNode = new ModelNode("Model", "Kaykit/Characters/gltf/Knight.glb");
            parent->addChild(childNode);

            if (Global::m_selectedNode != -1) {
                Global::m_level.getTree()->findNode(Global::m_selectedNode)->displayBoundingBox(false);
            }
            childNode->displayBoundingBox(true);
            Global::m_selectedNode = childNode->getId();
            Global::m_selectedFromViewport = true;
        }

		ImGui::Dummy(ImVec2(0.0f, 5.0f));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0.0f, 5.0f));

        ImGui::SetCursorPosX(80);
        if (ImGui::Button("Cancel")) {
            ImGui::CloseCurrentPopup();
            m_isOpen = false;
        }

        ImGui::EndPopup();
    }
}

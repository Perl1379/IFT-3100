/*****************************************************
 * TP IFT3100H24 - 3D Scene Editor
 * by Team 12
 *****************************************************
 *
 * Application class implementation
 *
 *****************************************************/


#include "application.h"

#include <ofAppRunner.h>
#include <ofGraphics.h>


// Declare GUI elements

/**
 * Application setup (title, menu and various visual elements)
 */
void Application::setup() {

 ofSetWindowTitle("3D Scene Editor");

 gui.setup();

 // TODO: Create game menu here
 // TODO: Create tree view
 // TODO: Create multiple viewports
 // TODO: Create property view
}


/**
 * Main draw function
 */
void Application::draw() {

 gui.begin();

 _draw_menu();
 _draw_tree();
 _draw_status();
 _draw_properties();
 _draw_viewport();

 gui.end();

}

/**
* Draw the menu
*/
void Application::_draw_menu() {

 // Draw menu
 if (ImGui::BeginMainMenuBar()) {
  if (ImGui::BeginMenu("File")) {
   if (ImGui::MenuItem("Open Scene")) {
    // handle action
   }
   if (ImGui::MenuItem("Save Scene")) {
    // handle action
   }

   if (ImGui::MenuItem("Export Texture Atlas")) {
    // handle action
   }

   if (ImGui::MenuItem("Exit")) {
    ofExit(0);
   }

   ImGui::EndMenu();
  }

  if (ImGui::BeginMenu("Edit")) {
   if (ImGui::MenuItem("Undo")) {
    // handle action
   }
   if (ImGui::MenuItem("Redo")) {
    // handle action
   }
   if (ImGui::MenuItem("Copy Node")) {
    // handle action
   }
   if (ImGui::MenuItem("Paste Node")) {
    // handle action
   }
   ImGui::EndMenu();
  }

  if (ImGui::BeginMenu("Help")) {
   if (ImGui::MenuItem("About 3D Scene Editor")) {
    // handle action
   }
   ImGui::EndMenu();
  }

  ImGui::EndMainMenuBar(); // End the menu bar
 }
}


/**
* Draw tree containing nodes
*/
void Application::_draw_tree() {

// Define position and size
 ImGui::SetNextWindowPos(ImVec2(0, 20), ImGuiCond_Always);
 ImGui::SetNextWindowSize(ImVec2(200, ofGetHeight() - 50), ImGuiCond_Always);

 // Create a tree view with ImGui
 if (ImGui::Begin("Scene")) {

  ImGui::SetNextTreeNodeOpen(true, ImGuiCond_Always);

  // Root node
  if (ImGui::TreeNode("Root Node")) {

   // All tree nodes opens

   // Child nodes under Root Node
   if (ImGui::TreeNode("Child 1")) {
    ImGui::Selectable(" Sub-Child 1");
    ImGui::TreePop();
   }

   if (ImGui::TreeNode("Child 2")) {
    ImGui::Selectable(" Sub-Child 2");
    ImGui::TreePop();
   }

   // Nested tree nodes
   if (ImGui::TreeNode("Child 3")) {
    ImGui::Selectable(" Sub-Child 3");
    ImGui::TreePop();
   }

   ImGui::TreePop(); // Close the root node
  }
  ImGui::End();

 }
}


/**
* Draw the status bar
*/
void Application::_draw_status() {

 ImGui::SetNextWindowPos(ImVec2(0, ofGetHeight() - 30)); // Position the status bar at the bottom
 ImGui::SetNextWindowSize(ImVec2(ofGetWidth(), 30)); // Set the height of the status bar

 ImGui::Begin("Status Bar", nullptr,
  ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

 ImGui::Text("Rendering 0 node(s)");
 ImGui::SameLine(ImGui::GetWindowWidth() - 100);
 ImGui::Text("FPS: %.1f", ofGetFrameRate());
 ImGui::End();

}


/**
* Draw properties for a selected node
*/
void Application::_draw_properties() {

 ImGui::SetNextWindowPos(ImVec2(ofGetWidth() - 250, 0));
 ImGui::SetNextWindowSize(ImVec2(250, ofGetHeight() - 30));

 ImGui::Begin("Node Properties");

 // Add some properties with input fields
 static char name[128] = "Sample Node";
 ImGui::Text("Name");
 ImGui::SameLine(100);
 ImGui::InputText("", name, IM_ARRAYSIZE(name));

 static int age = 30;
 ImGui::Text("Render Order");
 ImGui::SameLine(100);
 ImGui::InputInt("", &age);

 static float height = 1.75f;
 ImGui::Text("Alpha Value");
 ImGui::SameLine(100);
 ImGui::InputFloat("", &height, 0.01f, 0.1f, 3);

 static bool isActive = true;
 ImGui::Text("Active");
 ImGui::SameLine(100);
 ImGui::Checkbox("", &isActive);

 ImGui::End();  // End of the property list window

}


/**
 * Draw viewport
 */
void Application::_draw_viewport() {

 // Nothing for now
}


/**
 * Called when the application is about to exit
 */
void Application::exit() {
}

/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * ActionManager class implementation
 *
 *****************************************************/
#include "ActionManager.h"

#include <Global.h>
#include <PerlinNoiseTexture.h>


 /**
  * Undo last action
  */
void ActionManager::undo() {

	if (m_nextAction == 0) {
		return;
	}

	EditorAction action = m_actions.at(m_nextAction - 1);
	performAction(action.getNode(), action.getPropertyName(), action.getOrigValue());
	m_nextAction--;

}


/**
 * Redo last action
 */
void ActionManager::redo() {
	if (m_nextAction == m_actions.size()) return;

	EditorAction action = m_actions.at(m_nextAction);
	performAction(action.getNode(), action.getPropertyName(), action.getNewValue());
	m_nextAction++;

}


/**
 * Add action to manager
 */
void ActionManager::addAction(BaseNode* p_node, const std::string& p_property_name, std::any p_oldValue,
	std::any p_newValue) {
	EditorAction action(p_node, p_property_name, p_oldValue, p_newValue);

	while (m_actions.size() > m_nextAction) {
		m_actions.pop_back();
	}

	m_actions.push_back(action);

	performAction(p_node, p_property_name, p_newValue);
	m_nextAction++;
}

/**
* Perform action (set property)
*/
void ActionManager::performAction(BaseNode* p_node, const std::string& p_property_name, std::any p_new_value) {
	ofLog() << "Perform action : " << p_property_name;
	if (p_node != nullptr) {
		p_node->setProperty(p_property_name, p_new_value);
	}
	else {
		if (p_property_name == "ambient_light_color") {
			Global::m_ambientLightColor = std::any_cast<ofFloatColor>(p_new_value);
			ofSetGlobalAmbientColor(Global::m_ambientLightColor);
		}

		if (p_property_name == "skybox_change") {
			Global::m_skybox.setup(std::any_cast<std::string>(p_new_value));

		}

		if (p_property_name == "Proc. Texture") {
			

		}
	}
}

/**
 * Replace a node with a null ptr
 */
void ActionManager::removeNode(BaseNode* p_node) {
	for (size_t i = 0;i < m_actions.size();i++) {
		if (m_actions[i].getNode() == p_node) {
			m_actions.erase(m_actions.begin() + i);
			m_nextAction--;
			return;
		}

	}
}

/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * ActionManager class definition
 *
 *****************************************************/
#pragma once

#include <vector>
#include "EditorAction.h"


class ActionManager {

  private:

    unsigned int m_nextAction = 0;
    std::vector<EditorAction> m_actions;
    void performAction(BaseNode* p_node, const std::string& p_property_name, std::any p_new_value);

  public:

    void undo();
    void redo();
    void addAction(BaseNode* p_node, const std::string& p_property_name, std::any p_oldValue, std::any p_newValue);
    void removeNode(BaseNode* p_node);

};



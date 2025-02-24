/*****************************************************
* TP IFT3100H25 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * EditorAction class definition
 *
 *****************************************************/
#pragma once
#include <BaseNode.h>

class EditorAction {

  private:
    BaseNode* m_node;
    std::string m_property_name;
    std::any m_orig_value;
    std::any m_new_value;


  public:
    EditorAction(BaseNode* p_node, const std::string& p_property_name, std::any p_orig_value, std::any p_new_value);
    ~EditorAction() = default;

    BaseNode* getNode();
    std::string getPropertyName();
    std::any getOrigValue();
    std::any getNewValue();

};


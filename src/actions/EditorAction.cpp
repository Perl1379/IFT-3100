/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * EditorAction class implementation
 *
 *****************************************************/
#include "EditorAction.h"


/**
 * Constructor
 */
EditorAction::EditorAction(BaseNode *p_node, const std::string &p_property_name, std::any p_orig_value,
                           std::any p_new_value) :
                           m_node(p_node), m_property_name(p_property_name),
                           m_orig_value(p_orig_value), m_new_value(p_new_value) {
}


/**
 *  Get node
 */
BaseNode *EditorAction::getNode() {
    return m_node;
}


/**
 * Get property name
 */
std::string EditorAction::getPropertyName() {
    return m_property_name;
}


/**
 * Get original value
 */
std::any EditorAction::getOrigValue() {
    return m_orig_value;
}


/**
 * Get new value
 */
std::any EditorAction::getNewValue() {
    return m_new_value;
}

/*****************************************************
* TP IFT3100H25 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * NodeProperty class implementation
 *
 *****************************************************/
#include "NodeProperty.h"


 /**
  * Constructor, receive 3 parameters (name, type and value)
  */
NodeProperty::NodeProperty(std::string p_name, int p_type, std::any p_value, std::string p_tooltip) : m_name(p_name), m_type(p_type), m_value(p_value), m_tooltip(p_tooltip) {
}


/**
 * Retrieve name
 */
const std::string NodeProperty::getName() {
	return m_name;
}


/**
 * Retrieve type
 */
const int NodeProperty::getType() {
	return m_type;
}


/**
 * Retrieve value
 */
const std::any NodeProperty::getValue() {
	return m_value;
}


/**
 * Retrieve the tooltip (may be an empty string)
 */
const std::string NodeProperty::getTooltip()
{
	return m_tooltip;
}

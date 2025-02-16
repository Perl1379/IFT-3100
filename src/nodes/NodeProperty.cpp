/*****************************************************
* TP IFT3100H24 - Knight Maker
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
NodeProperty::NodeProperty(std::string p_name, int p_type, std::any p_value) : m_name(p_name), m_type(p_type), m_value(p_value) {
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

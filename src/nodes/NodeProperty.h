/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * NodeProperty class definition
 *
 *****************************************************/
#pragma once
#include <any>
#include <string>

enum PROPERTY_TYPE {
	TEXT_FIELD,
	VECTOR3,
	COLOR_PICKER,
	FLOAT_FIELD,
	LABEL,
	BOOLEAN_FIELD,
	INT_FIELD,
	ITEM_LIST, //pass a std::vector<std::string> with the currentItem placed at the back
	ITEM_CLIST, //pass a std::pair<int, std::vector<char*>>: first is the currenItem and second is the list of options
};


class NodeProperty {

private:

	std::string m_name;
	int m_type;
	std::any m_value;
	std::string m_tooltip;

public:

	NodeProperty(std::string p_name, int p_type, std::any p_value, std::string p_tooltip = "");
	const std::string getName();
	const int getType();
	const std::any getValue();
	const std::string getTooltip();

};


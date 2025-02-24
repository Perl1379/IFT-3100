#pragma once

#include <BaseNode.h>

#include "ModalDialog.h"


class Vector3Dialog : public ModalDialog {

private:
	BaseNode* m_node;
	std::string m_name;
	glm::vec3 m_value;
	glm::vec3 m_Origvalue;



public:
	Vector3Dialog();
	void useProperty(BaseNode* p_node, const std::string& p_name, glm::vec3 p_value);
	void draw() override;

};


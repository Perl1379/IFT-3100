/*****************************************************
* TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * GroupNode class definition
 *
 *****************************************************/
#pragma once
#include "BaseNode.h"

class GroupNode : public BaseNode {

public:

 explicit GroupNode(const std::string &p_name);
 std::vector<NodeProperty> getProperties() const override;
 ofVec3f getBoundingBox() const override;

};



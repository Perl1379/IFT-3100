/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
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
    std::string getClassName() override { return "GroupNode"; }
    std::vector<NodeProperty> getProperties() const override;
    ofVec3f getBoundingBox() const override;

};

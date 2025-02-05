/*****************************************************
 * TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * BaseNode class definition
 *
 *****************************************************/
#pragma once
#include <of3dPrimitives.h>
#include <ofNode.h>

class BaseNode {

private:
    std::vector<BaseNode*> m_children;
    ofNode m_transform;

    // To be removed
    ofSpherePrimitive m_primitive;


public:

    BaseNode();
    virtual void draw();
    void addChild(BaseNode* child);

    // TODO:
    // load and save function
};




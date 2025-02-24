/*****************************************************
 * TP IFT3100H24 - Knight Maker
 * by Team 12
 *****************************************************
 *
 * BaseNode class definition
 *
 *****************************************************/
#pragma once
#include <ofMaterial.h>
#include <ofNode.h>
#include "NodeProperty.h"

class BaseNode {
protected:
    std::vector<BaseNode *> m_children;
    ofNode m_transform;
    std::string m_name = "Unnamed";
    int m_id = 0;
    bool m_displayBoundingBox = false;
    ofMaterial m_materialNode;
    ofMaterial m_materialUnlit;

    void beginDraw(bool p_objectPicking);

    void endDraw(bool p_objectPicking);

    void drawBoundingBox();

public:
    virtual ~BaseNode() = default;

    explicit BaseNode(const std::string &p_name);

    virtual void draw(bool p_objectPicking);

    virtual ofVec3f getBoundingBox() const;

    void addChild(BaseNode *p_child);

    void removeChild(int p_index);

    ofNode &getTransform() { return m_transform; };
    void setName(const std::string &p_name) { m_name = p_name; };
    const std::string &getName() { return m_name; }

    int getId() const;

    void displayBoundingBox(bool display);

    std::vector<BaseNode *> &getChildren() { return m_children; };

    virtual std::vector<NodeProperty> getProperties() const;

    virtual void setProperty(const std::string &p_name, std::any p_value);

    BaseNode *findNode(int p_id);
};

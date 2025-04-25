/*****************************************************
 * TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * BaseNode class definition
 *
 *****************************************************/
#pragma once
#include <Camera.h>
#include <ofMaterial.h>
#include <ofNode.h>
#include <TextureInfo.h>

#include "NodeProperty.h"

class BaseNode {
protected:
    std::vector<BaseNode *> m_children;
    BaseNode* m_parentNode;

    ofNode m_transform;
    std::string m_name = "Unnamed";
    int m_id = 0;
    bool m_displayBoundingBox = false;
    bool m_displayNode = true;
    bool m_userCanAddChild = true;
    bool m_useMaterial = true;
    bool m_isExpanded = true;

    bool m_transformTranslation = true;
    bool m_transformRotation = true;
    bool m_transformScale = true;
    bool m_axisTransformX = true;
    bool m_axisTransformY = true;
    bool m_axisTransformZ = true;

    int m_selectedMaterialPreset = 0;

    ofMaterial m_materialNode;
    ofMaterial m_materialUnlit;

    TextureInfo m_textureAlbedo;
    TextureInfo m_textureNormal;
    TextureInfo m_textureAmbientOcclusion;
    TextureInfo m_textureRoughness;
    TextureInfo m_textureMetallic;


    void beginDraw(bool p_objectPicking, Camera* p_camera);

    int endDraw(bool p_objectPicking, Camera* p_camera);

    void drawBoundingBox();


public:
    virtual ~BaseNode();

    explicit BaseNode(const std::string &p_name);

    virtual int draw(bool p_objectPicking, Camera* p_camera);
    virtual std::string getClassName() { return "BaseNode"; }
    virtual ofVec3f getBoundingBox() const;
    virtual bool isSerializable() { return true; }
    void setParent(BaseNode* p_parentNode);
    BaseNode* getParent();

    void addChild(BaseNode *p_child);
    void swapChildOrder(BaseNode* p_child1, BaseNode* p_child2);
    void removeChild(int p_index);
    virtual void removeAllChildren();
    bool userCanAddChild() const;

    ofNode &getTransform() { return m_transform; }
    ofMaterial &getMaterial() { return m_materialNode; }
    void setUseMaterial(bool p_useMaterial) { m_useMaterial = p_useMaterial; }
    bool getUseMaterial() { return m_useMaterial; }

    void setName(const std::string &p_name) { m_name = p_name; };
    const std::string &getName() { return m_name; }

    int getId() const;
    void setDisplayNode(bool p_displayNode);
    bool getDisplayNode() const;

    void displayNode(bool p_display);
    void displayBoundingBox(bool p_display);

    std::vector<BaseNode *> &getChildren() { return m_children; };

    // called to alert another node of a change, optionally defining what changed
    virtual void nodeChanged(const std::string& p_name = "", std::any p_value = nullptr) {};

    virtual std::vector<NodeProperty> getProperties() const;
    virtual void setProperty(const std::string &p_name, std::any p_value);
    virtual void applyPreset(int p_index);

    virtual void calculateTangentsAndBitangents();

    BaseNode* findNode(int p_id);
    BaseNode* getPreviousNode();
    BaseNode* getNextNode();
    virtual ofMesh* getMesh() { return nullptr; }

    bool isExpanded();
    void setExpanded(bool p_expanded);

    std::tuple<bool, bool, bool> getTransformOperations();
    std::tuple<bool, bool, bool> getTransformAxes();


};

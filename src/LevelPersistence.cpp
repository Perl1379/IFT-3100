/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * LevelPersistence class implementation
 *
 *****************************************************/

#include "LevelPersistence.h"

#include <AssetNode.h>
#include <BoxNode.h>
#include <CharacterNode.h>
#include <ConeNode.h>
#include <CylinderNode.h>
#include <Global.h>
#include <GroupNode.h>
#include <ofXml.h>
#include <PlaneNode.h>
#include <SplineControlPoint.h>
#include <SplineNode.h>
#include <TerrainNode.h>


/**
 * Helper function to convert string to vec3
 */
glm::vec3 stringToVec3(const std::string& str) {
    float x, y, z;
    std::stringstream ss(str);
    char delimiter;

    if (ss >> x >> delimiter >> y >> delimiter >> z) {
        return glm::vec3(x, y, z);
    } else {
        ofLogError() << "Invalid string format for glm::vec3 :" << str;
        return glm::vec3(0.0f);
    }
}


/**
 * Helper function to convert string to floatColor3
 */
ofFloatColor stringToColor(const std::string& str) {
    float r, g, b, a;
    std::stringstream ss(str);
    char delimiter;

    if (ss >> r >> delimiter >> g >> delimiter >> b >> delimiter >> a) {
        return ofFloatColor(r,g,b,a);
    } else {
        ofLogError() << "Invalid string format for glm::vec3" ;
        return ofFloatColor(1.0f);
    }
}


/**
 * Save level to file
 */
void LevelPersistence::saveToFile(const std::string& filename) {

    ofXml xml;

    ofXml xmlLevel = xml.appendChild("Level");
    ofXml xmlCameras = xmlLevel.appendChild("Cameras");
    ofXml xmlLights = xmlLevel.appendChild("Lights");
    ofXml xmlNodes = xmlLevel.appendChild("Nodes");
    xmlLevel.setAttribute("skyboxName", Global::m_skybox.getCurrentSkybox());

    for (int i=0;i<Global::m_cameras.size();i++) {

        ofCustomCamera* cam = Global::m_cameras[i].getCamera();
        ofXml xmlCamera = xmlCameras.appendChild("Camera");
        xmlCamera.setAttribute("position", cam->getPosition());
        xmlCamera.setAttribute("orientation", cam->getOrientationEulerDeg());
        xmlCamera.setAttribute("orthoMode", cam->getOrtho());
        xmlCamera.setAttribute("orthoZoom", cam->getOrthoZoom());
        xmlCamera.setAttribute("fov", cam->getFov());
        xmlCamera.setAttribute("nearClip", cam->getNearClip());
        xmlCamera.setAttribute("farClip", cam->getFarClip());

    }

    for (int i=0;i<8;i++) {

        LightSource* light = &Global::m_lights[i];
        ofXml xmlLight = xmlLights.appendChild("LightSource");
        xmlLight.setAttribute("type", light->getLightType());
        xmlLight.setAttribute("enabled", light->getEnabled());
        xmlLight.setAttribute("position", light->getPosition());
        xmlLight.setAttribute("orientation", light->getOrientation());
        xmlLight.setAttribute("scale", light->getScale());
        xmlLight.setAttribute("attenuation", light->getAttenuation());
        xmlLight.setAttribute("ambientColor", light->getColorAmbient());
        xmlLight.setAttribute("diffuseColor", light->getColorDiffuse());
        xmlLight.setAttribute("specularColor", light->getColorSpecular());

    }

    saveNode(xmlNodes, Global::m_level.getTree()->getChildren().at(0));


    xml.save(filename);

}


/**
 * Save a node and childs (recursive function)
 */
void LevelPersistence::saveNode(ofXml & xml, BaseNode * node) {

    if (!node->isSerializable()) return;

    ofXml xmlNode = xml.appendChild("Node");
    xmlNode.setAttribute("class", node->getClassName());
    xmlNode.setAttribute("expanded", node->isExpanded());

    ofXml xmlProperties = xmlNode.appendChild("Properties");
    auto properties = node->getProperties();
    for (auto prop : properties) {
        ofXml xmlProperty = xmlProperties.appendChild("Property");
        xmlProperty.setAttribute("name", prop.getName());
        xmlProperty.setAttribute("type", prop.getType());

        switch(prop.getType()) {
            case PROPERTY_TYPE::TEXT_FIELD: {
                auto value = std::any_cast<std::string>(prop.getValue());
                xmlProperty.setAttribute("value", value);
            }
            break;

            case PROPERTY_TYPE::COLOR_PICKER: {
                auto value = std::any_cast<ofFloatColor>(prop.getValue());
                xmlProperty.setAttribute("value", value);
            }
            break;

            case PROPERTY_TYPE::VECTOR3: {
                glm::vec3 value = std::any_cast<glm::vec3>(prop.getValue());
                xmlProperty.setAttribute("value", value);
            }
            break;

            case PROPERTY_TYPE::FLOAT_FIELD: {
                auto value = std::any_cast<float>(prop.getValue());
                xmlProperty.setAttribute("value", value);
            }
            break;

            case PROPERTY_TYPE::PRECISE_FLOAT_FIELD: {
                auto value = std::any_cast<float>(prop.getValue());
                xmlProperty.setAttribute("value", value);
            }
            break;

            case PROPERTY_TYPE::INT_FIELD: {
                auto value = std::any_cast<int>(prop.getValue());
                xmlProperty.setAttribute("value", value);
            }
            break;

            case PROPERTY_TYPE::BOOLEAN_FIELD: {
                auto value = std::any_cast<bool>(prop.getValue());
                xmlProperty.setAttribute("value", value);
            }
            break;

            case PROPERTY_TYPE::ITEM_LIST: {
                std::vector<std::string> value = std::any_cast<std::vector<std::string> >(prop.getValue());
                int initialSelection = stoi(value.back()); //get the index at the back of the vector
                xmlProperty.setAttribute("value", initialSelection);
            }
            break;

            case PROPERTY_TYPE::ITEM_CLIST: {
                std::pair<int, std::vector<char *> > value = std::any_cast<std::pair<int, std::vector<char *> > >(
                    prop.getValue());
                int currentItem = value.first;
                xmlProperty.setAttribute("value", currentItem);
            }
            break;

            case PROPERTY_TYPE::TEXT_INFO: {
                auto value = std::any_cast<std::string>(prop.getValue()).data();
                xmlProperty.setAttribute("value", value);
            }
            break;
        }

    }

    for (BaseNode* child : node->getChildren()) {
        saveNode(xmlNode, child);
    }

}


/**
 * Load level from file
 */
void LevelPersistence::loadFromFile(const std::string& filename) {
    ofLog() << "Load from file: " << filename;
    Global::m_level.reset();

    ofXml xml;
    if (!xml.load(filename)) {
        ofLogError() << "Failed to load level xml file: " << filename;
        return;
    }

    ofXml xmlLevel = xml.getFirstChild();

    std::string skyboxName = xmlLevel.getAttribute("skyboxName").getValue();
    Global::m_skybox.setup(skyboxName);

    auto xmlCameras = xmlLevel.getChild("Cameras").getChildren();


    int i = 0;
    for (ofXml camera : xmlCameras) {
        ofCustomCamera* cam = Global::m_cameras[i].getCamera();
        cam->setPosition(stringToVec3(camera.getAttribute("position").getValue()));
        cam->setOrientation(stringToVec3(camera.getAttribute("orientation").getValue()));
        if (camera.getAttribute("orthoMode").getBoolValue()) {
            cam->enableOrtho();
        } else {
            cam->disableOrtho();
        }
        cam->setOrthoZoom(camera.getAttribute("orthoZoom").getFloatValue());
        cam->setFov(camera.getAttribute("fov").getFloatValue());
        cam->setNearClip(camera.getAttribute("nearClip").getFloatValue());
        cam->setFarClip(camera.getAttribute("farClip").getFloatValue());
        i++;
    }

    i = 0;
    auto xmlLights = xmlLevel.getChild("Lights").getChildren();
    for (ofXml light : xmlLights) {
        LightSource* lightSource = &Global::m_lights[i];
        lightSource->setLightType(static_cast<LIGHT_TYPE>(light.getAttribute("type").getIntValue()));
        lightSource->setEnabled(light.getAttribute("enabled").getBoolValue());
        lightSource->setPosition(stringToVec3(light.getAttribute("position").getValue()));
        lightSource->setOrientation(stringToVec3(light.getAttribute("orientation").getValue()));
        lightSource->setScale(stringToVec3(light.getAttribute("scale").getValue()));
        lightSource->setAttenuation(light.getAttribute("attenuation").getFloatValue());
        lightSource->setColorAmbient(stringToColor(light.getAttribute("ambientColor").getValue()));
        lightSource->setColorDiffuse(stringToColor(light.getAttribute("diffuseColor").getValue()));
        lightSource->setColorSpecular(stringToColor(light.getAttribute("specularColor").getValue()));
         i++;
    }



    auto xmlNodes = xmlLevel.getChild("Nodes").getChildren();
    for (ofXml node : xmlNodes) {
        loadNode(node, Global::m_level.getTree()->getChildren().at(0));
    }
}


/**
 * Load node
 */
void LevelPersistence::loadNode(ofXml &xml, BaseNode *parent) {
    std::string className = xml.getAttribute("class").getValue();

    auto children = xml.getChildren();
    ofXml properties = xml.getFirstChild();
    std::string nodeName = "Unnamed";

    BaseNode* node;
    for (ofXml property : properties.getChildren()) {
        std::string propertyName = property.getAttribute("name").getValue();
        PROPERTY_TYPE propertyType = static_cast<PROPERTY_TYPE>(property.getAttribute("type").getIntValue());


        if (propertyName == "Name") {
            nodeName = property.getAttribute("value").getValue();
            if (className == "AssetStore") node = new AssetNode(nodeName);
            else if (className == "BoxNode") node = new BoxNode(nodeName);
            else if (className == "CharacterNode") node = new CharacterNode(nodeName);
            else if (className == "ConeNode") node = new ConeNode(nodeName);
            else if (className == "CylinderNode") node = new CylinderNode(nodeName);
            else if (className == "GroupNode") node = new GroupNode(nodeName);
            else if (className == "PlaneNode") node = new PlaneNode(nodeName);
            else if (className == "SphereNode") node = new SphereNode(nodeName);
            else if (className == "SplineNode") {node = new SplineNode(nodeName); ((SplineNode*) node)->init(); }
            else if (className == "TerrainNode") node = new TerrainNode(nodeName);
            else node = new BaseNode(nodeName);

            parent->addChild(node);

            continue;
        }

        switch(propertyType) {


            case PROPERTY_TYPE::ITEM_CLIST:
            case PROPERTY_TYPE::ITEM_LIST: {
                auto value = property.getAttribute("value").getIntValue();
                node->setProperty(propertyName, value);
            }
            break;

            case PROPERTY_TYPE::BOOLEAN_FIELD: {
                auto value = property.getAttribute("value").getBoolValue();
                node->setProperty(propertyName, value);
            }
            break;

            case PROPERTY_TYPE::TEXT_FIELD: {
                auto value = property.getAttribute("value").getValue();
                node->setProperty(propertyName, value);

            }
            break;

            case PROPERTY_TYPE::TEXT_INFO: {
                auto value = property.getAttribute("value").getValue();
                node->setProperty(propertyName, value);
            }
            break;

            case PROPERTY_TYPE::COLOR_PICKER: {
                std::string propertyValue = property.getAttribute("value").getValue();
                auto value = stringToColor(propertyValue);
                node->setProperty(propertyName, value);
            }
            break;

            case PROPERTY_TYPE::VECTOR3: {

                std::string propertyValue = property.getAttribute("value").getValue();
                auto value = stringToVec3(propertyValue);
                node->setProperty(propertyName, value);
            }
            break;

            case PROPERTY_TYPE::INT_FIELD: {
                auto value = property.getAttribute("value").getIntValue();
                node->setProperty(propertyName, value);
            }
            break;

            case PROPERTY_TYPE::PRECISE_FLOAT_FIELD:
            case PROPERTY_TYPE::FLOAT_FIELD: {
                auto value = property.getAttribute("value").getFloatValue();
                node->setProperty(propertyName, value);
            }
            break;

            default:
            {
                // Do nothing
            }
            break;
        }



    }

//    ofExit(0);




    int i = 0;
    for (ofXml child : children) {

        if (child.getName() == "Node") {
            loadNode(child, node);
        }

        i++;
    }

   // ofExit(0);

    //auto childs = xml.getChildren();
    //for (ofXml child : childs) {

        //loadNode(child, test);
    //}

}


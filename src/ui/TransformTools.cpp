/*****************************************************
* TP IFT3100H25 - Adventure Party Maker
 * by Team 12
 *****************************************************
 *
 * TransformTools class implementation
 *
 *****************************************************/
#include "TransformTools.h"
#include <Global.h>
#include <LightNode.h>
#include <ofGraphics.h>


/**
 * Object constructor
 */
TransformTools::TransformTools() {

    m_materialUnlit.setEmissiveColor(ofFloatColor(1.0, 1.0, 1.0));
    m_materialUnlit.setAmbientColor(ofFloatColor(0.0, 0.0, 0.0));
    m_materialUnlit.setDiffuseColor(ofFloatColor(0.0));
    m_materialUnlit.setSpecularColor(ofFloatColor(0.0));

    for (int i=0;i<3;i++) {
        m_conePrimitives.emplace_back();
        m_spherePrimitives.emplace_back();
        m_conePrimitivesObjectPicking.emplace_back();
        m_spherePrimitivesObjectPicking.emplace_back();
    }

    for (int i=0;i<4;i++) {
        m_cubePrimitives.emplace_back();
        m_cubePrimitivesObjectPicking.emplace_back();
    }

    m_conePrimitives[0].setScale(m_conePrimitivesScale);
    m_conePrimitives[0].setOrientation(glm::vec3(0, 0, 90));
    m_conePrimitives[1].setScale(m_conePrimitivesScale);
    m_conePrimitives[1].setOrientation(glm::vec3(180, 0, 0));
    m_conePrimitives[2].setScale(m_conePrimitivesScale);
    m_conePrimitives[2].setOrientation(glm::vec3(-90, 0, 0));
    m_spherePrimitives[0].setScale(m_spherePrimitivesScale);
    m_spherePrimitives[1].setScale(m_spherePrimitivesScale);
    m_spherePrimitives[2].setScale(m_spherePrimitivesScale);
    m_cubePrimitives[0].setScale(m_cubePrimitivesScale);
    m_cubePrimitives[1].setScale(m_cubePrimitivesScale);
    m_cubePrimitives[2].setScale(m_cubePrimitivesScale);
    m_cubePrimitives[3].setScale(m_cubePrimitivesScale);

    m_conePrimitivesObjectPicking[0].setScale(m_conePrimitivesScaleObjectPicking);
    m_conePrimitivesObjectPicking[0].setOrientation(glm::vec3(0, 0, 90));
    m_conePrimitivesObjectPicking[1].setScale(m_conePrimitivesScaleObjectPicking);
    m_conePrimitivesObjectPicking[1].setOrientation(glm::vec3(180, 0, 0));
    m_conePrimitivesObjectPicking[2].setScale(m_conePrimitivesScaleObjectPicking);
    m_conePrimitivesObjectPicking[2].setOrientation(glm::vec3(-90, 0, 0));
    m_spherePrimitivesObjectPicking[0].setScale(m_spherePrimitivesScaleObjectPicking);
    m_spherePrimitivesObjectPicking[1].setScale(m_spherePrimitivesScaleObjectPicking);
    m_spherePrimitivesObjectPicking[2].setScale(m_spherePrimitivesScaleObjectPicking);
    m_cubePrimitivesObjectPicking[0].setScale(m_cubePrimitivesScaleObjectPicking);
    m_cubePrimitivesObjectPicking[1].setScale(m_cubePrimitivesScaleObjectPicking);
    m_cubePrimitivesObjectPicking[2].setScale(m_cubePrimitivesScaleObjectPicking);
    m_cubePrimitivesObjectPicking[3].setScale(m_cubePrimitivesScaleObjectPicking);

}

/**
 * Draw transform tools
 */
void TransformTools::draw(bool p_objectPicking) {
    if (Global::m_selectedNode < 2) return;

    BaseNode* node = Global::m_level.getTree()->findNode(Global::m_selectedNode);
    m_materialUnlit.begin();
    ofDisableDepthTest();

    m_transform.transformGL();
    m_transform.setOrientation(node->getTransform().getGlobalOrientation());
    m_transform.setPosition(node->getTransform().getGlobalPosition());

    auto [doTranslate,doRotate,doScale] = node->getTransformOperations();
    switch(m_transformMode) {
        case TRANSLATE:
            if (doTranslate) {
                drawTranslate(p_objectPicking, node);
            }
            break;
        case ROTATE:
            if (doRotate) {
                drawRotate(p_objectPicking, node);
            }
            break;
        case SCALE:
            if (doScale) {
                drawScale(p_objectPicking, node);
            }
            break;

    }

    m_transform.restoreTransformGL();
    ofEnableDepthTest();
    m_materialUnlit.end();

}


/**
 * Draw translate arrows
 */
void TransformTools::drawTranslate(bool p_objectPicking, BaseNode* node)  {

    auto [doX, doY, doZ ] = node->getTransformAxes();

    glm::vec3 pos(0,0,0);
    auto scale = node->getTransform().getGlobalScale();
    auto length = node->getBoundingBox() * 0.5;

    float lengthX = length.x * scale.x;
    float lengthY = length.y * scale.y;
    float lengthZ = length.z * scale.z;

    if (lengthX < 200.0f) lengthX = 200.0f;
    if (lengthY < 200.0f) lengthY = 200.0f;
    if (lengthZ < 200.0f) lengthZ = 200.0f;

    if (lengthX > 600.0f) lengthX = 600.0f;
    if (lengthY > 600.0f) lengthY = 600.0f;
    if (lengthZ > 600.0f) lengthZ = 600.0f;

    if (doX) {
        if (p_objectPicking) {
            m_materialUnlit.setEmissiveColor(Global::idToColor(TRANSLATE_X));
        } else {
            m_materialUnlit.setEmissiveColor(ofFloatColor(1.0, 0.0, 0.0));
        }

        if (p_objectPicking) {
            m_conePrimitivesObjectPicking[0].setPosition(pos + glm::vec3(abs(lengthX), 0.0, 0.0));
            m_conePrimitivesObjectPicking[0].draw();
        } else {
            ofDrawLine(pos, pos + glm::vec3(abs(lengthX), 0.0, 0.0));
            m_conePrimitives[0].setPosition(pos + glm::vec3(abs(lengthX), 0.0, 0.0));
            m_conePrimitives[0].draw();
        }
    }

    if (doY) {
        if (p_objectPicking) {
            m_materialUnlit.setEmissiveColor(Global::idToColor(TRANSLATE_Y));
        } else {
            m_materialUnlit.setEmissiveColor(ofFloatColor(0.0, 1.0, 0.0));
        }

        if (p_objectPicking) {
            m_conePrimitivesObjectPicking[1].setPosition(pos + glm::vec3(0, abs(lengthY), 0.0));
            m_conePrimitivesObjectPicking[1].draw();
        } else {
            ofDrawLine(pos, pos + glm::vec3(0.0, abs(lengthY), 0.0));
            m_conePrimitives[1].setPosition(pos + glm::vec3(0, abs(lengthY), 0.0));
            m_conePrimitives[1].draw();
        }
    }

    if (doZ) {
        if (p_objectPicking) {
            m_materialUnlit.setEmissiveColor(Global::idToColor(TRANSLATE_Z));
        } else {
            m_materialUnlit.setEmissiveColor(ofFloatColor(0.0, 0.0, 1.0));
        }

        if (p_objectPicking) {
            m_conePrimitivesObjectPicking[2].setPosition(pos + glm::vec3(0.0, 0.0, abs(lengthZ)));
            m_conePrimitivesObjectPicking[2].draw();
        } else {
            ofDrawLine(pos, pos + glm::vec3(0.0, 0.0, abs(lengthZ)));
            m_conePrimitives[2].setPosition(pos + glm::vec3(0.0, 0.0, abs(lengthZ)));
            m_conePrimitives[2].draw();

        }
    }
}



/**
 * Draw rotate circles
 */
void TransformTools::drawRotate(bool p_objectPicking, BaseNode* node)  {

    auto [doX, doY, doZ ] = node->getTransformAxes();

    glm::vec3 pos(0,0,0);
    auto scale = node->getTransform().getScale();
    auto length = node->getBoundingBox() * 0.5;
    float lengthX = length.x * scale.x;
    float lengthY = length.y * scale.y;
    float lengthZ = length.z * scale.z;

    if (lengthX < 200.0f) lengthX = 200.0f;
    if (lengthY < 200.0f) lengthY = 200.0f;
    if (lengthZ < 200.0f) lengthZ = 200.0f;

    if (lengthX > 600.0f) lengthX = 600.0f;
    if (lengthY > 600.0f) lengthY = 600.0f;
    if (lengthZ > 600.0f) lengthZ = 600.0f;

    if (doX) {
        if (p_objectPicking) {
            m_materialUnlit.setEmissiveColor(Global::idToColor(ROTATE_X));
        } else {
            m_materialUnlit.setEmissiveColor(ofFloatColor(1.0, 0.0, 0.0));
        }

        if (p_objectPicking) {
            m_spherePrimitivesObjectPicking[0].setPosition(pos + glm::vec3(lengthX, 0.0, 0.0));
            m_spherePrimitivesObjectPicking[0].draw();

        } else {
            ofNoFill();
            ofDrawCircle(pos, lengthX);
            ofFill();
            m_spherePrimitives[0].setPosition(pos + glm::vec3(lengthX, 0.0, 0.0));
            m_spherePrimitives[0].draw();
        }
    }

    if (doY) {
        if (p_objectPicking) {
            m_materialUnlit.setEmissiveColor(Global::idToColor(ROTATE_Y));
        } else {
            m_materialUnlit.setEmissiveColor(ofFloatColor(0.0, 1.0, 0.0));
        }

        if (p_objectPicking) {
            m_spherePrimitivesObjectPicking[1].setPosition(pos + glm::vec3(0, lengthY, 0.0));
            m_spherePrimitivesObjectPicking[1].draw();
        } else {
            ofPushMatrix();
            ofRotateYDeg(90);
            ofNoFill();
            ofDrawCircle(pos, lengthY);
            ofFill();
            ofPopMatrix();;
            m_spherePrimitives[1].setPosition(pos + glm::vec3(0, lengthY, 0.0));
            m_spherePrimitives[1].draw();

        }
    }

    if (doZ) {
        if (p_objectPicking) {
            m_materialUnlit.setEmissiveColor(Global::idToColor(ROTATE_Z));
        } else {
            m_materialUnlit.setEmissiveColor(ofFloatColor(0.0, 0.0, 1.0));
        }

        if (p_objectPicking) {
            m_spherePrimitivesObjectPicking[2].setPosition(pos + glm::vec3(0.0, 0.0, lengthZ));
            m_spherePrimitivesObjectPicking[2].draw();
        } else {
            ofPushMatrix();
            ofRotateXDeg(90);
            ofNoFill();
            ofDrawCircle(pos, lengthZ);
            ofFill();
            ofPopMatrix();;
            m_spherePrimitives[2].setPosition(pos + glm::vec3(0.0, 0.0, lengthZ));
            m_spherePrimitives[2].draw();
        }
    }
}


/**
 * Draw scale cubes
 */
void TransformTools::drawScale(bool p_objectPicking, BaseNode* node) {
    auto [doX, doY, doZ ] = node->getTransformAxes();

    glm::vec3 pos(0,0,0);
    auto scale = node->getTransform().getScale();
    auto length = node->getBoundingBox() * 0.5;
    float lengthX = length.x * scale.x;
    float lengthY = length.y * scale.y;
    float lengthZ = length.z * scale.z;

    if (lengthX < 200.0f) lengthX = 200.0f;
    if (lengthY < 200.0f) lengthY = 200.0f;
    if (lengthZ < 200.0f) lengthZ = 200.0f;

    if (lengthX > 600.0f) lengthX = 600.0f;
    if (lengthY > 600.0f) lengthY = 600.0f;
    if (lengthZ > 600.0f) lengthZ = 600.0f;

    if (doX) {
        if (p_objectPicking) {
            m_materialUnlit.setEmissiveColor(Global::idToColor(SCALE_X));
        } else {
            m_materialUnlit.setEmissiveColor(ofFloatColor(1.0, 0.0, 0.0));
        }

        if (p_objectPicking) {
            m_cubePrimitivesObjectPicking[0].setPosition(pos + glm::vec3(lengthX, 0.0, 0.0));
            m_cubePrimitivesObjectPicking[0].draw();
        } else {
            ofDrawLine(pos, pos + glm::vec3(lengthX, 0.0, 0.0));
            m_cubePrimitives[0].setPosition(pos + glm::vec3(lengthX, 0.0, 0.0));
            m_cubePrimitives[0].draw();
        }
    }

    if (doY) {
        if (p_objectPicking) {
            m_materialUnlit.setEmissiveColor(Global::idToColor(SCALE_Y));
        } else {
            m_materialUnlit.setEmissiveColor(ofFloatColor(0.0, 1.0, 0.0));
        }

        if (p_objectPicking) {
            m_cubePrimitivesObjectPicking[1].setPosition(pos + glm::vec3(0, lengthY, 0.0));
            m_cubePrimitivesObjectPicking[1].draw();
        } else {
            ofDrawLine(pos, pos + glm::vec3(0.0, lengthY, 0.0));
            m_cubePrimitives[1].setPosition(pos + glm::vec3(0, lengthY, 0.0));
            m_cubePrimitives[1].draw();
        }
    }

    if (doZ) {
        if (p_objectPicking) {
            m_materialUnlit.setEmissiveColor(Global::idToColor(SCALE_Z));
        } else {
            m_materialUnlit.setEmissiveColor(ofFloatColor(0.0, 0.0, 1.0));
        }

        if (p_objectPicking) {
            m_cubePrimitivesObjectPicking[2].setPosition(pos + glm::vec3(0.0, 0.0, lengthZ));
            m_cubePrimitivesObjectPicking[2].draw();
        } else {
            ofDrawLine(pos, pos + glm::vec3(0.0, 0.0, lengthZ));
            m_cubePrimitives[2].setPosition(pos + glm::vec3(0.0, 0.0, lengthZ));
            m_cubePrimitives[2].draw();
        }
    }

    if (doX && doY && doZ) {
        if (p_objectPicking) {
            m_materialUnlit.setEmissiveColor(Global::idToColor(SCALE_ALL));
        } else {
            m_materialUnlit.setEmissiveColor(ofFloatColor(1.0, 0.0, 1.0));
        }

        if (p_objectPicking) {
            m_cubePrimitivesObjectPicking[2].setPosition(pos);
            m_cubePrimitivesObjectPicking[2].draw();
        } else {
            m_cubePrimitives[2].setPosition(pos);
            m_cubePrimitives[2].draw();
        }
    }
}


/**
 * Begin transformation
 */
void TransformTools::onMouseButtonPressed(int p_transformPixelColor, ImVec2 mousePosition) {

    m_previousMousePosition = mousePosition;
    m_currentTransformPixelColor = p_transformPixelColor;
    BaseNode* node = Global::m_level.getTree()->findNode(Global::m_selectedNode);
    if (node != nullptr) {
        m_initialNodePosition = node->getTransform().getPosition();
        m_initialNodeOrientation = node->getTransform().getOrientationEulerDeg();
        m_initialNodeScale = node->getTransform().getScale();
    }

}


/**
 * Apply temporary changes to node
 */
void TransformTools::onMouseDrag(ImVec2 mousePosition) {

    if (m_currentTransformPixelColor == -1) return;

    // Get difference between previous mouse position and current one
    glm::vec2 diff = mousePosition - m_previousMousePosition;
    m_previousMousePosition = mousePosition;
    float mouseSpeedTranslate = 5.0f;
    float mouseSpeedRotate = 0.5f;
    float mouseSpeedScale = 0.025f;

    BaseNode* node = Global::m_level.getTree()->findNode(Global::m_selectedNode);

    // Access the camera's view matrix
    glm::vec3 cameraRight = Global::m_cameras[m_camera_index].getCamera()->getXAxis();
    glm::vec3 cameraUp = Global::m_cameras[m_camera_index].getCamera()->getYAxis();
    glm::vec3 cameraForward = Global::m_cameras[m_camera_index].getCamera()->getZAxis();
    glm::vec3 nodeUp = node->getTransform().getYAxis();
    glm::vec3 nodeRight = node->getTransform().getXAxis();
    glm::vec3 nodeForward = node->getTransform().getZAxis();


    // Depending on the selected axis, update the position
    switch(m_currentTransformPixelColor) {
        case TRANSLATE_X: {
            float rightDirection = glm::dot(nodeRight, cameraRight);
            node->getTransform().truck(diff.x * mouseSpeedTranslate * glm::sign(rightDirection));
            if (node->getClassName() == "LightNode") {
                Global::m_lights[((LightNode*) node)->getLightIndex()].setPosition(node->getTransform().getPosition());
            }
        }
        break;

        case TRANSLATE_Y: {

            float upDirection = glm::dot(nodeUp, cameraUp);
            node->getTransform().boom(-diff.y * mouseSpeedTranslate * glm::sign(upDirection));
            if (node->getClassName() == "LightNode") {
                Global::m_lights[((LightNode*) node)->getLightIndex()].setPosition(node->getTransform().getPosition());
            }

        }
        break;

        case TRANSLATE_Z: {

            float moveAmount = diff.y * mouseSpeedTranslate;
            float direction = glm::dot(nodeForward, cameraForward);
            node->getTransform().dolly(moveAmount * glm::sign(direction));
            if (node->getClassName() == "LightNode") {
                Global::m_lights[((LightNode*) node)->getLightIndex()].setPosition(node->getTransform().getPosition());
            }
        }
        break;

        case ROTATE_X: {

            float rightDirection = glm::dot(cameraRight, nodeForward);
            node->getTransform().rotateDeg(glm::sign(rightDirection) * -diff.x * mouseSpeedRotate, nodeForward);
            if (node->getClassName() == "LightNode") {
                Global::m_lights[((LightNode*) node)->getLightIndex()].setOrientation(node->getTransform().getOrientationEulerDeg());
            }

        }
        break;
        case ROTATE_Y: {

            float upDirection = glm::dot(cameraUp, nodeRight);
            node->getTransform().rotateDeg(glm::sign(upDirection) * -diff.y * mouseSpeedRotate, nodeRight);
            if (node->getClassName() == "LightNode") {
                Global::m_lights[((LightNode*) node)->getLightIndex()].setOrientation(node->getTransform().getOrientationEulerDeg());
            }
        }
        break;

        case ROTATE_Z: {
            float forwardDirection = glm::dot(cameraForward, nodeUp);
            node->getTransform().rotateDeg(glm::sign(forwardDirection) * -diff.x * mouseSpeedRotate, nodeUp);
            if (node->getClassName() == "LightNode") {
                Global::m_lights[((LightNode*) node)->getLightIndex()].setOrientation(node->getTransform().getOrientationEulerDeg());
            }
        }
        break;

        case SCALE_X: {
            float rightDirection = glm::dot(cameraRight, nodeRight);
            glm::vec3 scale = node->getTransform().getScale();
            scale.x += glm::sign(rightDirection) * diff.x * mouseSpeedScale;
            node->getTransform().setScale(scale);
            if (node->getClassName() == "LightNode") {
                Global::m_lights[((LightNode*) node)->getLightIndex()].setScale(node->getTransform().getScale());
            }
        }
        break;

        case SCALE_Y: {
            float upDirection = glm::dot(cameraUp, nodeUp);
            glm::vec3 scale = node->getTransform().getScale();
            scale.y += glm::sign(upDirection) * diff.y * mouseSpeedScale;
            node->getTransform().setScale(scale);
            if (node->getClassName() == "LightNode") {
                Global::m_lights[((LightNode*) node)->getLightIndex()].setScale(node->getTransform().getScale());
            }
        }
        break;

        case SCALE_Z: {
            float forwardDirection = glm::dot(cameraForward, nodeForward);
            glm::vec3 scale = node->getTransform().getScale();
            scale.z += glm::sign(forwardDirection) * diff.x * mouseSpeedScale;
            node->getTransform().setScale(scale);
            if (node->getClassName() == "LightNode") {
                Global::m_lights[((LightNode*) node)->getLightIndex()].setScale(node->getTransform().getScale());
            }
        }

        case SCALE_ALL: {
            glm::vec3 scale = node->getTransform().getScale();
            if (cameraForward.y < 0) {
                scale += diff.x * mouseSpeedScale;
            } else {
                scale -= diff.x * mouseSpeedScale;
            }
            node->getTransform().setScale(scale);
            if (node->getClassName() == "LightNode") {
                Global::m_lights[((LightNode*) node)->getLightIndex()].setScale(node->getTransform().getScale());
            }
        }
        break;
    }
}


/**
 * Complete transformation
 */
void TransformTools::onMouseButtonReleased(ImVec2 mousePosition) {
    if (m_currentTransformPixelColor == -1) return;

    BaseNode* node = Global::m_level.getTree()->findNode(Global::m_selectedNode);
    if (node != nullptr) {
        switch (m_transformMode) {

            case TRANSLATE: {
                Global::m_actions.addAction(node, "Position", m_initialNodePosition, node->getTransform().getPosition());
            }
            break;

            case ROTATE: {
                Global::m_actions.addAction(node, "Orientation", m_initialNodeOrientation, node->getTransform().getOrientationEulerDeg());
            }
            break;

            case SCALE: {
                Global::m_actions.addAction(node, "Scale", m_initialNodeScale, node->getTransform().getScale());
            }
            break;
        }
    }
    m_currentTransformPixelColor = -1;
}


/**
 * Set camera index
 */
void TransformTools::setCameraIndex(int index) {
    m_camera_index = index;
}


/**
 * Get transform mode
 */
int TransformTools::getTransformMode() const {
    return m_transformMode;
}


/**
 * Set transform mode
 */
void TransformTools::setTransformMode(int mode) {
    m_transformMode = mode;
}


/**
 * Get cone primitives
 */
const std::vector<ofConePrimitive>& TransformTools::getConePrimitives() {
    return m_conePrimitives;
}


/**
 * Get sphere primitives
 */
const std::vector<ofSpherePrimitive>& TransformTools::getSpherePrimitives() {
    return m_spherePrimitives;
}


/**
 * Get cube primitives
 */
const std::vector<ofBoxPrimitive>& TransformTools::getCubePrimitives() {
    return m_cubePrimitives;
}
